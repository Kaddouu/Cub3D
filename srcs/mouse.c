/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:53:46 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/14 12:00:00 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	update_vertical_look(t_game *game, double delta)
{
	game->vertical_look -= delta;
	if (game->vertical_look > VERTICAL_LOOK_LIMIT)
	game->vertical_look = VERTICAL_LOOK_LIMIT;
	else if (game->vertical_look < -VERTICAL_LOOK_LIMIT)
	game->vertical_look = -VERTICAL_LOOK_LIMIT;
}

void	handle_mouse_delta(t_game *game, int delta_x, int delta_y)
{
	double	angle_h;
	double	angle_v;

	angle_h = delta_x * MOUSE_SENSITIVITY;
	angle_v = delta_y * MOUSE_SENSITIVITY;
	if (angle_h != 0)
		rotate_player_mouse(game, angle_h);
	if (angle_v != 0)
		update_vertical_look(game, angle_v);
}

void	recenter_mouse_if_needed(t_game *game, int x, int y)
{
	if (x < 50 || x > WINDOW_WIDTH - 50 || y < 50 || y > WINDOW_HEIGHT - 50)
	{
		mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT
			/ 2);
		game->last_mouse_x = WINDOW_WIDTH / 2;
		game->last_mouse_y = WINDOW_HEIGHT / 2;
	}
}

int	mouse_move(int x, int y, t_game *game)
{
	int	delta_x;
	int	delta_y;

	if (!game->mouse_enabled)
		return (0);
	delta_x = x - game->last_mouse_x;
	delta_y = y - game->last_mouse_y;
	if (abs(delta_x) > 200 || abs(delta_y) > 200)
	{
		game->last_mouse_x = x;
		game->last_mouse_y = y;
		return (0);
	}
	handle_mouse_delta(game, delta_x, delta_y);
	game->last_mouse_x = x;
	game->last_mouse_y = y;
	recenter_mouse_if_needed(game, x, y);
	return (0);
}

void	init_mouse(t_game *game)
{
	game->mouse_enabled = 1;
	game->mouse_x = WINDOW_WIDTH / 2;
	game->mouse_y = WINDOW_HEIGHT / 2;
	game->last_mouse_x = WINDOW_WIDTH / 2;
	game->last_mouse_y = WINDOW_HEIGHT / 2;
	game->vertical_look = 0.0;
	mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_mouse_hide(game->mlx, game->win);
}
