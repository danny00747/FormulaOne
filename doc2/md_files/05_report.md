
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

Au départ de la course, chaque participant démarre dans l'ordre précédemment déterminé par les séances de qualifications et 
avec une pénalité relative à leur position de départ.

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

Sous Linux, la mémoire partagée peut s’utiliser via les appels systèmes `shmget`, `shmat` et `shmdt`. 
L’appel système `shmget` permet de créer un segment de mémoire partagée. Le premier argument de `shmget` est une clé 
qui identifie le segment de mémoire partagée. Cette clé est en pratique encodée sous la forme d’un entier qui 
identifie le segment de mémoire partagée. Elle sert d’identifiant du segment de mémoire partagée dans le noyau. 
Un processus doit connaître la clé qui identifie un segment de mémoire partagée pour pouvoir y accéder. 
On utilise la clé IPC_PRIVATE pour la création de ce dernier. Le deuxième argument de `shmget` donne le nombre d’octets 
du segment. Enfin, le troisième argument est une combinaison (par OU bit à bit) de constantes 
(telles que IPC_CREAT pour la création) et de droits d’accès (comme 0666). Par exemple pour créer un segment on utilisera 
typiquement l’option IPC_CREAT|0666, et pour l’acquisition simplement 0666.

```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg);
```

L’appel système `shmget` retourne un entier qui identifie le segment de mémoire partagée à l’intérieur du processus 
si il réussit et -1 sinon. Il est important de noter que si l’appel à`shmget` réussit, cela indique que le processus 
dispose des permissions pour accéder au segment de mémoire partagée, mais à ce stade il n’est pas accessible depuis la table 
des pages du processus. 

```c
F1_Car *car;
  int struct_shm_id = shmget(IPC_PRIVATE, sizeof(F1_Car) * circuit.number_of_cars, 0600 | IPC_CREAT);
    if (struct_shm_id == -1) {
        perror("shmget failed !");
        exit(EXIT_FAILURE);
    }
```

Cette modification à la table des pages du processus se fait en utilisant `shmat`. Cet appel 
système permet d’attacher un segment de mémoire partagée à un processus. Il prend comme premier argument l’identifiant 
du segment de mémoire retourné par `shmget`. Le deuxième argument est un pointeur vers la zone mémoire via laquelle le segment 
doit être accessible dans l’espace d’adressage virtuel du processus. Généralement, c’est la valeur NULL qui est spécifiée 
comme second argument et le noyau choisit l’adresse à laquelle le segment de mémoire est attaché dans le processus. 
Il est aussi possible de spécifier une adresse dans l’espace d’adressage du processus. Le troisième argument permet, 
en utilisant le drapeau SHM_RDONLY, d’attacher le segment en lecture seule ou 0 pour un segment en lecture/écriture. 
`shmat` retourne l’adresse à laquelle le segment a été attaché en cas de succès et (void *) -1 en cas d’erreur.

```c
#include <sys/types.h>
#include <sys/shm.h>

void *shmat(int shmid, const void *shmaddr, int shmflg);
```
```c
   car = shmat(struct_shm_id, NULL, 0);
    if (car == (void *) (-1)) {
        perror("shmat failed !");
        exit(EXIT_FAILURE);
    }
```

### Sémaphores 

La notion de sémaphore est implémentée dans la plupart des systèmes d'exploitation. Il s'agit d'un concept fondamental 
car il permet une solution à la plupart des problèmes d'exclusion.

Un sémaphore est un mécanisme empêchant deux processus ou plus d'accéder simultanément à une ressource partagée.
Sur les voies ferrées, un sémaphore empêche deux trains d'entrer en collision sur un tronçon de voie commune.
Sur les voies ferrées comme dans les ordinateurs, les sémaphores ne sont qu'indicatifs : si un machiniste ne voit pas 
le signal ou ne s'y conforme pas, le sémaphore ne pourra éviter la collision.

De même si un processus ne teste pas un sémaphore avant d'accéder à une ressource partagée, le chaos peut en résulter.
Un sémaphore binaire n'a que deux états :

- 0 verrouillé (ou occupé).
- 1 déverrouillé (ou libre).

Quand il vaut zéro, un processus tentant de l'acquérir doit attendre qu'un autre processus ait augmenté sa valeur 
car le sémaphore ne peut jamais devenir négatif. Dans le cas de notre projet on utilise les sémaphores POSIX qui sont disponibles 
dans la librairie standard C (GNU). La glibc offre donc une implémentation des sémaphores.

Dans notre projet on utilise les fonctions suivantes de la librairie pour gérer un sémaphore de type `sem_t` : 

```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_destroy(sem_t *sem);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
```

Pour pouvoir utiliser un sémaphore, il faut d’abord l’initialiser. Cela se fait en utilisant la fonction `sem_init`
qui prend comme premier argument un pointeur vers le sémaphore à initialiser, deuxième argument pshared indique si ce 
sémaphore sera partagé  entre les threads d'un processus ou entre processus. Si pshared vaut 0, le sémaphore est partagé entre 
les threads d'un processus si non c'est entre les processus. Enfin, le troisième argument value spécifie la valeur 
initiale du sémaphore. 

