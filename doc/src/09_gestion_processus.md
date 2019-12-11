### Création et gestion des processus

Chaque voiture correspond à un processus fils, tandis que le père s'occupe de la gestion des étapes et de l'affichage.

La création des processus se fait par la fonction `fork`, faisant partie des appels système POSIX. Elle permet de donner 
naissance à un nouveau processus qui est sa copie.

La création des processus fils est présent dans le fichier de code source `main.c`.

**Rôle du processus père**

Dans notre cas, nous avons un processus père donnant naissance au nombre de processus fils nécessaire à l'étape choisie.
Chaque processus fils représente une voiture.


Le processus père, quant à lui, va lire des informations provenant de la mémoire partagée.
Il s'occupe également de l'affichage ainsi que du tri tout comme la sauvegarde des informations sur fichier des étapes de 
qualifications et de la course. 

**Rôle des processus fils**

Dans le cadre de ce projet, les fils sont seulement chargés à courir. Càd exécuter les étapes à faire pour un week-end complet d’un 
grand prix de Formule 1. Pour y arriver on utilise une boucle `while()` avec comme condition si le temps de l'étape chosi n'a
pas écoulé, alors les fils courent. Pour la course de dimanche les fils courent tant qu'ils n'ont pas fini les tours à faire. Les crash
sont gérés à l'interieur du la boucle `while()`. 

Le code du fils est présent dans le fichier de code source `child.c`. 

**Affichage**

Pour pouvoir les données dans table, on utilise une librairie public `libfort` disponible sur github : <https://github.com/seleznevae/libfort>. Voilà un exemple du résultat lors de l'étape Q2. 

| Position | NAME |   S1   |   S2   |   S3   | OUT | PIT | LAP | LAP TIME  | BEST LAP TIME |
|----------|------|--------|--------|--------|-----|-----|-----|-----------|---------------|
| 1        |  7   | 32":03 | 39":03 | 44":77 |  0  |  0  |  13 | 1':02":19 |   1':19":42   |
| 2        |  35  | 42":53 | 41":27 | 39":23 |  0  |  1  |  9  | 1':11":71 |   1':22":31   |
| 3        |  40  | 36":13 | 30":03 | 44":12 |  0  |  0  |  16 | 1':03":36 |   1':44":28   |
| 4        |  40  | 40":04 | 43":03 | 43":03 |  0  |  0  |  10 | 1':40":11 |   1':51":47   |
| 5        |  77  | 33":11 | 34":43 | 42":59 |  0  |  1  |  11 | 1':17":23 |   2':12":73   |

Il y a également une deuxième table pour savoir qui a le meilleur temps dans chacun des secteurs. 

| SECTOR | NAME |  TIME  |   
|--------|------|--------|
|   S1   |  3   | 31":03 | 
|   S2   |  42  | 33":27 | 
|   S3   |  36  | 38":44 | 

Le code de la création de ces deux tables est présent dans le fichier de code source `display.c`. 

**Le trie**

Pour pouvoir classer les voitures en fonction de leur tour complet le plus rapide, ou en fonction de leur rapididté lors 
la course, on utilise la fonction de la librairie `qsort`. 

```c
void qsort(void *base, size_t nel, size_t width,
           int (*compar)(const void *, const void *));
```

Le premier est un pointeur vers le début de la zone mémoire à trier. Le second est le nombre d’éléments à trier. 
Le troisième contient la taille des éléments stockés dans le tableau. Le quatrième argument est un pointeur vers la fonction 
qui permet de comparer deux éléments du tableau. Cette fonction retourne un entier négatif si son premier argument est 
inférieur au second et positif ou nul sinon. 

Les deux arguments de type `(const void *)` font appel à l’utilisation de pointeurs `(void *)` qui est nécessaire car la fonction doit 
être générique et pouvoir traiter n’importe quel type de pointeurs. `(void *)` est un pointeur vers une zone quelconque de mémoire 
qui peut être casté vers n’importe quel type de pointeur par la fonction de comparaison. Le qualificatif const indique que la 
fonction n’a pas le droit de modifier la donnée référencée par ce pointeur, même si elle reçoit un pointeur vers cette donnée. 
On retrouve régulièrement cette utilisation de const dans les signatures des fonctions de la librairie pour spécifier des 
contraintes sur les arguments passés à une fonction.

Un exemple de fonction de comparaison est la fonction `strcmp` de la librairie 
standard. Le pseudo-code repris ci-dessous est notre implémentation de la fonction `qsort`. 

```c
int compare(const void *left, const void *right) {
    const F1_Car *process_a = (F1_Car *) left;
    const F1_Car *process_b = (F1_Car *) right;

    if (strcmp(circuit.step_name, "RACE")) {
        if (process_a->best_lap_time < process_b->best_lap_time)
            return -1;
        else if (process_a->best_lap_time > process_b->best_lap_time)
            return 1;
        else
            return 0;
    } else {
        if (process_a->lap < process_b->lap)
            return 1;
        else if (process_a->lap > process_b->lap)
            return -1;
        else
            return 0;
    }
}

sem_wait(sem);
memcpy(car_array, data, sizeof(F1_Car) * circuit.number_of_cars); 
sem_post(sem);
qsort(car_array, circuit.number_of_cars, sizeof(F1_Car), compare);
```

Avant de trier on fait une copie des données du struct partagée entre les processus par la fonction `memcpy`. Cette fonction permet de copier 
un bloc de mémoire spécifié par le paramètre source, et dont la taille est spécifiée via le paramètre size, dans un nouvel 
emplacement désigné par le paramètre destination. Il est bien entendu qu'il est de notre responsabilité d'allouer suffisamment 
de mémoire pour le bloc de destination afin qu'il puisse contenir toutes les données.

Le code sur qui permet de gérer les trie est présent dans le fichier de code source `display.c`. 

\pagebreak 
