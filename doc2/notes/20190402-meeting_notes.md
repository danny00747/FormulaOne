# 2 avril 2019 - 15h

Rendez-vous avec la professeur.

## Notes

- Essais libres : 3x le même programme, à paramétrer (temps)
- Qualifications : 3x le même programme, à paramétrer (temps, voitures qualifiées)

Si voiture out, entre P (essais libres) et Q (qualifications) ou Q et GP, elle est réparée.

### Affichage

_**Essais libres :**_

- Temps au passage par secteur,
- Temps total,
- PIT et OUT,
- Temps au tour,
- Classement par le meilleur tour (même si plus sur circuit).

_**Qualifications :**_

- Idem qu'essais libres sauf :
  - 15 voitures qualifiées au Q2,
  - 10 voitures qualifiées pour Q1.
- Garder le meilleur temps au tour, même si crashé (comme dans les essais libres).
- Sauvegarde sur fichier à la fin de chaque fichiers.

_**Courses :**_

- Ordre de qualification = ordre de départ
- Classer en fonction _du temps total !_

Relancer les processus à chaque départ et les lancer dans l'ordre de départ.

Question programmation, les sémaphores sont tout à la fin, les mémoires partagées avant.

Commencer par ceci :

- Structure d'une voiture,
- Temps aléatoire (random, 30-40 secondes),
- Essayer de faire tourner une voiture puis les 20 sans sémaphores puis attribuer un ID,
- Passage en fork après avoir fait tout ça.
