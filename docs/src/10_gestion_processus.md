### Création et gestion des processus

Chaque voiture correspond à un processus fils, tandis que le père s'occupe de la gestion des étapes.

La création des processus se fait par la fonction `fork()`, faisant partie des appels système POSIX. Elle permet de donner 
naissance à un nouveau processus qui est une copie du programme au moment de l'appel.

::: tip
Voir le code en annexe dans le fichier **main.c** pour la création des processus fils. 
::: 

**I. Rôle du processus père**

Dans notre cas, nous avons un processus père qui donne naissance à un nombre de processus fils en fonction de l'étape choisie.

Le processus père est chargé de lire les données stockées en mémoire partagée.
Il s'occupe également du tri des voitures ainsi que de l'affichage.
En fin de session, il sauvegarde les informations dans les fichiers correspondant.  

**II. Rôle des processus fils**

Les fils sont seulement chargés de "courir". C'est à dire, d'exécuter les étapes d'un week-end complet de
grand prix de Formule 1. Pour ce faire nous avons utilisé une boucle `while(...)` qui tourne tant que la voiture n'a pas 
dépassé le temps de session autorisé ou, si nous sommes en course, tant que la voiture n'a pas fait les X tours de circuit demandé. 

Le nombre de tours à faire est déterminé par la longueur du circuit qui varie en fonction l'option **_--length_** passé 
en argument du programme. Si ce dernier n'est pas fourni une valeur par défaut de 7km lui est attribuée. 

::: tip
Le code du fils se trouve dans le fichier **child.c**. 
::: 

**III. Affichage**

Pour pouvoir afficher les données proprement dans un tableaux, nous avons utilisé la librairie public **libfort** disponible sur 
github : <https://github.com/seleznevae/libfort>. Voici un exemple du tableau des résultats lors de l'étape Q2. 

| Position | NAME |   S1   |   S2   |   S3   | OUT | PIT | LAP | LAP TIME  | BEST LAP TIME |
|----------|------|--------|--------|--------|-----|-----|-----|-----------|---------------|
| 1        |  7   | 32":03 | 39":03 | 44":77 |  0  |  0  |  13 | 1':02":19 |   1':19":42   |
| 2        |  35  | 42":53 | 41":27 | 39":23 |  0  |  1  |  9  | 1':11":71 |   1':22":31   |
| 3        |  40  | 36":13 | 30":03 | 44":12 |  0  |  0  |  16 | 1':03":36 |   1':44":28   |
| 4        |  40  | 40":04 | 43":03 | 43":03 |  0  |  0  |  10 | 1':40":11 |   1':51":47   |
| 5        |  77  | 33":11 | 34":43 | 42":59 |  0  |  1  |  11 | 1':17":23 |   2':12":73   |

Table:  Table des résultats.

```{=latex}
\begin{awesomeblock}[gray]{1pt}{\faGrin*[regular]}{gray}   
```

Pour les colonnes de "_secteurs, lap time et best lap time_", les données utilisé dans notre programme sont des entiers.
Afin de rendre les choses plus lisible, nous les avons converties vers un format temporel. 
 
```{=latex}
\end{awesomeblock}
```

Nous avons également un deuxième tableau affichant le meilleur temps de chaque secteur ainsi que la voiture qui l'a fait. 

Table:  Table de meilleur temps dans chacun des secteurs.

| SECTOR | NAME |  TIME  |   
|--------|------|--------|
|   S1   |  3   | 31":03 | 
|   S2   |  42  | 33":27 | 
|   S3   |  36  | 38":44 | 

::: tip
Voir le code en annexe dans le fichier **display.c** pour l'implémentation de ces tableaux. 
:::
**IV. Le tri du classement**

Avant de trier on fait une copie des données de la mémoire partagée par le biais de la fonction `memcpy(...)`. Cette fonction 
permet de copier un bloc de mémoire spécifié par le paramètre source, et dont la taille est spécifiée via le paramètre size, 
dans un nouvel emplacement désigné par le paramètre destination. Il faut évidemment allouer suffisamment de mémoire pour le bloc 
de destination afin que celui-ci puisse contenir toutes les données.

Pour pouvoir classer les voitures en fonction de leur tour le plus rapide, ou en fonction de leur position par rapport aux autres,
on utilise la fonction de la librairie `qsort(...)`. 

```{.c caption="man of qsort"}
void qsort(void *base, size_t nel, size_t width,
           int (*compar)(const void *, const void *));
```

Voici une petite explication des arguments de cette fonction:

::: note
Argument n° :

1. un pointeur vers le début de la zone mémoire à trier
2. le nombre d’éléments à trier
3. la taille des éléments stockés dans le tableau
4. un pointeur vers la fonction permettant de comparer deux éléments du tableau. Cette fonction retourne un entier négatif si 
    son premier argument est inférieur au second et positif ou nul sinon. 
5. les paramètres suivant sont expliqué ci-dessous
::: 

```{=latex}
\begin{awesomeblock}[white][\abShortLine][\textbf{Les const de qsort}]{0pt}{\faBookReader}{black}
```
Les deux paramètres de type `(const void *)` font appel à l’utilisation de pointeurs `(void *)` qui sont nécessaire car 
la fonction doit être générique et pouvoir traiter n’importe quel type de pointeurs. `(void *)` est un pointeur vers 
une zone quelconque de mémoire qui peut être casté vers n’importe quel type de pointeur par la fonction de comparaison. 
\newline \newline 
Le qualificatif `const` indique que la fonction n’a pas le droit de modifier la donnée référencée par ce pointeur, 
même si elle reçoit un pointeur vers cette donnée. On retrouve régulièrement cette utilisation de `const` dans 
les signatures des fonctions de la librairie pour spécifier des contraintes sur les arguments passés à une fonction.

```{=latex}
\end{awesomeblock}
```

::: tip
Voir le code en annexe dans le fichier **display.c** pour l'implémentation de ces fonctions. 
:::
\pagebreak 
