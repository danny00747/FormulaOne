### Création et gestion des processus

Chaque voiture correspond à un processus fils, tandis que le père s'occupe de la gestion des étapes et de l'affichage.

La création des processus se fait par la fonction `fork`, faisant partie des appels système POSIX. Elle permet de donner 
naissance à un nouveau processus qui est sa copie.

La création des processus fils est présent dans le fichier de code source `main.c`.

**Rôle du processus père**

Dans notre cas, nous avons un processus père donnant naissance au nombre de processus fils nécessaire à l'étape choisie.
Chaque processus fils représente une voiture.

Le processus père, quant à lui, va lire des informations provenant de la mémoire partagée.
Il s'occupe également de l'affichage ainsi que du tri tout comme la sauvegarde des informations sur fichier des étapes de 
qualifications et de la course. 

**Rôle des processus fils**

Dans le cadre de ce projet, les fils sont seulement chargés à courir. Càd exécuter les étapes à faire pour un week-end complet d’un 
grand prix de Formule 1. Pour y arriver on utilise une boucle `while()` avec comme condition si le temps de l'étape chosi n'a
pas écoulé, alors les fils courent. Pour la course de dimanche les fils courent tant qu'ils n'ont pas fini les tours à faire. Les crash
sont gérés à l'interieur du la boucle `while()`. 

Le code du fils est présent dans le fichier de code source `child.c`. 

**Affichage**

Pour pouvoir les données dans table, on utilise une librairie public `libfort` disponible sur github : <https://github.com/seleznevae/libfort>. Voilà un exemple du résultat lors de l'étape Q2. 

| Position | NAME |   S1   |   S2   |   S3   | OUT | PIT | LAP | LAP TIME  | BEST LAP TIME |
|----------|------|--------|--------|--------|-----|-----|-----|-----------|---------------|
| 1        |  7   | 32":03 | 39":03 | 44":77 |  0  |  0  |  13 | 1':02":19 |   1':19":42   |
| 2        |  35  | 42":53 | 41":27 | 39":23 |  0  |  1  |  9  | 1':11":71 |   1':22":31   |
| 3        |  40  | 36":13 | 30":03 | 44":12 |  0  |  0  |  16 | 1':03":36 |   1':44":28   |
| 4        |  40  | 40":04 | 43":03 | 43":03 |  0  |  0  |  10 | 1':40":11 |   1':51":47   |
| 5        |  77  | 33":11 | 34":43 | 42":59 |  0  |  1  |  11 | 1':17":23 |   2':12":73   |

Les autres parties du code arrivent par après. 

\pagebreak 
