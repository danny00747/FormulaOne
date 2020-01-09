Évolutions futures
------------------

### Intégration de codes couleurs dans l'affichage : DONE ! 

Il s'agit certes d'une implémentation de moindre importance, mais on pense que cela pourrait s'avérer pratique pour 
ressortir de manière plus rapide les informations les plus importantes. On a donc réalisé un code couleur pour :


```{=latex}
\begin{awesomeblock}[white][\abShortLine]{0pt}{\faCheckCircle}{green}
```

- Les 3 premières places dans le classement
- Le temps au tour le plus rapide
- La ou les voiture(s) au stands
- La ou les voiture(s) ayant abandonné la course (OUT).

```{=latex}
\end{awesomeblock}
```

### Affichage cliquable : TODO !

Comme pour le tableaux généré par `htop` dans Linux, la possibilité de cliquer sur un des en-têtes de colonne afin de trier automatiquement 
l'affichage du tableau en fonction de cette colonne pourrait s'avérer intéressante.

### Options lié à la pression d'une touche de clavier : TODO !

Une autre idée d'implémentation est de proposer des options en fonction d'un bouton appuyé lorsque le programme est en cours 
de fonctionnement.

Imaginons par exemple les options suivantes :

```{=latex}
\begin{awesomeblock}[white][\abShortLine]{0pt}{\faThumbsUp}{blue}
```

- <kbd>F1</kbd> : Help
- <kbd>F2</kbd> : Mettre en pause / Reprendre
- <kbd>F3</kbd> : Afficher / Retirer les codes couleurs
- <kbd>F4</kbd> : Tri en fonction du meilleur temps au tour
- <kbd>F5</kbd> : Tri en fonction du meilleur temps au tour total
- <kbd>F6</kbd> : Tri en fonction du nom du pilote (id)
- <kbd>F10</kbd> : Quitter 

```{=latex}
\end{awesomeblock}
```

### Phase d'essai entièrement libre : TODO ! 

Il serait possible, sans nécessairement y consacrer un temps considérable, de permettre aux différents pilotes de 
commencer et arrêter leurs séances d'essais libres lorsqu'ils le souhaitent.
La question concrète serait : "Est-ce que lors de la limite du temps imparti d'une séance d'essais libres, un pilote souhaite 
prendre le volant ou non et si oui, pour combien de tours ou combien de temps?"

Cela correspondrait bien plus à une course de Formule 1 en condition réelle.

\pagebreak 
