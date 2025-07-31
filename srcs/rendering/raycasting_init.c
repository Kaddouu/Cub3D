/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ysaadaou          #+#    #+#             */
/*   Updated: 2025/06/16 18:40:42 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	init_ray_delta(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_ray_x_direction(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos.x)
			* ray->delta_dist_x;
	}
}

static void	init_ray_y_direction(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos.y)
			* ray->delta_dist_y;
	}
}

void	ft_init_ray(t_game *game, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->ray_dir_y = game->player.dir.y + game->player.plane.y * camera_x;
	ray->dir.x = ray->ray_dir_x;
	ray->dir.y = ray->ray_dir_y;
	ray->map_x = (int)game->player.pos.x;
	ray->map_y = (int)game->player.pos.y;
	init_ray_delta(ray);
	init_ray_x_direction(game, ray);
	init_ray_y_direction(game, ray);
	ray->hit = 0;
}

void	ft_raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ft_init_ray(game, x, &ray);
		ft_perform_dda(game, &ray);
		ft_calculate_wall_height(game, &ray);
		ft_draw_wall_texture(game, &ray, x);
		ft_draw_ceiling_floor(game, &ray, x);
		x++;
	}
}





