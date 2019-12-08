
Explication des particularités du code
--------------------------------------

### Fonctionnalités du code

Le programme prend en tant qu'arguments le nom d'une étape du week-end de Formule 1 ainsi que la longueur d'un tour en kilomètres.
Si ce dernier n'est pas fourni, une valeur par défaut est attribuée.

On lance la phase sélectionnée pour chacune des voitures participantes.
Lors de la simulation, les voitures participantes vont générer des temps aléatoires à chaque secteur.

Un tableau de valeurs reprenant des informations diverses est ensuite affiché afin de pouvoir suivre l'évolution de l'étape choisie.
Les informations représentée dans ce dernier dépendent de l'étape concernée.
Ce tableau est également trié en fonction du meilleur temps de tour par pilote ou, dans le cadre de la course, trié en fonction de leur position.

Au départ de la course, chaque participant démarre dans l'ordre précédemment déterminé par les séances de qualifications et avec une pénalité relative à leur position de départ.

Lorsque la simulation d'une étape est terminée, les positions des pilotes est sauvegardée dans un fichier.
Ce fichier sera chargé lors de l'étape suivante afin de déterminer les participants ainsi que leurs positions.

### Mémoire partagée et communication entre processus

La mémoire partagée est un moyen efficace de transférer des données entre processus
indépendants (issus de programmes binaires séparés, de propriétaires différents). Il s’agit
d’un ensemble d’adresses (perçu sous la forme d’un bloc d'octets) apparaissant dans
l’espace d’adressage du processus qui le crée. Les autres processus pouvant alors
« attacher » le même segment de mémoire partagée dans leur propre espace d’adressage
(virtuel).

Si un processus écrit dans la mémoire partagée, la modification est immédiatement perçue
par tout autre processus ayant accès à cette mémoire partagée.

La mémoire partagée ne dispose d’aucun dispositif de synchronisation. Rien ne permet de
veiller automatiquement à ce qu’un processus ne puisse commencer à lire la mémoire alors
qu’un autre processus n’y a pas terminé son écriture : c’est au programmeur de régler
l’accès à cette ressource commune aux processus ayant accès à cette mémoire partagée.

La mémoire partagée contient un tableau de structure comportant les informations de secteurs entre autres choses.

```c
typedef struct F1_Car {
    int id;
    double lap_time;
    double s1;
    double s2;
    double s3;
    int best_s1;
    int best_s2;
    int best_s3;
    int stand;
    int out;
    int lap;
    int best_lap_time;
    int done;
} F1_Car;
```

- `shmget` (cle,taille,flag) retourne l’identificateur d’un segment à partir de sa clé(cle) ou -1 en cas d’échec. 
Le segment sera créé s’il n’existait pas encore. On peut utiliser la clé IPC_PRIVATE pour la création quand 
il n’est pas utile ensuite d’acquérir l’identificateur. Le paramètre taille donne le nombre d’octets du segment 
(s’il a déjà été créé, la taille doit être inférieure ou égale à la taille de création). 
Le paramètre option est une combinaison (par OU bit à bit) de constantes (telles que IPC_CREAT pour la création) 
et de droits d’accès (comme 0666). Par exemple pour créer un segment on utilisera typiquement l’option IPC_CREAT|0666, 
et pour l’acquisition simplement 0666. 

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(key_t key, int size, int shmflg);
```

```c
F1_Car *car;

  int struct_shm_id = shmget(IPC_PRIVATE, sizeof(F1_Car) * circuit.number_of_cars, 0600 | IPC_CREAT);
    if (struct_shm_id == -1) {
        perror("shmget failed !");
        exit(EXIT_FAILURE);
    }
```

- `shmat` (identificateur,NULL,option) sert à attacher un segment, c’est à dire à obtenir une fois que l’on connaît son identificateur, un pointeur vers la zone de mémoire partagée. L’option sera SHM_RDONLY pour un segment en lecture seule ou 0 pour un segment
en lecture/écriture. Cette primitive retourne l’adresse de la zone de mémoire partagée ou (void *)(-1) en cas d’échec

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 
void *shmat(int shmid, void *shmaddr, int shmflg);
```

```c
   car = shmat(struct_shm_id, NULL, 0);
    if (car == (void *) (-1)) {
        perror("shmat failed !");
        exit(EXIT_FAILURE);
    }
```

Dans notre cas, la mémoire partagée n'est accédée ou modifiée qu'avec un seul "écrivain" et un seul "lecteur" à la fois; il n'y aura jamais plus d'une écriture et lecture en même temps.
Ici, chaque processus fils est un écrivain alors que le lecteur est le processus père.

La sémaphore nous permettent de garantir l'accès exclusif à la mémoire partagée.
Les opérations `sem_wait(sem_t *sem)` et `sem_post(sem_t *sem)` permettent respectivement de verrouiller et déverrouiller une sémaphore.

### Libération des ressources de l'ordinateur

Afin de libérer les ressources de l'ordinateur, plusieurs étapes sont réalisées une fois que les processus 
enfants ont terminé leur fonction et que le programme est prêt à quitter.

Premièrement, il y a "destruction" de la sémaphore par le biais de l'opération `sem_destroy(sem_t *sem)`.

Ensuite, on se détache des zones de mémoire partage et ensuite on les supprime.


- `shmdt` (adresse) sert à détacher le segment attaché à l’adresse passée en paramètre. Retourne 0 en cas de succès, ou -1 en cas d’échec.
Lorsqu'un processus n'utilise plus un segment de mémoire partagée, il peut le détacher de son espace adresses par shmdt. Attention, l'argument de shmdt est l'adresse à laquelle le segment a été attaché, pas le semid du segment!
shmdt ne détruit pas le segment. Pour cela, il faut utiliser shmctl.

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmdt(void *shmaddr);
```
```c
shmdt(car);
```

```c
shmdt(car);
shmctl(struct_shm_id, IPC_RMID, NULL);

sem_destroy(sem);
shmdt(sem);
shmctl(sem_shm_id, IPC_RMID, NULL);
```

### Création et gestion des processus

Chaque voiture correspond à un processus fils, tandis que le père s'occupe de la gestion des étapes et de l'affichage.

La création des processus se fait par le biais de la fonction `fork`, faisant partie des appels système POSIX.
Elle permet de donner naissance à un nouveau processus qui est sa copie.

Nos `fork` sont présent dans le fichier de code source `main.c`.

### Rôle du processus père

Dans notre cas, nous avons un processus père donnant naissance au nombre de processus fils nécessaire à l'étape choisie.
Chaque processus fils représente une voiture.

Le processus père, quant à lui, va lire des informations provenant de la mémoire partagée.
Il s'occupe également de l'affichage ainsi que du tri tout comme la sauvegarde des informations sur fichier.

\pagebreak

Difficultés rencontrées et solutions
------------------------------------

Concernant les difficultés rencontrées, suite à la reprise de ce projet pour la seconde session, il n'y a pas eu particulièrement de nouveaux problèmes rencontrés.

Comme indiqué dans le point traitant la compréhension du cahier des charges, grâce à la communication avec la professeur ainsi que du travail réalisé par chacun des membres pour la prise de note, la création d'un flowchart et d'un tableau détaillé reprenant les informations importantes de façon claire et concise, nous avons su éviter la plupart des difficultés possiblement rencontrées.

### Compréhension du cahier des charges

Au vu du cahier des charges reçu, nous avons eu des difficultés à comprendre plus concrètement comment mettre en œuvre certaines implémentations demandées tant lors de la première session que lors de la seconde session.
À force de recherche et également de questions posées dans le cadre du temps consacré spécifiquement au projet en cours lors de la première session, nous avons accumulé différentes notes nous permettant de mieux visualiser ce qui nous avait posé problème.

Deux rendez-vous ont été convenu avec la professeur (2 avril 2019 à 15h et 25 juin 2019 à 11h) afin de mieux visualiser les demandes, de comprendre ce qui n'avait pas été lors de la première session et également les détails qui n'avaient pas été correctement compris ou nous paraissant tout simplement trop flou.

Suite à ces rendez-vous avec la professeur, le flowchart et le tableau détaillé contenant les informations importantes des demandes dans le cahier des charges fourni, cette difficultée à été résolue.

\pagebreak

Évolutions futures
------------------

### Intégration de codes couleurs dans l'affichage

Il s'agit certes d'une implémentation de moindre importance, mais cela pourrait s'avérer pratique pour ressortir de manière plus rapide les informations les plus importantes.
Par exemple, on pourrait réaliser un code couleur pour :

- Les 3 premières places dans le classement,
- Le temps le plus rapide au tour,
- La voiture ayant le temps le plus rapide au tour depuis le début de la course,
- La ou les voiture(s) ayant abandonné la course (OUT).

### Affichage cliquable

Comme à la manière de `htop` dans Linux, la possibilité de cliquer sur un des en-têtes de colonne afin de trier automatiquement l'affichage en fonction de cette colonne pourrait s'avérer intéressante.
En effet, si l'utilisateur souhaite prêter plus particulièrement son attention sur une catégorie d'information précise, cela pourrait lui être utile.

### Options lié à la pression d'une touche de clavier

Une autre idée d'implémentation est de proposer des options en fonction d'un bouton appuyé lorsque le programme est en cours de fonctionnement.

Imaginons par exemple les options suivantes :

- <kbd>F1</kbd> : Help
- <kbd>F2</kbd> : Mettre en pause / Reprendre
- <kbd>F3</kbd> : Afficher / Retirer les codes couleurs
- <kbd>F4</kbd> : Tri en fonction du meilleur temps au tour
- <kbd>F5</kbd> : Tri en fonction du meilleur temps au tour total
- <kbd>F10</kbd> : Quitter

### Phase d'essai entièrement libre

Par souci de facilité (et pour se concentrer sur d'autres parties nécessitant plus de temps et de travail), nous avons décidé que les voitures présentes lors d'une séance d'essai libre démarrent toutes comme s'il s'agissent d'une étape classique (une qualification ou une course).

Il serait possible, sans nécessairement y consacrer un temps considérable, de permettre aux différents pilotes de commencer et arrêter leurs séances d'essais libres lorsqu'ils le souhaitent voire même s'ils rouleront lors de la séance.
La question concrète serait : _Est-ce que lors de la limite du temps imparti d'une séance d'essais libres, un pilote souhaite prendre le volant ou non et si oui, pour combien de tours ou combien de temps?_

Cela correspondrait bien plus à une course de Formule 1 en condition réelle.

\pagebreak

Conclusion
=============

L'avantage de ce projet est l'application de concepts multiples vue en cours théorique au courant du premier quadrimestre.
Cela nous a permis de comprendre plus concrètement ce que ces concepts permettent de faire (allocation d'une zone mémoire, appel d'une zone mémoire, sémaphores, algorithmes, fork, etc.).

Lors de la première session, ce projet nous avait permis d'apprendre à programmer de façon plus assidue.
Lors de l'écriture d'une nouvelle méthode, nous testions systématiquement le projet et en cas de problème, nous prenions le temps de relire le code (et si nécessaire, nous testions différentes méthodes pour déboguer et avancer dans le projet).
Nous avions rencontré plusieurs difficultés de compréhension par rapport au cahier des charges ainsi que d'autres difficultés rencontrées, nous avions accumulé un retard par rapport au planning que nous avions fixé au départ, mais l'avions rattrapé en courant de quadrimestre.
Malheureusement, la programmation présentée ne correspondant et ne remplissant pas toutes les demandes, cela nous a entraînés dans une seconde tentative pour ce projet.

En cette seconde session, nous avons changé de méthodologie et avons porté une importance quasi capitale sur le fait de réaliser les tests de méthodes.
Nous avons appris de nos erreurs et avons eu des moments constructifs d'échange avec la professeur afin de réussir au mieux ce projet.
Nous avons également découvert l'utilité de l'utilisation de quelques librairies, ainsi que d'une documentation disponible en ligne, nous permettant de mieux comprendre certaines implémentations nécessaires.

\pagebreak
