### Mémoire partagée et communication entre processus

La mémoire partagée est un moyen efficace de transférer des données entre processus
indépendants. On crée ce dernier via les appels systèmes `shmget(...)`, `shmat(...)` et `shmdt(...)`. L’appel 
système `shmget(...)` permet de créer un segment de mémoire partagée. 

Le premier argument de `shmget(...)` est une clé qui identifie le segment de mémoire partagée, on fait ensuite appel 
à la fonction `shmat(...)` qui permet d’attacher un segment de mémoire partagée à un processus. Elle prend comme premier argument 
l’identifiant du segment de mémoire retourné par `shmget(...)`. Pour l'implémentation de ces appels systèmes voir le code 
en annexe dans le fichier **main.c**.  

La mémoire partagée contient un `struct` comportant les informations de secteurs entre autres choses.

```{.c caption="shared struct"}
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




