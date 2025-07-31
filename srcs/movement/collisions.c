/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:32 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/14 12:02:04 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	check_single_point(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (0);
	if (map->grid[map_y][map_x] == '1' || map->grid[map_y][map_x] == ' ')
		return (0);
	return (1);
}

int	check_collision(t_map *map, double x, double y)
{
	double	collision_margin;
	double	check_points[4][2];
	int		i;

	collision_margin = 0.2;
	check_points[0][0] = x + collision_margin;
	check_points[0][1] = y;
	check_points[1][0] = x - collision_margin;
	check_points[1][1] = y;
	check_points[2][0] = x;
	check_points[2][1] = y + collision_margin;
	check_points[3][0] = x;
	check_points[3][1] = y - collision_margin;
	i = 0;
	while (i < 4)
	{
		if (!check_single_point(map, check_points[i][0], check_points[i][1]))
			return (0);
		i++;
	}
	return (1);
}
