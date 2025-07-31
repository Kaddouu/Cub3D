/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:30:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/16 17:18:14 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	parse_north_texture(t_game *game, char *line, int *info_count,
		bool *texture_found)
{
	if (texture_found[0] == true)
		return (1);
	if (parse_texture_path(&game->map.north_texture, line + 3) == 0)
	{
		(*info_count)++;
		texture_found[0] = true;
	}
	return (0);
}

int	parse_south_texture(t_game *game, char *line, int *info_count,
		bool *texture_found)
{
	if (texture_found[1] == true)
		return (1);
	if (parse_texture_path(&game->map.south_texture, line + 3) == 0)
	{
		(*info_count)++;
		texture_found[1] = true;
	}
	return (0);
}

int	parse_west_texture(t_game *game, char *line, int *info_count,
		bool *texture_found)
{
	if (texture_found[2] == true)
		return (1);
	if (parse_texture_path(&game->map.west_texture, line + 3) == 0)
	{
		(*info_count)++;
		texture_found[2] = true;
	}
	return (0);
}

int	parse_east_texture(t_game *game, char *line, int *info_count,
		bool *texture_found)
{
	if (texture_found[3] == true)
		return (1);
	if (parse_texture_path(&game->map.east_texture, line + 3) == 0)
	{
		(*info_count)++;
		texture_found[3] = true;
	}
	return (0);
}

int	parse_texture_line(t_game *game, char *line, int *info_count,
		bool *texture_found)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_north_texture(game, line, info_count, texture_found));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_south_texture(game, line, info_count, texture_found));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_west_texture(game, line, info_count, texture_found));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_east_texture(game, line, info_count, texture_found));
	return (0);
}
