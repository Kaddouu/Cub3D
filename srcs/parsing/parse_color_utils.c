/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:30:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/16 17:18:30 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	parse_floor_color(t_game *game, char *line, int *info_count)
{
	game->map.floor_color = parse_color(line + 2);
	if (game->map.floor_color != -1)
	{
		(*info_count)++;
		return (0);
	}
	return (1);
}

int	parse_ceiling_color(t_game *game, char *line, int *info_count)
{
	game->map.ceiling_color = parse_color(line + 2);
	if (game->map.ceiling_color != -1)
	{
		(*info_count)++;
		return (0);
	}
	return (1);
}

int	parse_color_line(t_game *game, char *line, int *info_count)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_floor_color(game, line, info_count));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_ceiling_color(game, line, info_count));
	return (0);
}
