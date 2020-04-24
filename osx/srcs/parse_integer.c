/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:44:18 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 18:04:57 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

int			ft_is_unsigned(char *s)
{
	size_t		i;

	if (s == NULL)
		return (FALSE);
	i = 0;
	while (s[i] && s[i] != ',')
	{
		if ('0' <= s[i] && s[i] <= '9')
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

static int	rt_is_digit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static int	rt_is_whitespace(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r' \
		|| c == '\n' || c == ' ')
		return (1);
	return (0);
}

int			ft_rt_atoi(const char *str)
{
	long long int	res;
	int				i;
	int				sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && rt_is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && rt_is_digit(str[i]) && str[i] != ',')
	{
		res = ((res * 10) + (str[i] - '0'));
		i++;
	}
	return ((int)res * sign);
}
