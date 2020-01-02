### Création et gestion des fichiers 

Pour avoir l’ordre sur la grille de départ lors de la course de dimanche, on passe par plusieurs étapes : 

1. _Enregistrement des fichiers Q1, Q2, Q3_

    Avant la terminaison du programme, on sauvegarde ces 3 fichiers car ils seront chargés lors de l'étape suivante 
    afin de déterminer les participants ainsi que leurs positions. La fonction `save_ranking()` permet de sauvegarder les 
    positions des pilotes dans un fichier qui aura comme nom le nom de l'étape en cours d'exécution. 

2. _Lecture des fichiers Q1, Q2, Q3_

    L'étape suivante est de lire ces fichiers pour pouvoir classer les qualifiés et non qualifiés. Les non qualifiés au Q1 
    et Q2 sont d'abord mis dans un array puis finalement dans un fichier car on exit le programme après chaque étape 
    du week-end de Formule 1. La fonction `read_files()` permet de lire les 15 premiers lignes du fichier Q1 à l'étape Q2 
    pour pouvoir déterminer les participants ainsi que leurs positions. On fait la même chose à l'étape Q3 mais ici, c'est
    les 10 premiers lignes du fichier Q2 qui sont lus afin de déterminer ses participants. Et finalement le fichier Q3 
    est lu avant que la course de dimanche démarrer.
    
3. _Lecture des Q1, Q2,Q3_

\pagebreak 