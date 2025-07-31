/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/06/15 19:40:47 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	trim_whitespace(char *str)
{
	int	start;
	int	end;
	int	i;

	if (!str)
		return ;
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t'
			|| str[end] == '\n' || str[end] == '\r'))
		end--;
	i = 0;
	while (start <= end)
	{
		str[i] = str[start];
		i++;
		start++;
	}
	str[i] = '\0';
}

static int	check_sign_and_advance(char *str, int *i)
{
	if (str[*i] == '+' || str[*i] == '-')
		(*i)++;
	if (!str[*i])
		return (0);
	return (1);
}

int	is_valid_number_string(char *str)
{
	int	i;

	if (!str || ft_strlen(str) == 0)
		return (0);
	i = 0;
	if (!check_sign_and_advance(str, &i))
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	trim_trailing_whitespace(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len
				- 1] == '\n' || str[len - 1] == '\r'))
	{
		str[len - 1] = '\0';
		len--;
	}
}
