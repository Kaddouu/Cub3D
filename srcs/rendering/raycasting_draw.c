/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ysaadaou          #+#    #+#             */
/*   Updated: 2025/06/14 12:24:10 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static double	calculate_step(t_ray *ray)
{
	double	step;

	step = 64.0;
	if (ray->line_height > 0)
		step = 64.0 / (double)ray->line_height;
	return (step);
}

static int	calculate_tex_y(t_ray *ray, int y, int vertical_offset, double step)
{
	int		real_y;
	double	tex_pos;
	int		tex_y;

	real_y = y - vertical_offset;
	tex_pos = (real_y - (WINDOW_HEIGHT / 2 - ray->line_height / 2)) * step;
	if (tex_pos < 0)
		tex_pos = 0;
	if (tex_pos >= 64.0)
		tex_pos = 63.0;
	tex_y = (int)tex_pos & 63;
	return (tex_y);
}

static void	get_texture_color(t_game *game, t_ray *ray, int tex_y)
{
	ray->color = *(unsigned int *)(game->textures[ray->tex_num].addr + (tex_y
				* game->textures[ray->tex_num].line_length + ray->tex_x
				* (game->textures[ray->tex_num].bpp / 8)));
	if (ray->side == 1)
		ray->color = (ray->color >> 1) & 8355711;
}

void	ft_draw_wall_texture(t_game *game, t_ray *ray, int x)
{
	int		y;
	double	step;
	int		vertical_offset;
	int		tex_y;

	step = calculate_step(ray);
	vertical_offset = (int)(game->vertical_look * WINDOW_HEIGHT / 2);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = calculate_tex_y(ray, y, vertical_offset, step);
		get_texture_color(game, ray, tex_y);
		my_mlx_pixel_put(&game->img, x, y, ray->color);
		y++;
	}
}

void	ft_draw_ceiling_floor(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&game->img, x, y, game->map.ceiling_color);
		y++;
	}
	y = ray->draw_end;
	while (y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(&game->img, x, y, game->map.floor_color);
		y++;
	}
}
