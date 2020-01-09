Explication des particularités du code
--------------------------------------

### Fonctionnalités du code

Pour le paramétrage du programme, nous avons décidé d'utiliser un "parser" de ligne de commande via la 
fonction `getopt_long(...)` disponible avec GNU C. Elle permet d'avoir des noms longs d'option, commençant par deux tirets. 

::: tip
Voir code en annexe dans le fichier **main.c** pour l'implémentation.
::: 

Notre programme prend 4 options d'argument : 

```{=latex}
\begin{awesomeblock}[gray]{1pt}{\faCogs}{gray}  
```

1. L'option **_--day_** qui prend comme paramètre le nom du jour 
2. L'option **_--step_** qui prend comme paramètre le nom de l'étape 
3. L'option **_--length_** qui prend comme paramètre la longueur du circuit en kilomètre
3. L'option **_--help_** qui prend aucun paramètre, sert juste à afficher le manuel du programme.

```{=latex}
\end{awesomeblock}
```

```{=latex}
\begin{awesomeblock}[black]{1pt}{\faToggleOff}{green}  
```

Si l'option **_--length_** n'est pas fourni comme argument du programme, une valeur par défaut est attribuée. 

```{=latex}
\end{awesomeblock}
```

```{=latex}
\begin{awesomeblock}[white][\abLongLine][\textbf{Voici quelques exemples de lancement de notre programme avec des arguments}]
 {0pt}{\faCogs}{gray}
```

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
>>

> Pour avoir le manuel (help) :
>
>>
>>``` ./prog --help ``` ou ``` ./prog -h ``` 
>>

```{=latex}
\end{awesomeblock}
```

Concrètement en exécutant notre programme, on lance la phase sélectionnée pour chacune des voitures participantes.
Les voitures participantes vont alors générer des temps aléatoires pour chaque secteur, toutes les informations relatives à la 
voiture sont, à chaque tour, écrites dans la mémoire partagée.

Un tableau de valeurs reprenant des informations diverses est ensuite affiché afin de pouvoir suivre l'évolution de l'étape 
choisie en console. Les informations représentée dans ce dernier dépendent de l'étape concernée. Ce tableau est 
également trié en fonction du meilleur temps au tour par voiture ou, dans le cadre de la course, trié en fonction de leur position.

Au départ de la course, chaque participant démarre dans l'ordre précédemment déterminé par les séances de qualifications et 
avec une pénalité relative à leur position de départ.

Lorsque la simulation d'une étape est terminée, la position des pilotes dans le ranking est sauvegardée dans un fichier.
Ce fichier sera lu lors de l'étape suivante afin de déterminer les participants ainsi que leurs positions. 
