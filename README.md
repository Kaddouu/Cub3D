# Cub3D

> This project has been archived in the state it was in at the time of evaluation.

## Status

<code>Validated 12/05/2025. Grade: 115%.</code>


## Overview
Cub3D is a 3D game engine project inspired by *Wolfenstein 3D*, the pioneering First Person Shooter (FPS). Developed as part of the 42 school curriculum, it uses ray-casting to render a 3D maze from a 2D map, powered by the MiniLibX library. The project delivers an immersive first-person experience with smooth movement, textured walls, and a minimap, integrating both mandatory and bonus features like wall collisions and mouse rotation. La pédagogie 42 excelle par son approche d'apprentissage par projets et par pairs, favorisant l'autonomie, la collaboration et la résolution créative de problèmes complexes.

The focus is on C programming, ray-casting algorithms, and graphics rendering, driven by a `.cub` configuration file.

## Features
- **3D Rendering**: First-person maze view using ray-casting.
- **Player Movement**: WASD for movement, arrow keys (or QE) for rotation, and mouse-based rotation.
- **Texture Mapping**: Supports North, South, East, and West wall textures.
- **Customizable Colors**: Configurable RGB floor and ceiling colors.
- **Wall Collisions**: Prevents passing through walls.
- **Minimap**: Displays a 2D maze overview.
- **Window Management**: Clean exit with ESC or window close.

## Installation

### Prerequisites
- **Operating System**: Linux or macOS.
- **MiniLibX**: Graphics library for rendering (automatically cloned via Makefile).
- **Compiler**: GCC or Clang.
- **Dependencies**: Standard C libraries and math library (`-lm`).

### Clone the Repository
```bash
git clone https://github.com/your-username/cub3D.git
cd cub3D
```
## Compilation

```shell
make
```

The Makefile clones MiniLibX and builds the full project, including mandatory and bonus features. Use make clean or make fclean to remove object files or the executable.

```shell
./cub3D maps/good/map.cub
```
The program requires a .cub file specifying the map, textures, and colors. Example maps are in the maps/good/ directory.

## Controls

- **W**: Move forward
- **S**: Move backward
- **A**: Strafe left
- **D**: Strafe right
- **Left Arrow**: Rotate left
- **Right Arrow**: Rotate right
- **Mouse**: Rotate view
- **ESC**: Exit the game

## Map Configuration

The .cub file defines the game environment:
- **Textures**: Paths for walls (NO, SO, WE, EA)
- **Colors**: Floor (F) and ceiling (C) in RGB (e.g., F 220,100,0)
- **Map**: 2D grid with:
- **1**: Wall
- **0**: Walkable space
- **N/S/E/W**: Player starting position/orientation
- **Spaces**: Empty (non-visible) areas

Example .cub File
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

## Structure du projet cub3D

```
cub3D/
├── GNL/                              # Get Next Line for file parsing
│   ├── get_next_line.c
│   └── get_next_line.h
├── includes/                         # Header files
│   └── cube3d.h
├── libft/                           # Custom C library
│   ├── ft_*.c                       # Standard and bonus libft functions
│   ├── libft.h
│   └── Makefile
├── maps/                            # Map files
│   ├── bad_name.txt
│   ├── error.cub
│   ├── good/                        # Valid map examples
│   │   ├── cheese_maze.cub
│   │   ├── creepy.cub
│   │   ├── dungeon.cub
│   │   ├── library.cub
│   │   ├── matrix.cub
│   │   ├── sad_face.cub
│   │   ├── square_map.cub
│   │   ├── subject_map.cub
│   │   ├── test_*.cub
│   │   └── works.cub
│   ├── simple.cub
│   └── subject.cub
├── srcs/                            # Source code
│   ├── exit.c
│   ├── free.c
│   ├── init.c
│   ├── key.c
│   ├── main.c
│   ├── mouse.c
│   ├── movement/                    # Player movement and collision logic
│   │   ├── collisions.c
│   │   ├── directions.c
│   │   ├── player_move.c
│   │   └── rotate.c
│   ├── parsing/                     # Map and config parsing
│   │   ├── parse_color*.c
│   │   ├── parse_map*.c
│   │   ├── parse_player.c
│   │   ├── parse_textures_utils.c
│   │   ├── parse_utils*.c
│   │   └── validate_map.c
│   ├── rendering/                   # Ray-casting and rendering
│   │   ├── minimap_draw.c
│   │   ├── minimap_utils.c
│   │   ├── raycasting*.c
│   │   └── textures.c
│   └── utils.c
├── textures/                        # Texture files
│   ├── *.xpm
│   ├── simonkraft/                  # Additional textures
│   │   ├── *.xpm
│   │   └── README.md
│   ├── test/                        # Test textures
│   │   ├── *.xpm
│   │   └── north/
│   └── wolfenstein/                 # Wolfenstein-themed textures
│       ├── *.xpm
│       └── README.md
├── Makefile                         # Build configuration
└── README.md                        # Documentation
```

### Description des dossiers principaux

- **GNL/** : Implémentation de Get Next Line pour la lecture des fichiers
- **includes/** : Fichiers d'en-tête du projet
- **libft/** : Bibliothèque C personnalisée avec fonctions utilitaires
- **maps/** : Fichiers de cartes (.cub) pour tester le jeu
- **srcs/** : Code source principal organisé par fonctionnalité
- **textures/** : Assets graphiques (.xpm) pour les murs et éléments du jeu

## Technical Details

- **Ray-Casting**: Uses the DDA algorithm for wall distance calculations and 2.5D projection.
- **MiniLibX**: Handles window management, pixel rendering, and input.
- **Error Handling**: Validates map for closed boundaries, valid characters, and correct configuration.
