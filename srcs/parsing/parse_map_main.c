/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/16 17:11:54 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	parse_map(t_game *game, char *map_path)
{
	int	fd;

	game->map.path = ft_strdup(map_path);
	if (!game->map.path)
		return (1);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (parse_map_info(game, fd) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (parse_map_grid(game, fd) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
