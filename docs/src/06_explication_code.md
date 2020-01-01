Explication des particularités du code
--------------------------------------

### Fonctionnalités du code


Pour le paramétrage du programme, nous avons décider d'utiliser un parser la ligne de commande avec la 
fonction `getopt_long` disponible avec GNU C. Elle permet d'avoir des noms longs d'option, commençant par deux tirets. 
Pour l'implémentation voir le code en annexe dans le fichier **main.c**. 

Notre programme prend en tant qu'arguments 4 options : 

1. L'option **--day** qui prend comme paramètre le nom du jour 
2. L'option **--step** qui prend comme paramètre le nom de l'étape 
3. L'option **--length** qui prend comme paramètre la longueur d'un tour en kilomètre
3. L'option **--help** qui prend aucun paramètre, sert juste à afficher le manuel du programme.

Si l'option **--length** n'est pas fourni comme argument du programme, une valeur par défaut est attribuée.

> Lors des séances d’essais (P1, P2, P3) :
>
>>
>>``` ./prog --day fri --step P2```
>>

> Lors des qualifications (Q1, Q2, Q3) :
>
>>
>>``` ./prog --day sat --step Q3```
>>

> Lors de la course (RACE) :
>
>>
>>``` ./prog --day sun --step RACE --length 10 ```
>>
>>``` ./prog -d sun -s RACE -l 10 ```
>>

> Pour avoir le manuel (help) :
>
>>
>>``` ./prog --help ``` ou ``` ./prog -h ``` 
>>

On lance la phase sélectionnée pour chacune des voitures participantes qui vont courir pendant un temps définit.
Lors de la simulation, les voitures participantes vont générer des temps aléatoires à chaque secteur et ces données 
sont écrites dans la mémoire partagée.

Un tableau de valeurs reprenant des informations diverses est ensuite affiché afin de pouvoir suivre l'évolution 
de l'étape choisie. Les informations représentée dans ce dernier dépendent de l'étape concernée. Ce tableau est 
également trié en fonction du meilleur temps de tour par pilote ou, dans le cadre de la course, trié en fonction de 
leur position.

Au départ de la course, chaque participant démarre dans l'ordre précédemment déterminé par les séances de qualifications et 
avec une pénalité relative à leur position de départ.

Lorsque la simulation d'une étape est terminée, les positions des pilotes est sauvegardée dans un fichier.
Ce fichier sera chargé lors de l'étape suivante afin de déterminer les participants ainsi que leurs positions. 
