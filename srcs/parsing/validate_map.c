/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/06/15 17:59:51 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	is_walkable_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\t');
}

static int	is_boundary_or_open_space(t_map *map, int i, int j)
{
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		return (1);
	if (j + 1 >= map->width || map->grid[i][j + 1] == ' ' || map->grid[i][j
		+ 1] == '\t')
		return (1);
	if (j - 1 < 0 || map->grid[i][j - 1] == ' ' || map->grid[i][j - 1] == '\t')
		return (1);
	if (i + 1 >= map->height || map->grid[i + 1][j] == ' ' || map->grid[i
		+ 1][j] == '\t')
		return (1);
	if (i - 1 < 0 || map->grid[i - 1][j] == ' ' || map->grid[i - 1][j] == '\t')
		return (1);
	return (0);
}

static int	validate_cell(t_map *map, int i, int j, int *player_count)
{
	char	c;

	c = map->grid[i][j];
	if (!is_valid_map_char(c))
		return (1);
	if (c == ' ' || c == '\t')
		return (0);
	if (is_walkable_char(c))
	{
		if (is_boundary_or_open_space(map, i, j))
			return (1);
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			(*player_count)++;
	}
	return (0);
}

int	validate_map(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (validate_cell(map, i, j, &player_count) != 0)
				return (1);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (1);
	return (0);
}
