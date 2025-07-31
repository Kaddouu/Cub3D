/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/06/14 19:28:21 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	init_struct(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->win = NULL;
	game->img.img = NULL;
	game->map.path = NULL;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	i = -1;
	while (++i < 4)
		game->textures[i].img = NULL;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.dir.x = 0;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0;
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cube3D");
	if (!game->win)
		return (1);
	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img.img)
		return (1);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.endian);
	ft_memset(game->keys, 0, sizeof(game->keys));
	game->player.plane.x = 0.66 * game->player.dir.y;
	game->player.plane.y = -0.66 * game->player.dir.x;
	return (0);
}

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	char	*newline;
	int		len;

	newline = ft_strchr(path, '\n');
	if (newline)
		*newline = '\0';
	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\t' || path[len
				- 1] == '\n'))
	{
		path[len - 1] = '\0';
		len--;
	}
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img || texture->width != 64 || texture->height != 64)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	return (0);
}

int	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
		game->textures[i++].img = NULL;
	if (load_texture(game, &game->textures[0], game->map.north_texture))
		return (1);
	if (load_texture(game, &game->textures[1], game->map.south_texture))
		return (1);
	if (load_texture(game, &game->textures[2], game->map.west_texture))
		return (1);
	if (load_texture(game, &game->textures[3], game->map.east_texture))
		return (1);
	return (0);
}

int	init_game(t_game *game, char *map_path)
{
	ft_memset(game, 0, sizeof(t_game));
	if (parse_map(game, map_path) != 0)
		return (1);
	if (validate_map(&game->map) != 0)
		return (1);
	if (init_mlx(game) != 0)
		return (1);
	if (init_textures(game) != 0)
		return (1);
	return (0);
}
