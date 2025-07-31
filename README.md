# cub3d

Ce projet est un exercice de l'école 42 qui consiste à réaliser un mini-moteur 3D inspiré de Wolfenstein 3D, en utilisant la technique du raycasting. Il permet de se déplacer dans un labyrinthe en vue subjective, avec gestion des textures, de la minimap et des interactions clavier/souris.

![Cub3d](https://github.com/user-attachments/assets/32df788d-98fd-42e8-8cde-a7b5c183ab59)

## Fonctionnement général

Le programme lit une carte (map) au format texte `.cub` qui décrit le labyrinthe, les textures à utiliser, la position de départ du joueur et l'orientation initiale. Ensuite, il utilise un algorithme de raycasting pour afficher une vue pseudo-3D du labyrinthe, comme dans les premiers jeux de tir à la première personne.

### Format de la map

- La map est un fichier texte `.cub`.
- Elle contient la description des textures (chemins vers les images pour chaque mur), les couleurs du sol et du plafond, puis la carte du labyrinthe sous forme de caractères :
    - `1` : mur
    - `0` : espace vide (où le joueur peut se déplacer)
    - `N`, `S`, `E`, `W` : position et orientation de départ du joueur
- Exemple minimal :

```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 225,30,0
111111
100001
1000N1
111111
```

### Algorithme de raycasting

Le moteur utilise le **raycasting** pour simuler la 3D :
- À chaque frame, pour chaque colonne de pixels de l'écran, un rayon est lancé depuis la position du joueur dans la direction correspondante.
- On avance le long du rayon jusqu'à rencontrer un mur dans la map (grille 2D).
- On calcule la distance entre le joueur et le mur touché, ce qui permet de déterminer la hauteur de la "barre" à dessiner pour cette colonne (plus le mur est loin, plus il est petit).
- On applique la texture correspondante sur la colonne.
- On répète pour chaque colonne de l'écran pour obtenir l'effet 3D.

L'algorithme utilisé est généralement le **DDA (Digital Differential Analyzer)**, qui permet de parcourir efficacement la grille de la map pour détecter les collisions avec les murs.

### Minimap

Une minimap 2D est affichée dans un coin de l'écran, représentant la carte vue de dessus, la position du joueur et son orientation.

## Objectif

- Comprendre les bases du raycasting et de la représentation 3D simple.
- Manipuler la librairie graphique MiniLibX (MLX).
- Gérer le parsing d'une carte au format `.cub`.
- Implémenter les déplacements, la gestion des collisions, l'affichage de textures et la minimap.

## Compilation

Pour compiler le projet, il suffit d'utiliser le Makefile fourni :

```sh
make
```

Cela va générer l'exécutable `cube3d`.

Pour nettoyer les fichiers objets :

```sh
make clean
```

Pour tout supprimer (binaire + objets) :

```sh
make fclean
```

Pour recompiler entièrement :

```sh
make re
```

## Utilisation

Le programme s'utilise comme suit :

```sh
./cube3d map.cub
```

- `map.cub` : fichier de configuration de la carte (voir sujet pour le format attendu).

### Exemple

```sh
./cube3d maps/level1.cub
```

## Arguments attendus

Le programme attend exactement 1 argument : le chemin vers un fichier `.cub`.

Si le nombre d'arguments est incorrect ou si le fichier n'a pas l'extension `.cub`, une erreur s'affiche :

```
Usage: ./cube3d <map.cub>
```

## Contrôles

- Déplacement : touches directionnelles ou ZQSD
- Rotation : souris ou touches fléchées
- Quitter : touche ESC ou croix de la fenêtre

## Remarques

- Le projet respecte les normes de l'école 42 (pas de fonction interdite, gestion stricte de la mémoire).
- Les erreurs de parsing, de chargement de textures ou d'initialisation sont gérées et affichent un message explicite.

  > Have fun !
