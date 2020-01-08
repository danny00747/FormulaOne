### Sémaphores 
 
Comme la mémoire partagée ne dispose d’aucun dispositif de synchronisation. Rien ne permet de veiller automatiquement 
à ce qu’un processus ne puisse commencer à lire la mémoire alors qu’un autre processus n’y a pas terminé son écriture; 
C’est donc à nous de régler ce problème de concurrence inter-processus.

Dans notre cas un processus fils peut être vu comme un "**rédacteur**" tandis que le processus père comme un "**lecteur**". 
Deux processus fils ne poserons jamais de problème de concurrence car ceux-ci écrivent dans une adresse mémoire différente. 
Il y a donc seulement un risque de concurrence si le père lit une adresse mémoire en cours d'écriture par un fils.
Pour résoudre ce problème, nous avons utilisé des sémaphores.

Il y a plusieurs variété de sémaphores, les sémaphores du System V et les sémaphores POSIX.
On peut encore différencier 2 type de sémaphore POSIX:
* **unnamed semaphores** 
* **named semaphores**
Nous avons décidé d'utilise des sémaphores POSIX de type **unnamed semaphores** disponibles dans la librairie standard C (GNU). 

Pour pouvoir utiliser un sémaphore, il faut d’abord l’initialiser. Cela se fait en 
utilisant la fonction `sem_init(...)` qui prend comme arguments :
* un pointeur vers le sémaphore à initialiser
* un flag 'pshared' indiquant si ce sémaphore sera partagé entre les threads d’un processus ou entre plusieurs processus 
* la valeur initiale du sémaphore

Les opérations `sem_wait(sem_t *sem)` et `sem_post(sem_t *sem)` permettent respectivement de verrouiller et déverrouiller une sémaphore. 
> Voir le code en annexe dans le fichier **main.c** pour l'implémentation de ces fonctions. 
 
