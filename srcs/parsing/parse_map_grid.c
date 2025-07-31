/* ************************************************************************** */
/*                                                                            */
/*                                                        ::: :::::::: */
/*   parse_map_grid.c                                  :+: :+: :+: */
/*                                                    +:+ +:+         +:+ */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/14 16:24:40 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	allocate_map_grid(t_game *game)
{
	int	i;

	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (1);
	i = 0;
	while (i <= game->map.height)
	{
		game->map.grid[i] = NULL;
		i++;
	}
	return (0);
}

static int	fill_map_from_file(t_game *game, int fd)
{
	char	*line;
	int		i;
	int		map_started;

	i = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line && i <= game->map.height)
	{
		if (is_map_line(line) && !fill_map_line(game, line, i++))
			map_started = 1;
		else if (map_started && is_empty_line(line))
		{
			free(line);
			get_next_line(-1);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	game->map.grid[i] = NULL;
	return (i != game->map.height);
}

static int	process_map_file(t_game *game, int fd)
{
	if (allocate_map_grid(game) != 0)
	{
		close(fd);
		return (1);
	}
	if (fill_map_from_file(game, fd) != 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

int	parse_map_grid(t_game *game, int fd)
{
	if (calculate_map_dimensions(game, fd) != 0)
	{
		get_next_line(-1);
		return (1);
	}
	close(fd);
	fd = open(game->map.path, O_RDONLY);
	if (fd == -1)
		return (1);
	if (process_map_file(game, fd) != 0)
		return (1);
	close(fd);
	return (0);
}
