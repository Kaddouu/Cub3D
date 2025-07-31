/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:58:14 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/15 16:14:15 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED / 100;
	new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED / 100;
	if (check_collision(&game->map, new_x, game->player.pos.y))
		game->player.pos.x = new_x;
	if (check_collision(&game->map, game->player.pos.x, new_y))
		game->player.pos.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED / 100;
	new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED / 100;
	if (check_collision(&game->map, new_x, game->player.pos.y))
		game->player.pos.x = new_x;
	if (check_collision(&game->map, game->player.pos.x, new_y))
		game->player.pos.y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.y * MOVE_SPEED / 100;
	new_y = game->player.pos.y - game->player.dir.x * MOVE_SPEED / 100;
	if (check_collision(&game->map, new_x, game->player.pos.y))
		game->player.pos.x = new_x;
	if (check_collision(&game->map, game->player.pos.x, new_y))
		game->player.pos.y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.dir.y * MOVE_SPEED / 100;
	new_y = game->player.pos.y + game->player.dir.x * MOVE_SPEED / 100;
	if (check_collision(&game->map, new_x, game->player.pos.y))
		game->player.pos.x = new_x;
	if (check_collision(&game->map, game->player.pos.x, new_y))
		game->player.pos.y = new_y;
}
