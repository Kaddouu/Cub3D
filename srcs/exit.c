/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:56:39 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/14 16:04:53 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	error_exit(t_game *game, char *message)
{
	printf("Error\n%s\n", message);
	if (game)
		free_game(game);
	exit(1);
}
