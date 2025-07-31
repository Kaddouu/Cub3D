/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/16 17:20:21 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	parse_map_info(t_game *game, int fd)
{
	char	*line;
	int		info_count;
	bool	texture_found[4];

	init_texture_found(texture_found);
	info_count = 0;
	while (info_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trim_whitespace(line);
		if (process_line(game, line, &info_count, texture_found))
			return (free(line), get_next_line(-1), 1);
		free(line);
	}
	if (info_count != 6)
		return (get_next_line(-1), 1);
	return (validate_remaining_lines(fd));
}