Les deux principales fonctions de manipulation des sémaphores sont `sem_wait` et `sem_post`. 

- `sem_wait()` décrémente (verrouille) le sémaphore pointé par sem. Si la valeur du sémaphore est plus grande que 0,
la décrémentation s'effectue et la fonction revient immédiatement. Si le sémaphore vaut zéro, l'appel bloquera jusqu'à 
ce que soit il devienne disponible pour effectuer la décrémentation (c'est-à-dire la valeur du sémaphore n'est plus nulle), 
soit un gestionnaire de signaux interrompe l'appel.

- `sem_post()` incrémente (déverrouille) le sémaphore pointé par sem. Si, à la suite de cet incrément, la valeur du sémaphore 
devient supérieure à zéro, un autre processus ou thread bloqué dans un appel `sem_wait()` sera réveillé et procédera 
au verrouillage du sémaphore.

Ces deux opérations sont bien entendu des opérations qui ne peuvent s’exécuter simultanément. Leur implémentation 
réelle comprend des sections critiques qui doivent être construites avec soin. La section critique dans notre projet est lors 
de l'affichage. 

```c
#include <semaphore.h>

sem_t *sem;

sem_init(sem, 1, 1);

sem_wait(sem);
// section critique : affichage voir le code dans le fichier display.c 
sem_post(sem);

sem_destroy(sem);
```

### Libération des ressources de l'ordinateur

Afin de libérer les ressources de l'ordinateur, plusieurs étapes sont réalisées une fois que les processus 
enfants ont terminé leur fonction et que le programme est prêt à quitter.

Premièrement, il y a "détachement" de la mémoire partagée et ensuite ce dernier est supprimée. 

L’appel système `shmdt` permet de détacher un segment de mémoire qui avait été attaché en utilisant `shmat`. 
L’argument passé à `shmdt` doit être l’adresse d’un segment de mémoire attaché préalablement par `shmat`. 
Lorsqu’un processus se termine, tous les segments auxquels il était attaché sont détachés lors de l’appel à `exit`. 

Détacher la mémoire partagée ne la supprime pas. Détacher la mémoire partagée permet juste de casser la correspondance 
entre les pages de l'espace virtuel dédiées au segment  de mémoire et les pages frames de la mémoire physique dédiées 
au segment de mémoire partagée. Pour réellement la mémoire partagée on fait appel à la fonction `shmctl`. 

L’appel système `shmctl` prend trois arguments. Le premier est un identifiant de segment de mémoire partagée retourné 
par `shmget`. Le deuxième est une constante qui spécifie une commande. On utilise uniquement la commande IPC_RMID 
qui permet de retirer le segment de mémoire partagée dont l’identifiant est passé comme premier argument. Si il n’y a plus 
de processus attaché au segment de mémoire partagée, celui-ci est directement supprimé. Sinon, il est marqué de façon à ce 
que le noyau retire le segment dès que le dernier processus s’en détache. `shmctl` retourne 0 en cas de succès et -1 en 
cas d’échec.

```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmdt(const void *shmaddr);
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

Deuxièmement, on fait presque la même chose avec les sémaphores mais avec des fonctions différentes. La fonction `sem_destroy` 
permet de libérer un sémaphore qui a été initialisé avec `sem_init`. Les sémaphores consomment des ressources qui peuvent 
être limitées dans certains environnements. Il est important de détruire proprement les sémaphores dès qu’ils ne sont plus 
nécessaires.

```c
shmdt(car);
shmctl(struct_shm_id, IPC_RMID, NULL);
sem_destroy(sem);
```

### Création et gestion des processus

Chaque voiture correspond à un processus fils, tandis que le père s'occupe de la gestion des étapes et de l'affichage.

La création des processus se fait par la fonction `fork`, faisant partie des appels système POSIX. Elle permet de donner 
naissance à un nouveau processus qui est sa copie.

La création des processus fils est présent dans le fichier de code source `main.c`.

### Rôle du processus père

Dans notre cas, nous avons un processus père donnant naissance au nombre de processus fils nécessaire à l'étape choisie.
Chaque processus fils représente une voiture.

Le processus père, quant à lui, va lire des informations provenant de la mémoire partagée.
Il s'occupe également de l'affichage ainsi que du tri tout comme la sauvegarde des informations sur fichier.

### Rôle des processus fils

Dans le cadre de ce projet, les fils sont seulement chargés à courir. Càd exécuter les étapes à faire pour un week-end complet d’un 
grand prix de Formule 1. Pour y arriver on utilise une boucle `while()` avec comme condition si le temps de l'étape chosi n'a
pas écoulé, alors les fils courent. Pour la course de dimanche les fils courent tant qu'ils n'ont pas fini les tours à faire. Les crash
sont gérés à l'interieur du la boucle `while()`. 

Le code du fils est présent dans le fichier de code source `child.c`. 


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
