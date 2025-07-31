/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/06/16 17:20:32 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "../GNL/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifdef __linux__
#  include "../minilibx-linux/mlx.h"
# else
#  include "../minilibx_macos/mlx.h"
# endif

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* Constantes de fenêtre et de jeu */
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define TILE_SIZE 64
# define FOV 3
# define MOVE_SPEED 5.5
# define ROT_SPEED 0.02

/* Constantes de souris */
# define MOUSE_SENSITIVITY 0.0028
# define VERTICAL_LOOK_LIMIT 1.5
# define MOUSE_HIDE_CURSOR 1

/* Keycodes par système */
# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# else
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# endif

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	char			dir_char;
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
}					t_player;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*floor_texture;
	char			*ceiling_texture;
	int				floor_color;
	int				ceiling_color;
	int				use_floor_texture;
	int				use_ceiling_texture;
	char			*path;
	char			**remaining_lines;
	int				remaining_line_count;
}					t_map;

typedef struct s_ray
{
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			wall_x;
	t_vector		dir;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	int				tex_x;
	unsigned int	color;
}					t_ray;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_draw_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				delta_x;
	int				delta_y;
	int				step_x;
	int				step_y;
	int				error;
}					t_draw_line;

typedef struct s_arrow
{
	int				center_x;
	int				center_y;
	int				tip_x;
	int				tip_y;
	int				base1_x;
	int				base1_y;
	int				base2_x;
	int				base2_y;
}					t_arrow;

typedef struct s_minimap
{
	int				x;
	int				y;
	int				size;
	int				margin;
	int				screen_x;
	int				screen_y;
}					t_minimap;

typedef struct s_line_params
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
}					t_line_params;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_map			map;
	t_player		player;
	t_texture		textures[6];
	int				keys[66000];
	int				mouse_x;
	int				mouse_y;
	int				last_mouse_x;
	int				last_mouse_y;
	int				mouse_enabled;
	double			vertical_look;
}					t_game;

/* ************************************************************************** */
/*                           FONCTIONS D'INITIALISATION                      */
/* ************************************************************************** */

int					init_game(t_game *game, char *map_path);
void				init_struct(t_game *game);
int					init_mlx(t_game *game);
int					init_textures(t_game *game);
void				init_mouse(t_game *game);

/* ************************************************************************** */
/*                             FONCTIONS DE PARSING                          */
/* ************************************************************************** */

/* Parsing principal */
int					parse_map(t_game *game, char *map_path);
int					parse_map_info(t_game *game, int fd);
int					parse_map_grid(t_game *game, int fd);

/* Parsing des textures */
int					parse_north_texture(t_game *game, char *line,
						int *info_count, bool *texture_found);
int					parse_south_texture(t_game *game, char *line,
						int *info_count, bool *texture_found);
int					parse_west_texture(t_game *game, char *line,
						int *info_count, bool *texture_found);
int					parse_east_texture(t_game *game, char *line,
						int *info_count, bool *texture_found);
int					parse_texture_line(t_game *game, char *line,
						int *info_count, bool *texture_found);
int					parse_texture_path(char **dest, char *line);

/* Parsing des couleurs */
int					parse_floor_color(t_game *game, char *line,
						int *info_count);
int					parse_ceiling_color(t_game *game, char *line,
						int *info_count);
int					parse_color_line(t_game *game, char *line, int *info_count);
int					parse_color(char *line);

/* Parsing du joueur */
void				process_player_position(t_game *game, char c, int i, int j);

/* Validation et traitement des lignes */
int					check_invalid_line(char *line);
int					process_line(t_game *game, char *line, int *info_count,
						bool *texture_found);
int					validate_remaining_lines(int fd);
void				init_texture_found(bool *texture_found);

/* Utilitaires de parsing */
int					is_empty_line(char *line);
int					is_map_line(char *line);
char				get_map_char(char *line, int k);
int					fill_map_line(t_game *game, char *line, int i);
int					calculate_map_dimensions(t_game *game, int fd);
int					skip_header_lines(int fd);
void				trim_trailing_whitespace(char *str);
void				trim_whitespace(char *str);
int					is_valid_number_string(char *str);

/* Validation */
int					validate_map(t_map *map);

/* ************************************************************************** */
/*                            FONCTIONS DE RAYCASTING                        */
/* ************************************************************************** */

void				ft_raycasting(t_game *game);
void				ft_init_ray(t_game *game, int x, t_ray *ray);
void				ft_perform_dda(t_game *game, t_ray *ray);
void				ft_calculate_wall_height(t_game *game, t_ray *ray);
void				ft_draw_wall_texture(t_game *game, t_ray *ray, int x);
void				ft_draw_ceiling_floor(t_game *game, t_ray *ray, int x);

/* ************************************************************************** */
/*                             FONCTIONS DE RENDU                            */
/* ************************************************************************** */

/* Rendu des murs */
void				draw_vertical_line(t_game *game, int x, t_ray *ray);
void				draw_textured_wall(t_game *game, int x, t_ray *ray,
						int tex_num);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* Minimap */
void				draw_minimap(t_game *game);
void				draw_minimap_grid(t_game *game);
void				draw_line(t_img *img, t_line_params *params, int color);
void				draw_arrow(t_game *game, int center_x, int center_y,
						int size);

/* ************************************************************************** */
/*                            FONCTIONS DE MOUVEMENT                         */
/* ************************************************************************** */

/* Mouvement du joueur */
void				move_player(t_game *game);
int					check_collision(t_map *map, double x, double y);

/* Déplacement directionnel */
void				move_forward(t_game *game);
void				move_backward(t_game *game);
void				move_left(t_game *game);
void				move_right(t_game *game);

/* Rotation */
void				rotate_left(t_game *game);
void				rotate_right(t_game *game);
void				rotate_player_mouse(t_game *game, double angle);
void				update_vertical_look(t_game *game, double delta);

/* ************************************************************************** */
/*                           FONCTIONS DE CONTRÔLES                          */
/* ************************************************************************** */

/* Gestion du clavier */
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);

/* Gestion de la souris */
int					mouse_move(int x, int y, t_game *game);
void				handle_mouse_delta(t_game *game, int delta_x, int delta_y);
void				recenter_mouse_if_needed(t_game *game, int x, int y);

/* Gestion de la fenêtre */
int					close_window(t_game *game);

/* ************************************************************************** */
/*                            FONCTIONS UTILITAIRES                          */
/* ************************************************************************** */

void				error_exit(t_game *game, char *message);
void				free_game(t_game *game);

#endif
