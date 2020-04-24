/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:24:33 by lspiess           #+#    #+#             */
/*   Updated: 2019/04/15 13:31:35 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	unsigned long	i;
	unsigned long	len;

	len = ft_strlen(s);
	i = 0;
	while ((i < len) && (s[i] != (char)c))
		i++;
	if (i == len)
	{
		if (c != '\0')
		{
			return (NULL);
		}
	}
	return ((char *)(&(s[i])));
}
