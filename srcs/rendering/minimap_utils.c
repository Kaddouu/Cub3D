/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/15 18:44:22 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	get_minimap_color(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == '1')
		return (0xFFFFFF);
	else if (game->map.grid[y][x] == ' ' || game->map.grid[y][x] == '\t')
		return (0xFF0000);
	else
		return (0x444444);
}

static void	draw_minimap_square(t_game *game, t_minimap *mini, int color)
{
	int	px;
	int	py;

	py = 0;
	while (py < mini->size)
	{
		px = 0;
		while (px < mini->size)
		{
			my_mlx_pixel_put(&game->img, mini->screen_x + px, mini->screen_y
				+ py, color);
			px++;
		}
		py++;
	}
}

void	draw_minimap_grid(t_game *game)
{
	t_minimap	mini;
	int			color;

	mini.size = 5;
	mini.margin = 10;
	mini.y = 0;
	while (mini.y < game->map.height)
	{
		mini.x = 0;
		while (mini.x < game->map.width)
		{
			mini.screen_x = mini.margin + (game->map.width - 1 - mini.x)
				* mini.size;
			mini.screen_y = mini.margin + mini.y * mini.size;
			color = get_minimap_color(game, mini.x, mini.y);
			draw_minimap_square(game, &mini, color);
			mini.x++;
		}
		mini.y++;
	}
}

void	draw_minimap(t_game *game)
{
	int	player_x;
	int	player_y;
	int	minimap_size;

	minimap_size = 5;
	draw_minimap_grid(game);
	player_x = 10 + (game->map.width - game->player.pos.x) * minimap_size
		+ minimap_size / 2;
	player_y = 10 + game->player.pos.y * minimap_size + minimap_size / 2;
	draw_arrow(game, player_x, player_y, minimap_size);
}
