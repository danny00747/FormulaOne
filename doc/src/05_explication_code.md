
Explication des particularités du code
--------------------------------------

### Fonctionnalités du code

Le programme prend en tant qu'arguments le nom d'une étape du week-end de Formule 1 ainsi que la longueur d'un tour en kilomètres.
Si ce dernier n'est pas fourni, une valeur par défaut est attribuée.

On lance la phase sélectionnée pour chacune des voitures participantes.
Lors de la simulation, les voitures participantes vont générer des temps aléatoires à chaque secteur.

Un tableau de valeurs reprenant des informations diverses est ensuite affiché afin de pouvoir suivre l'évolution de l'étape choisie.
Les informations représentée dans ce dernier dépendent de l'étape concernée.
Ce tableau est également trié en fonction du meilleur temps de tour par pilote ou, dans le cadre de la course, trié en fonction de leur position.

Au départ de la course, chaque participant démarre dans l'ordre précédemment déterminé par les séances de qualifications et 
avec une pénalité relative à leur position de départ.


Lorsque la simulation d'une étape est terminée, les positions des pilotes est sauvegardée dans un fichier.
Ce fichier sera chargé lors de l'étape suivante afin de déterminer les participants ainsi que leurs positions. 
