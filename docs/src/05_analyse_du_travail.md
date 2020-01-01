Analyse du travail
------------------

### Plan du programme 

Afin d'améliorer notre rapport, nous avons retenu les remarques faites par la professeur lors d'une séance de TP. 
Suite à ce dernier, nous avons décidé de commencer par décortiquer les demandes et en faire un flowchart afin 
de mieux visualiser le projet : 

\begin{figure}[H]
\centering
\caption{Flowchart}
\includegraphics[scale=0.25]{imgs/test.png}
\end{figure}

Malheureusement vu la taille du l'image, on était obligé de l'imprimer à part sur une feuille A3 qui se trouve en annexe 
du rapport. Comme vous pouvez le voir sur l'image le projet est divisé en 3 parties. Vendredi, samedi et dimanche. 
P1 et P2 sont exécutés le vendredi, samedi on a les étapes suivantes : P3, Q1, Q2, Q3 et afin dimanche on a la course finale.

Pour une question de sécurité si le nom jour passé comme argument du programme est ni vendredi ni samedi ni dimanche, 
le programme affiche un manuel en console et s'arrêter. 
 
### Découpage en plusieurs fichiers 

\begin{figure}[H]
\centering
\caption{Structure des fichiers}
\includegraphics[scale=0.6]{imgs/files-struct.png}
\end{figure}

Pour simplifier le projet, nous avons décidé de découper ce dernier en plusieurs au lieu d'avoir tout le code dans un 
seul fichier. Nous avons **7 fichiers** C qui communiquent entre eux pour produire un exécutable. Le fait d'avoir coupé le 
code en plusieurs fichiers nous a beaucoup aidé lors du débogage des problèmes rencontrés au fur qu'on avançait. 

### Fichiers principaux 

Sans surprise, le fichier le plus important c'est le fichier **main.c**. C'est dans ce dernier qu'on trouve la création 
de la mémoire partagée, des sémaphores, paramétrage du programme et également des fils/voitures qui vont participer 
au Grand Prix. Le fichier **display.c**. sert principalement à afficher les données triées en console, 
le fichier **child.c** comme son nom l'indique c'est dans ce fichier que les voitures créent par la fonction
`fork` dans **main.c** vont écrire dans la mémoire partagée. et finalement parmis les fichiers principaux, on a le fichier 
**files.c** qui va se charger de tout ce qui a avoir avec un fichier. La création et la lecture des fichiers est géré par
ce fichier **files.c**. 
 
### Description de la méthode de travail 

Tout premièrement, nous avons décidé de travailler avec un logiciel de gestion de version notamment connu sous le nom de 
git. Ce type de logiciel est devenu indispensable lorsqu’on travaille à plusieurs sur un même projet et donc sur 
le même code source. cela nous a permit deux choses : 
  
 - **suivre l’évolution du code source**, pour retenir les modifications effectuées sur chaque fichier et être 
   ainsi capable de revenir en arrière en cas de problème. 
 - **travailler à plusieurs**, sans risquer de se marcher sur les pieds. Si deux personnes modifient un même fichier en même 
   temps, leurs modifications doivent pouvoir être fusionnées sans perte d’information.

On a remarqué toute au début du projet qu'il était primordiale d'avoir une voiture qui tourne et affiche bien les données 
en console avant d'en avoir 20 qui tournent en même temps. Du coup on a commencé par créer le fichier **child.c** pour 
générer aléatoirement le temps secteurs, le temps passé au stand etc...

Une fois qu'on avait une voiture qui tournait correctement, on est passé à l'étape suivante l'affichage. On a décidé de 
représenter les données en console sous forme d'une table. Il existe plusieurs librairies qui permettent d'avoir une 
table en console mais la plupart supporte pas le rafraichissement. L'un de plus gros challenge qu'on a rencontré, 
c'était le rafraichissement des données dans une table en console. On a fini par utiliser une librairie disponible 
sur github sous le nom de **libfort** ([lien](https://github.com/seleznevae/libfort "github de libfort")) 
et quelques commandes bash qu'on a dû convertir en langage C pour obtenir le rafraichissement des données 
affichés en console.

Après avoir réussi à obtenir une voiture qui tournait correctement et un affichage qui nous convenait bien, on est passé 
à la création de la mémoire partagée, évidemment créer ce dernier sans avoir au moins 2 processus qui tournent n'a pas de 
de sens. On est resté bloquer sur la mémoire partagée pendant plusieurs semaines car on a connu plusieurs problèmes notamment 
les fils qui terminaient jamais, des processus zombie, les voitures qui tournaient plus alors qu'une tournait bien avant 
la mémoire partagée...Mais tous ces problèmes ont étaient résolu. 

À ce stade, on avait un affichage correcte et la mémoire partagée qui fonctionnait correctement, on est passé l'étape 
suivant, le trie des données et surtout trouver un moyen d'avoir le bon classement pour la course de dimanche.
Cette étape englobe plusieurs choses, pour pouvoir arriver à un bon classement des voitures pour la course de dimanche, 
il a fallu introduire le paramétrage du programme qu'on n'a pas encore traité càd passer les étapes P1, P2, Q1 
jusqu'à RACE comme arguments de notre programme et la gestion des dépassements qui va engendrer la création des fichiers.

\pagebreak