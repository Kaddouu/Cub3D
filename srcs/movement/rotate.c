/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:58:50 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/15 16:17:20 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(ROT_SPEED)
		- game->player.dir.y * sin(ROT_SPEED);
	game->player.dir.y = old_dir_x * sin(ROT_SPEED) + game->player.dir.y
		* cos(ROT_SPEED);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(ROT_SPEED)
		- game->player.plane.y * sin(ROT_SPEED);
	game->player.plane.y = old_plane_x * sin(ROT_SPEED) + game->player.plane.y
		* cos(ROT_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(-ROT_SPEED)
		- game->player.dir.y * sin(-ROT_SPEED);
	game->player.dir.y = old_dir_x * sin(-ROT_SPEED) + game->player.dir.y
		* cos(-ROT_SPEED);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(-ROT_SPEED)
		- game->player.plane.y * sin(-ROT_SPEED);
	game->player.plane.y = old_plane_x * sin(-ROT_SPEED) + game->player.plane.y
		* cos(-ROT_SPEED);
}

void	rotate_player_mouse(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(angle) - game->player.dir.y
		* sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + game->player.dir.y
		* cos(angle);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(angle)
		- game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) + game->player.plane.y
		* cos(angle);
}
