Introduction et présentation du projet
--------------------------------------

::: box
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam aliquet libero
quis lectus elementum fermentum.
:::

\tcbset{colback=red!5!white,colframe=red!75!black}

\begin{tcolorbox}[title=Préface]
Je souhaite tout d'abord remercier Dreamnet SRL et leurs contacts, car sans eux, ce projet n'aurait sans doute pas existé. Leur soutien à été d'une grande aide malgré les circonstances atténuantes lié au COVID-19.

\medskip

Je remercie également mon rapporteur de TFE, le professeur Arnaud Dewulf, pour les multiples échanges que nous avons eus et qui m'a permis de me conforter dans le choix de certains capteurs et de particularités à tenir en compte au niveau de l'aspect électronique de ce travail de fin d'études.

\medskip

Je remercie également le client venant du professeur Arnaud Dewulf qui m'a orienté vers une réflexion poussée sur LoRaWAN et Zigbee. Cela m'a permis de tenir en compte de possibles ouvertures en termes de moyen de communication. De plus, il m'a permis de rediriger mes choix de capteurs afin de rendre ce travail le plus générique possible avec possibilité de personnalisation. Malheureusement, au vu des circonstances mondiales rencontrées, nos échanges n'ont finalement pas donné de suite.
\end{tcolorbox}

Ce projet consiste à présenter un week-end complet d'un grand prix de Formule 1, depuis les séances d'essais du vendredi 
jusqu'à la course du dimanche, en passant par les essais du samedi et la séance de qualifications.

Notre but consiste à reproduire et simuler cela par le bais du langage de programmation C. Nous devons utiliser la ligne de 
commande afin d'afficher la grille des positions tout au long des séances d'essais libres, des qualifications ainsi que de la course.

Nous afficherons dès lors :

::: note

* le meilleur temps au tour par voiture
* les noms(id) de voitures ainsi que leurs positions 
* qui a le meilleur temps dans chacun des secteurs
* le nombre de tours(lap) effectué par voiture
* les voitures aux stand(pit)
* ...

:::

De plus, nous devons appliquer des concepts vus en cours comme :

* utilisation de processus père-fils via la fonction `fork()` (cours de 1ère année)[^1]
* utilisation de la mémoire partagée pour le partage de données entre processus
* utilisation de sémaphores pour gérer la synchronisation des processus [^2].

[^1]: [Fork](https://www.man7.org/linux/man-pages/man2/fork.2.html) 
[^2]: [Sémaphores](https://sites.uclouvain.be/SystInfo/notes/Theorie/html/Threads/coordination.html) 

\pagebreak

