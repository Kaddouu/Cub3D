/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ysaadaou          #+#    #+#             */
/*   Updated: 2025/06/15 16:05:22 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	calculate_perp_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos.x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos.y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
}

static void	calculate_draw_limits(t_game *game, t_ray *ray)
{
	int	vertical_offset;

	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	vertical_offset = (int)(game->vertical_look * WINDOW_HEIGHT / 2);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2
		+ vertical_offset;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2 + vertical_offset;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

static void	calculate_texture_num(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex_num = 3;
		else
			ray->tex_num = 2;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex_num = 1;
		else
			ray->tex_num = 0;
	}
}

static void	calculate_wall_x_and_tex(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * 64.0);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
}

void	ft_calculate_wall_height(t_game *game, t_ray *ray)
{
	calculate_perp_wall_dist(game, ray);
	calculate_draw_limits(game, ray);
	calculate_texture_num(ray);
	calculate_wall_x_and_tex(game, ray);
}
