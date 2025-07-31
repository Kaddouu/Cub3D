/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ysaadaou          #+#    #+#             */
/*   Updated: 2025/06/15 16:03:57 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	check_map_bounds(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= game->map.width)
		return (1);
	if (ray->map_y < 0 || ray->map_y >= game->map.height)
		return (1);
	return (0);
}

static void	perform_dda_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	ft_perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		perform_dda_step(ray);
		if (check_map_bounds(game, ray))
			break ;
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
