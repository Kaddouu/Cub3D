/* ************************************************************************** */
/*                                                                            */
/*                                                        ::: :::::::: */
/*   parse_map_utils2.c                                :+: :+: :+: */
/*                                                    +:+ +:+         +:+ */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/14 16:24:40 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

char	get_map_char(char *line, int k)
{
	if (!line[k] || line[k] == '\n')
		return (' ');
	return (line[k]);
}

static int	is_config_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static int	skip_config_info(int fd)
{
	char	*line;
	int		info_count;

	info_count = 0;
	while (info_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
		{
			get_next_line(-1);
			return (1);
		}
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (is_config_line(line))
			info_count++;
		free(line);
	}
	return (0);
}

static int	skip_empty_lines(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			get_next_line(-1);
			return (1);
		}
		if (!is_empty_line(line))
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (0);
}

int	skip_to_map_start(int fd)
{
	if (skip_config_info(fd))
		return (1);
	if (skip_empty_lines(fd))
		return (1);
	return (0);
}
