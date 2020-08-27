### Libération des ressources de l'ordinateur

Afin de libérer les ressources de l'ordinateur, deux étapes sont réalisées une fois que les processus 
enfants ont terminés leur fonction et que le programme est prêt à quitter.

**I. Détachement" de la mémoire partagée et suppression de celui-ci**

::: note 

L’appel système `shmdt(...)` permet de détacher un segment de mémoire qui avait été attaché en utilisant `shmat(...)`. 
L’argument passé à `shmdt(...)` est l’adresse d’un segment de mémoire. 
Lorsqu’un processus se termine, tous les segments auxquels il était attaché sont détachés lors de l’appel `exit(...)`. 

\medskip

Néanmoins, détacher la mémoire partagée ne la supprime pas. Détacher la mémoire partagée permet juste de casser la correspondance 
entre les pages de l'espace virtuel dédiées au segment de mémoire et les pages frames de la mémoire physique dédiées 
au segment de mémoire partagée. Pour réellement supprimer la mémoire partagée on fait appel à la fonction `shmctl(...)`. 

::: 

L’appel système `shmctl(...)` prend trois arguments :

::: note

1. un identifiant de segment de mémoire partagée (retourné par `shmget(...)`). 
2. le deuxième est une constante qui spécifie une commande. On utilise uniquement la commande _IPC_RMID_ qui 
    permet de retirer le segment de mémoire partagée dont l’identifiant est passé comme premier argument.
3. le troisième est un pointeur _buf_ sur une structure paratagée. Avec la commande _IPC_RMID_, buf pourra être positionné à 
   NULL dans ce cas. 
   
::: 

Si il n’y a plus de processus attaché au segment de mémoire partagée, celui-ci est directement supprimé. Sinon, il est marqué de 
façon à ce que le noyau retire le segment dès que le dernier processus s’en détache. `shmctl(...)` retourne 0 en cas de succès et -1 
en cas d’échec.

**II. Suppression des sémaphore**

La fonction `sem_destroy(...)` permet de libérer un sémaphore qui a été initialisé avec `sem_init(...)`. Les sémaphores consomment 
des ressources qui peuvent être limitées dans certains environnements. Il est important de détruire proprement les sémaphores 
dès qu’ils ne sont plus nécessaires. 

::: tip

L'implémentation de ces fonctions bous permettant de libérer des ressources se trouve en annexe dans 
le fichier **main.c**. 

:::
