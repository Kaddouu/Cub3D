# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 15:23:27 by ysaadaou          #+#    #+#              #
#    Updated: 2025/06/16 17:21:23 by ilkaddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom du programme
NAME = cub3D

# Compilateur et options
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# Détection de l'OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX_DIR = minilibx-linux
	MLX_URL = https://github.com/42Paris/minilibx-linux.git
	MLXFLAGS = -lXext -lX11 -lm
else ifeq ($(UNAME_S),Darwin)
	MLX_DIR = minilibx_macos
	MLX_URL = https://github.com/42Paris/minilibx_macos.git
	MLXFLAGS = -framework OpenGL -framework AppKit
else
	# Fallback pour Windows ou autres
	MLX_DIR = minilibx-linux
	MLX_URL = https://github.com/42Paris/minilibx-linux.git
	MLXFLAGS = -lXext -lX11 -lm
endif

# Dossiers
SRCS_DIR = srcs
INCS_DIR = includes
OBJS_DIR = objs
LIBFT_DIR = libft
GNL_DIR = GNL

# Sources listées explicitement
SRCS_MAIN = \
	$(SRCS_DIR)/exit.c \
	$(SRCS_DIR)/free.c \
	$(SRCS_DIR)/init.c \
	$(SRCS_DIR)/key.c \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/mouse.c

SRCS_PARSING = \
	$(SRCS_DIR)/parsing/parse_color.c \
	$(SRCS_DIR)/parsing/parse_map_grid.c \
	$(SRCS_DIR)/parsing/parse_map_info.c \
	$(SRCS_DIR)/parsing/parse_textures_utils.c \
	$(SRCS_DIR)/parsing/parse_color_utils.c \
	$(SRCS_DIR)/parsing/parse_map_validation.c \
	$(SRCS_DIR)/parsing/parse_map_main.c \
	$(SRCS_DIR)/parsing/parse_player.c \
	$(SRCS_DIR)/parsing/parse_utils.c \
	$(SRCS_DIR)/parsing/parse_utils2.c \
	$(SRCS_DIR)/parsing/parse_utils3.c \
	$(SRCS_DIR)/parsing/validate_map.c

SRCS_RENDERING = \
	$(SRCS_DIR)/rendering/minimap_draw.c \
	$(SRCS_DIR)/rendering/minimap_utils.c \
	$(SRCS_DIR)/rendering/raycasting_calc.c \
	$(SRCS_DIR)/rendering/raycasting_dda.c \
	$(SRCS_DIR)/rendering/raycasting_draw.c \
	$(SRCS_DIR)/rendering/raycasting_init.c \
	$(SRCS_DIR)/rendering/textures.c

SRCS_MOVEMENT = \
	$(SRCS_DIR)/movement/collisions.c \
	$(SRCS_DIR)/movement/directions.c \
	$(SRCS_DIR)/movement/player_move.c \
	$(SRCS_DIR)/movement/rotate.c

SRCS_GNL = \
	$(GNL_DIR)/get_next_line.c

# Conversion des chemins sources en chemins objets
OBJS_MAIN = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_MAIN))
OBJS_PARSING = $(patsubst $(SRCS_DIR)/parsing/%.c, $(OBJS_DIR)/parsing/%.o, $(SRCS_PARSING))
OBJS_RENDERING = $(patsubst $(SRCS_DIR)/rendering/%.c, $(OBJS_DIR)/rendering/%.o, $(SRCS_RENDERING))
OBJS_MOVEMENT = $(patsubst $(SRCS_DIR)/movement/%.c, $(OBJS_DIR)/movement/%.o, $(SRCS_MOVEMENT))
OBJS_GNL = $(patsubst $(GNL_DIR)/%.c, $(OBJS_DIR)/gnl/%.o, $(SRCS_GNL))

# Tous les objets
OBJS = $(OBJS_MAIN) $(OBJS_PARSING) $(OBJS_RENDERING) $(OBJS_MOVEMENT) $(OBJS_GNL)

# Règle par défaut
all: libft_compile gnl_compile mlx_download $(NAME)

# Création des dossiers d'objets
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/parsing
	mkdir -p $(OBJS_DIR)/rendering
	mkdir -p $(OBJS_DIR)/movement
	mkdir -p $(OBJS_DIR)/gnl

# Compilation de la libft
$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

# Règle explicite pour compiler libft en premier
libft_compile: $(LIBFT_DIR)/libft.a

# Règle explicite pour compiler GNL
gnl_compile: $(OBJS_DIR) $(OBJS_GNL)

# Téléchargement automatique de minilibx selon l'OS
mlx_download:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "\033[33mTéléchargement de minilibx pour $(UNAME_S)...\033[0m"; \
		git clone $(MLX_URL) $(MLX_DIR); \
		echo "\033[32mMinilibx téléchargée avec succès !\033[0m"; \
	else \
		echo "\033[32mMinilibx déjà présente.\033[0m"; \
	fi

# Compilation de la minilibx seulement si libmlx.a n'existe pas
$(MLX_DIR)/libmlx.a: mlx_download
	@if [ ! -f "$(MLX_DIR)/libmlx.a" ]; then \
		echo "\033[33mCompilation de minilibx...\033[0m"; \
		make -C $(MLX_DIR); \
		echo "\033[32mMinilibx compilée avec succès !\033[0m"; \
	else \
		echo "\033[32mMinilibx déjà compilée.\033[0m"; \
	fi

# Compilation du programme principal
$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(MLXFLAGS) -o $(NAME)

# Règles de compilation pour les différents types de fichiers
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -c $< -o $@

$(OBJS_DIR)/parsing/%.o: $(SRCS_DIR)/parsing/%.c
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -c $< -o $@

$(OBJS_DIR)/rendering/%.o: $(SRCS_DIR)/rendering/%.c
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -c $< -o $@

$(OBJS_DIR)/movement/%.o: $(SRCS_DIR)/movement/%.c
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -c $< -o $@

$(OBJS_DIR)/gnl/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -c $< -o $@
	@echo "\033[32mCompilation terminée avec succès !\033[0m"

# Nettoyage
clean:
	make -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	@if [ -d "$(MLX_DIR)" ]; then \
		echo "\033[31mSuppression de minilibx...\033[0m"; \
		rm -rf $(MLX_DIR); \
		echo "\033[32mMinilibx supprimée !\033[0m"; \
	fi
	rm -f $(NAME)

re: fclean all

# Règle pour forcer le téléchargement de minilibx
mlx_redownload:
	@echo "\033[31mSuppression de l'ancienne minilibx...\033[0m"
	@rm -rf $(MLX_DIR)
	@echo "\033[33mTéléchargement de la nouvelle minilibx...\033[0m"
	@git clone $(MLX_URL) $(MLX_DIR)
	@echo "\033[32mMinilibx retéléchargée avec succès !\033[0m"

.PHONY: all clean fclean re libft_compile gnl_compile mlx_download mlx_redownload
