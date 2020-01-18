Analyse du travail
------------------

### Plan du programme 

Afin d'améliorer notre rapport, nous avons retenu les remarques faites par la professeur lors d'une séance de TP. 
Suite à ce dernier, nous avons décidé de commencer par décortiquer les demandes et en faire un flowchart afin 
de mieux visualiser le projet : 

\begin{figure}[H]
\centering
\caption{Flowchart}
\includegraphics[scale=0.25]{imgs/inkscape-pic-of-plantuml.png}
\end{figure}

Malheureusement vu la taille du l'image, on était obligé de l'imprimer à part sur une feuille A3 qui se trouve en annexe 
du rapport. Comme vous pouvez le voir sur l'image le projet est divisé en 3 parties. Vendredi, samedi et dimanche. 
P1 et P2 sont exécutés le vendredi, samedi on a les étapes suivantes : P3, Q1, Q2, Q3 et afin dimanche on a la course finale.

Pour une question de sécurité si le nom du jour passé en argument du programme est ni vendredi ni samedi ni dimanche, 
le programme affiche le manuel d'utilisation en console et s'arrêter. 
 
### Découpage en plusieurs fichiers 

```{=latex}
\begin{awesomeblock}[white][\abShortLine][\textbf{Tous les fichiers C du projet }] 
{5pt}{\faFileCode}{purple}
```

\begin{figure}[H]
\centering
\caption{Structure des fichiers}
\includegraphics[scale=0.6]{imgs/files-struct.png}
\end{figure}

```{=latex}
\end{awesomeblock}
```

Pour simplifier le projet, nous avons décidé de découper ce dernier en plusieurs fichiers au lieu d'avoir tout le code dans un 
seul fichier. Nous avons **7 fichiers** C qui communiquent entre eux pour produire un exécutable. Le fait d'avoir découpé le 
code en plusieurs fichiers nous a beaucoup aidé lors du débogage des problèmes rencontrés au fur à mesure de notre avancement.

### Fichiers principaux 

::: important

Sans surprise, le fichier le plus important est le fichier **main.c**. C'est dans ce dernier qu'on trouve la création 
de la mémoire partagée, des sémaphores, paramétrage du programme et également la création des fils/voitures qui participeront 
au Grand Prix. Le fichier **display.c**. sert principalement à afficher les données triées en console. 
\newline \newline 
Le fichier **child.c** contient quant à lui tout ce qui est propre à une voiture. C'est dans ce fichier que la voiture va "s'exécuter" 
une fois créée par le `fork()` du **main.c**. Finalement on a aussi un fichier **files.c** qui se charge de la creation, écriture 
et lecture des fichiers texte contenant les données des classements après chaque session. 

:::
 
### Description de la méthode de travail 

Premièrement, nous avons décidé de travailler avec un logiciel de gestion de version connu sous le nom de 
**_git_**. Ce type de logiciel est devenu indispensable lorsqu’on travaille à plusieurs sur un même projet et donc sur 
le même code source. 

Cela nous a permit deux choses : 

```{=latex}
\begin{awesomeblock}[orange]{1.7pt}{\faGit*}{orange} 
```

 1. **suivre l’évolution du code source**, pour retenir les modifications effectuées sur chaque fichier et être 
   ainsi capable de revenir en arrière en cas de problème. 
\newline 
 2. **travailler à plusieurs**, sans risquer de se marcher sur les pieds. Si deux personnes modifient un même fichier en même 
   temps, leurs modifications doivent pouvoir être fusionnées sans perte d’information.
   
```{=latex}
\end{awesomeblock}
```

On a remarqué au début du projet qu'il était primordiale d'avoir d'abord une voiture qui tourne et affiche convenablement les données 
en console avant d'en avoir 20 qui tournent en même temps. Du coup on a commencé par créer le fichier **child.c** pour 
générer aléatoirement le temps secteurs, le temps passé au stand etc...

Une fois qu'on avait une voiture qui tournait correctement, on est passé à l'étape suivante l'affichage. On a décidé de 
représenter les données en console sous forme d'une table. Il existe plusieurs librairies qui permettent d'avoir une 
table en console mais la plupart ne supportent pas le rafraîchissement. L'un de plus gros challenge rencontré était le rafraîchissement 
des données dans une table en console. On a fini par utiliser une librairie disponible sur github sous le nom 
de **libfort** ([lien](https://github.com/seleznevae/libfort "github de libfort")) et quelques commandes bash qu'on a dû convertir 
en langage C.

Après avoir réussi à obtenir une voiture qui tournait correctement et un affichage qui nous convenait, on est passé 
à la création de la mémoire partagée. Évidemment créer cette dernière sans avoir au moins 2 processus qui tournent n'a pas de 
de sens. On est resté bloqué sur la mémoire partagée pendant plusieurs semaines. 

```{=latex}
\begin{awesomeblock}[white][\abShortLine][\textbf{Quelquels problèmes rencontrés}]
{0pt}{\faQuestionCircle}{red} 
```

* des processus qui ne terminent jamais (le père et les fils restaient bloqué après à la fin d'une session)
* des processus zombie
* des voitures qui tournaient plus

```{=latex}
\end{awesomeblock}
``` 

Néanmoins, tous ces problèmes ont été résolu. 

À ce stade, on avait une mémoire partagée fonctionnelle et un affichage digne de ce nom. L'étape suivante était donc de trier 
les données afin d'obtenir un classement correct pour la course du dimanche. Ceci implique plusieurs choses: 

```{=latex}
\begin{awesomeblock}[black]{0.2pt}{\faHandPointRight}{black}  
```

* La mise en place du paramétrage de notre programme.
* La création d'un fichier par classement en fonction de l'étape.  

```{=latex}
\end{awesomeblock}
```

\pagebreak