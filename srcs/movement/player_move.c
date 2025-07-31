/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/06/15 16:13:50 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	move_player(t_game *game)
{
	if (game->keys[KEY_W])
		move_forward(game);
	if (game->keys[KEY_S])
		move_backward(game);
	if (game->keys[KEY_A])
		move_left(game);
	if (game->keys[KEY_D])
		move_right(game);
	if (game->keys[KEY_LEFT])
		rotate_right(game);
	if (game->keys[KEY_RIGHT])
		rotate_left(game);
}
