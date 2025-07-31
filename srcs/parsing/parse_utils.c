/* ************************************************************************** */
/*                                                                            */
/*                                                        ::: :::::::: */
/*   parse_map_utils.c                                 :+: :+: :+: */
/*                                                    +:+ +:+         +:+ */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/14 16:24:40 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_valid_char;

	if (!line || is_empty_line(line))
		return (0);
	i = 0;
	has_valid_char = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W' || line[i] == ' '
			|| line[i] == '\t')
		{
			if (line[i] != ' ' && line[i] != '\t')
				has_valid_char = 1;
			i++;
		}
		else if (line[i] == '\n' || line[i] == '\r')
			break ;
		else
			return (0);
	}
	return (has_valid_char);
}

int	fill_map_line(t_game *game, char *line, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	game->map.grid[i] = (char *)malloc(sizeof(char) * (game->map.width + 1));
	if (!game->map.grid[i])
		return (1);
	while (j < game->map.width)
	{
		game->map.grid[i][j] = get_map_char(line, k);
		if (line[k] && line[k] != '\n')
			k++;
		process_player_position(game, game->map.grid[i][j], i, j);
		j++;
	}
	game->map.grid[i][j] = '\0';
	return (0);
}

static int	process_map_line(t_game *game, char *line)
{
	int	len;
	int	k;

	len = 0;
	k = 0;
	while (line[k] && line[k] != '\n')
	{
		len++;
		k++;
	}
	if (len > game->map.width)
		game->map.width = len;
	game->map.height++;
	return (0);
}

int	calculate_map_dimensions(t_game *game, int fd)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_line(line))
		{
			map_started = 1;
			process_map_line(game, line);
		}
		else if (map_started && is_empty_line(line))
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	return (0);
}
