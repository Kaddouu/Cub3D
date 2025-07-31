/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:30:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/16 17:18:56 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_invalid_line(char *line)
{
	if (ft_strncmp("NO ", line, 3) && ft_strncmp("SO ", line, 3)
		&& ft_strncmp("WE ", line, 3) && ft_strncmp("EA ", line, 3)
		&& ft_strncmp("F ", line, 2) && ft_strncmp("C ", line, 2))
		return (1);
	return (0);
}

int	process_line(t_game *game, char *line, int *info_count,
		bool *texture_found)
{
	if (is_empty_line(line))
		return (0);
	if (parse_texture_line(game, line, info_count, texture_found)
		|| parse_color_line(game, line, info_count))
		return (1);
	if (check_invalid_line(line))
		return (1);
	return (0);
}

int	validate_remaining_lines(int fd)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		trim_whitespace(line);
		if (!is_empty_line(line))
		{
			if (is_map_line(line))
				map_started = 1;
			else
				return (free(line), get_next_line(-1), 1);
		}
		else if (map_started)
			return (free(line), get_next_line(-1), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (get_next_line(-1), 0);
}

void	init_texture_found(bool *texture_found)
{
	texture_found[0] = false;
	texture_found[1] = false;
	texture_found[2] = false;
	texture_found[3] = false;
}
