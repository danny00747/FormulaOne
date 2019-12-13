### Sémaphores 
 
 La notion de sémaphore est implémentée dans la plupart des systèmes d'exploitation. Il s'agit d'un concept fondamental 
 car il permet une solution à la plupart des problèmes d'exclusion.
 
 Un sémaphore est un mécanisme empêchant deux processus ou plus d'accéder simultanément à une ressource partagée.
 Sur les voies ferrées, un sémaphore empêche deux trains d'entrer en collision sur un tronçon de voie commune.
 Sur les voies ferrées comme dans les ordinateurs, les sémaphores ne sont qu'indicatifs : si un machiniste ne voit pas 
 le signal ou ne s'y conforme pas, le sémaphore ne pourra éviter la collision.
 
 De même si un processus ne teste pas un sémaphore avant d'accéder à une ressource partagée, le chaos peut en résulter.
 Un sémaphore binaire n'a que deux états:
 
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
