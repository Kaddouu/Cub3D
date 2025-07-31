/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:54:38 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/14 13:13:10 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buffer(int fd, char *buffer, int *reader)
{
	*reader = read(fd, buffer, BUFFER_SIZE);
	if (*reader < 0)
		return (NULL);
	buffer[*reader] = '\0';
	return (buffer);
}

static char	*buffer_to_cache(int fd, char *cache)
{
	char	*buffer;
	int		reader;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(cache), NULL);
	reader = 1;
	while (!ft_strchr(cache, '\n') && reader > 0)
	{
		if (!read_buffer(fd, buffer, &reader))
			return (free(cache), free(buffer), NULL);
		temp = ft_strjoin(cache, buffer);
		if (!temp)
			return (free(buffer), free(cache), NULL);
		free(cache);
		cache = temp;
	}
	free(buffer);
	return (cache);
}

static char	*extract_line(char *cache, size_t *i)
{
	char	*line;

	*i = 0;
	while (cache[*i] && cache[*i] != '\n')
		(*i)++;
	line = ft_substr(cache, 0, *i + (cache[*i] == '\n'));
	return (line);
}

static char	*cache_to_line(char **cache)
{
	size_t	i;
	char	*line;
	char	*temp;

	if (!*cache || !**cache)
		return (free(*cache), *cache = NULL, NULL);
	line = extract_line(*cache, &i);
	if (!line)
		return (free(*cache), *cache = NULL, NULL);
	if ((*cache)[i] == '\n')
	{
		temp = ft_strdup(*cache + i + 1);
		if (!temp)
			return (free(line), free(*cache), *cache = NULL, NULL);
	}
	else
		temp = NULL;
	free(*cache);
	*cache = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(cache), cache = NULL, NULL);
	if (!cache)
	{
		cache = malloc(1);
		if (!cache)
			return (NULL);
		cache[0] = '\0';
	}
	cache = buffer_to_cache(fd, cache);
	if (!cache)
		return (NULL);
	line = cache_to_line(&cache);
	if (!line && cache)
		return (free(cache), cache = NULL, NULL);
	return (line);
}
