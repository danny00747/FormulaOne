### Sécurité du programme 

Pour éviter de rendre le code lourd on a décidé de rendre les séances d’essais libre. Càd on peut passer au P2 sans 
avoir exécuter P1. Par contre quand on passe au séances de qualifications surtout au Q2 et Q3, on a ajouté de la sécurité. 
Q2 sera jamais exécuter si Q1 n'a jamais été lancé car Q2 lit un fichier généré à la fin de Q1 afin de déterminer les 
participants ainsi que leurs positions. Si ce fichier n'est pas disponible le programme s'arrêter, également pour Q3 qui va 
jamais se lancer si le fichier Q2 est inexistant car Q3 dépend de Q2. Pour l'étape RACE, ce dernier dépend de 
plusieurs fichiers notamment Q3, les fichiers contenant les éliminés du Q1 et Q2. 

Il existe également un manuel (**_--help_** ) qui est affiché lorsque la commande passé comme arguments du programme est erroné afin 
d'éviter le crash du programme. Cela nous permet aussi de garantir que le programme se lancer uniquement si ce dernier a reçu correctement 
les arguments attendu. L'implémentation de tout cela voir le code en annexe dans le fichier **main.c**.  