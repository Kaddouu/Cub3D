/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:05:16 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/15 18:05:20 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->player.dir = (t_vector){0, -1};
		game->player.plane = (t_vector){0.66, 0};
	}
	else if (direction == 'S')
	{
		game->player.dir = (t_vector){0, 1};
		game->player.plane = (t_vector){-0.66, 0};
	}
	else if (direction == 'E')
	{
		game->player.dir = (t_vector){1, 0};
		game->player.plane = (t_vector){0, 0.66};
	}
	else if (direction == 'W')
	{
		game->player.dir = (t_vector){-1, 0};
		game->player.plane = (t_vector){0, -0.66};
	}
}

void	process_player_position(t_game *game, char c, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player.pos.x = j + 0.5;
		game->player.pos.y = i + 0.5;
		set_player_direction(game, c);
	}
}
