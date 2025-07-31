/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/06/15 16:12:59 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		flipped_x;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		flipped_x = WINDOW_WIDTH - 1 - x;
		dst = img->addr + (y * img->line_length + flipped_x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char			*dst;
	unsigned int	color;

	if (x >= 0 && x < texture->width && y >= 0 && y < texture->height)
	{
		dst = texture->addr + (y * texture->line_length + x * (texture->bpp
					/ 8));
		color = *(unsigned int *)dst;
		return (color);
	}
	return (0);
}

void	draw_ceiling_and_floor(t_game *game, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < start)
	{
		my_mlx_pixel_put(&game->img, x, y, game->map.ceiling_color);
		y++;
	}
	y = end;
	while (y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(&game->img, x, y, game->map.floor_color);
		y++;
	}
}

void	draw_textured_wall(t_game *game, int x, t_ray *ray, int tex_num)
{
	double	wall_x;
	int		tex_x;
	int		y;
	int		tex_y;
	int		color;

	if (ray->side == 0)
		wall_x = game->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = game->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)game->textures[tex_num].width);
	if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1
			&& ray->dir.y < 0))
		tex_x = game->textures[tex_num].width - tex_x - 1;
	draw_ceiling_and_floor(game, x, ray->draw_start, ray->draw_end);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (y - WINDOW_HEIGHT / 2 + ray->line_height / 2)
			* game->textures[tex_num].height / ray->line_height;
		color = get_texture_pixel(&game->textures[tex_num], tex_x, tex_y);
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}
