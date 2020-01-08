### Création et gestion des fichiers 

Pour avoir l’ordre sur la grille de départ lors de la course de dimanche, on passe par plusieurs étapes : 

1. _Enregistrement des fichiers Q1, Q2, Q3_

    Avant la terminaison du programme, on sauvegarde ces 3 fichiers car ils seront chargés lors de l'étape suivante 
    afin de déterminer les participants ainsi que leurs positions. La fonction `save_ranking(...)` permet de sauvegarder les 
    positions des voitures dans un fichier qui aura comme nom le nom de l'étape en cours d'exécution. 

2. _Lecture des fichiers Q1, Q2, Q3_

    L'étape suivante est de lire ces fichiers pour pouvoir classer les qualifiés et non qualifiés. Les non qualifiés au Q1 
    et Q2 sont d'abord mis dans un array puis finalement dans un fichier car on exit le programme après chaque étape 
    du week-end. La fonction `read_files(...)` permet de lire les 15 premiers lignes du fichier Q1 à l'étape Q2 
    pour pouvoir déterminer les participants ainsi que leurs positions. On fait la même chose à l'étape Q3 mais cette fois ci, ce sont
    les 10 premiers lignes du fichier Q2 qui sont lues afin de déterminer les participants. Finalement le fichier Q3 
    est lu avant le début de la course du dimanche.
    
3. _Lecture des fichiers lastQ1, lastQ2, Q3_
    
    Le fichier lastQ1 contient les 5 dernières voitures du Q1, lastQ2 contient les 5 dernières voitures du Q2. On utilise le 
    fichier Q3 généré à la fin de Q3 afin de déterminer les 10 premières positions sur la grille de départ. Les 
    autres places restant sont remplis grâce aux fichiers lastQ1 et lastQ2. Pour l'implémentation de ces 3 étapes voir 
    le code en annexe dans le fichier **files.c**. 
    
\pagebreak 