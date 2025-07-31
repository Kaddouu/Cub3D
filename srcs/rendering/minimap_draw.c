/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:54:58 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/15 18:43:56 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	init_draw_line(t_draw_line *line, t_line_params *params)
{
	line->x0 = params->x0;
	line->y0 = params->y0;
	line->x1 = params->x1;
	line->y1 = params->y1;
	line->delta_x = abs(params->x1 - params->x0);
	line->delta_y = abs(params->y1 - params->y0);
	if (line->x0 < line->x1)
		line->step_x = 1;
	else
		line->step_x = -1;
	if (line->y0 < line->y1)
		line->step_y = 1;
	else
		line->step_y = -1;
	line->error = line->delta_x - line->delta_y;
}

static void	draw_line_loop(t_img *img, t_draw_line *line, int color)
{
	int	error_doubled;

	while (1)
	{
		my_mlx_pixel_put(img, line->x0, line->y0, color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		error_doubled = 2 * line->error;
		if (error_doubled > -line->delta_y)
		{
			line->error -= line->delta_y;
			line->x0 += line->step_x;
		}
		if (error_doubled < line->delta_x)
		{
			line->error += line->delta_x;
			line->y0 += line->step_y;
		}
	}
}

void	draw_line(t_img *img, t_line_params *params, int color)
{
	t_draw_line	line;

	init_draw_line(&line, params);
	draw_line_loop(img, &line, color);
}

static void	calculate_arrow_points(t_game *game, t_arrow *arrow, int size)
{
	double	angle;
	double	length;
	double	half_base;

	angle = atan2(game->player.dir.y, game->player.dir.x);
	length = size * 1.5;
	half_base = size * 1;
	arrow->tip_x = arrow->center_x - (int)(cos(angle) * length);
	arrow->tip_y = arrow->center_y + (int)(sin(angle) * length);
	arrow->base1_x = arrow->center_x - (int)(cos(angle + 2.35619449)
			* half_base);
	arrow->base1_y = arrow->center_y + (int)(sin(angle + 2.35619449)
			* half_base);
	arrow->base2_x = arrow->center_x - (int)(cos(angle - 2.35619449)
			* half_base);
	arrow->base2_y = arrow->center_y + (int)(sin(angle - 2.35619449)
			* half_base);
}

void	draw_arrow(t_game *game, int center_x, int center_y, int size)
{
	t_arrow			arrow;
	t_line_params	line_params;

	arrow.center_x = center_x;
	arrow.center_y = center_y;
	calculate_arrow_points(game, &arrow, size);
	line_params = (t_line_params){arrow.tip_x, arrow.tip_y, arrow.base1_x,
		arrow.base1_y};
	draw_line(&game->img, &line_params, 0xFF0000);
	line_params = (t_line_params){arrow.base1_x, arrow.base1_y, arrow.base2_x,
		arrow.base2_y};
	draw_line(&game->img, &line_params, 0xFF0000);
	line_params = (t_line_params){arrow.base2_x, arrow.base2_y, arrow.tip_x,
		arrow.tip_y};
	draw_line(&game->img, &line_params, 0xFF0000);
}
