### Sécurité du programme 

Pour éviter de rendre le code trop lourd on a décidé de ne pas obliger l'utilisateur à lancer toutes les séances d'essais. On peut donc passer au P2 sans 
avoir exécuté P1. Par contre pour les séances de qualifications on a ajouté de la sécurité. 
Nous avons fait en sorte qu'une qualification ne puisse pas être lancée si la précédente n'a pas été lancée et terminée auparavant.
Q2 ne sera donc jamais exécuté avant Q1 tout comme Q3 ne sera jamais exécuté avant Q2 ou Q1. 
Il en va de même pour la course, celle-ci ne peut être lancée si les 3 qualifications ont été terminées.

Il existe également un manuel (**_--help_** ) qui est affiché lorsque la commande passé comme arguments du programme est erroné afin 
d'éviter le crash du programme. Cela nous permet aussi de garantir que le programme se lancer uniquement si ce dernier a reçu les arguments attendu.

> Voir le code en annexe dans le fichier **main.c** pour l'implémentation de la sécurité 

