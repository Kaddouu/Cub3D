/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/16 16:56:25 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	free_split_array(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

static int	validate_color_components(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	validate_split_elements(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		trim_whitespace(split[i]);
		if (ft_strlen(split[i]) == 0 || !is_valid_number_string(split[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_color(char *line)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	if (!line)
		return (-1);
	split = ft_split(line, ',');
	if (!split)
		return (-1);
	if (!validate_split_elements(split))
		return (free_split_array(split), -1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split_array(split);
	return (validate_color_components(r, g, b));
}

int	parse_texture_path(char **dest, char *line)
{
	char	*trimmed;

	if (!line || !dest)
		return (1);
	trimmed = line;
	while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
		trimmed++;
	*dest = ft_strdup(trimmed);
	if (!*dest)
		return (1);
	trim_trailing_whitespace(*dest);
	return (0);
}
