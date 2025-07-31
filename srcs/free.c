/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/14 13:53:53 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

static void	free_texture_paths(t_game *game)
{
	if (game->map.north_texture)
	{
		free(game->map.north_texture);
		game->map.north_texture = NULL;
	}
	if (game->map.south_texture)
	{
		free(game->map.south_texture);
		game->map.south_texture = NULL;
	}
	if (game->map.west_texture)
	{
		free(game->map.west_texture);
		game->map.west_texture = NULL;
	}
	if (game->map.east_texture)
	{
		free(game->map.east_texture);
		game->map.east_texture = NULL;
	}
	if (game->map.path)
	{
		free(game->map.path);
		game->map.path = NULL;
	}
}

static void	free_map_grid(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height && game->map.grid[i])
		{
			free(game->map.grid[i]);
			game->map.grid[i] = NULL;
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
	}
}

static void	free_mlx_resources(t_game *game)
{
	if (game->img.img)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		game->img.img = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	free_texture_paths(game);
	free_map_grid(game);
	free_mlx_resources(game);
}
