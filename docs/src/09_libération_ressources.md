### Libération des ressources de l'ordinateur

Afin de libérer les ressources de l'ordinateur, plusieurs étapes sont réalisées une fois que les processus 
enfants ont terminé leur fonction et que le programme est prêt à quitter.

Premièrement, il y a "détachement" de la mémoire partagée et ensuite ce dernier est supprimée. 

L’appel système `shmdt` permet de détacher un segment de mémoire qui avait été attaché en utilisant `shmat`. 
L’argument passé à `shmdt` doit être l’adresse d’un segment de mémoire attaché préalablement par `shmat`. 
Lorsqu’un processus se termine, tous les segments auxquels il était attaché sont détachés lors de l’appel à `exit`. 

Détacher la mémoire partagée ne la supprime pas. Détacher la mémoire partagée permet juste de casser la correspondance 
entre les pages de l'espace virtuel dédiées au segment  de mémoire et les pages frames de la mémoire physique dédiées 
au segment de mémoire partagée. Pour réellement supprimer la mémoire partagée on fait appel à la fonction `shmctl`. 

L’appel système `shmctl` prend trois arguments. Le premier est un identifiant de segment de mémoire partagée retourné 
par `shmget`. Le deuxième est une constante qui spécifie une commande. On utilise uniquement la commande IPC_RMID 
qui permet de retirer le segment de mémoire partagée dont l’identifiant est passé comme premier argument. Si il n’y a plus 
de processus attaché au segment de mémoire partagée, celui-ci est directement supprimé. Sinon, il est marqué de façon à ce 
que le noyau retire le segment dès que le dernier processus s’en détache. `shmctl` retourne 0 en cas de succès et -1 en 
cas d’échec.

```{.c caption="man of shmdt and shmctl"}
#include <sys/ipc.h>
#include <sys/shm.h>

int shmdt(const void *shmaddr);
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

Deuxièmement, on fait presque la même chose avec les sémaphores mais avec des fonctions différentes. La fonction `sem_destroy` 
permet de libérer un sémaphore qui a été initialisé avec `sem_init`. Les sémaphores consomment des ressources qui peuvent 
être limitées dans certains environnements. Il est important de détruire proprement les sémaphores dès qu’ils ne sont plus 
nécessaires.

```{.c caption="destruction des semaphores"}
shmdt(car);
shmctl(struct_shm_id, IPC_RMID, NULL);
sem_destroy(sem);
``` 
