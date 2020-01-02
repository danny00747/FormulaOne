### Sémaphores 
 
Comme la mémoire partagée ne dispose d’aucun dispositif de synchronisation. Rien ne permet de veiller automatiquement 
à ce qu’un processus ne puisse commencer à lire la mémoire alors qu’un autre processus n’y a pas terminé son écriture; 
c’est à nous de régler l’accès à cette ressource commune aux processus ayant accès à cette mémoire partagée.

Dans notre cas, la mémoire partagée n’est accédée ou modifiée qu’avec un seul « **écrivain** » et un seul « **lecteur** » 
à la fois; il n’y aura jamais plus d’une écriture et lecture en même temps. Ici, chaque processus fils est un écrivain 
alors que le lecteur est le processus père.

Il y a plusieurs variété de sémaphores, les sémaphores du System V et également les plus récents les sémaphores POSIX. 
La librairie POSIX comprend deux types; les **unnamed semaphores** & **named semaphores**. Dans notre projet on utilise 
les sémaphores POSIX de type **unnamed semaphores** qui sont disponibles dans la librairie standard C (GNU). 

La glibc (GNU C Library) offre donc une implémentation des sémaphores. Ces derniers nous permettent de garantir l’accès 
exclusif à la mémoire partagée. Pour pouvoir utiliser un sémaphore, il faut d’abord l’initialiser. Cela se fait en 
utilisant la fonction `sem_init` qui prend comme premier argument un pointeur vers le sémaphore à initialiser, deuxième 
argument pshared indique si ce sémaphore sera partagé entre les threads d’un processus ou entre processus. 
Si pshared vaut 0, le sémaphore est partagé entre les threads d’un processus si non c’est entre les processus. 
Enfin, le troisième argument value spécifie la valeur initiale du sémaphore.

Les opérations `sem_wait(sem_t *sem)` et `sem_post(sem_t *sem)` permettent respectivement de 
verrouiller et déverrouiller une sémaphore. Pour l'implémentation de ces fonctions voir le code en annexe dans 
le fichier **main.c**.  
 
