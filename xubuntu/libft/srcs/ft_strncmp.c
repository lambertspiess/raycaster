/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 18:26:32 by lspiess           #+#    #+#             */
/*   Updated: 2019/04/14 19:08:52 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *us1;
	unsigned char *us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 && *us2 && n)
	{
		if (*us1 - *us2 != 0)
			return (*us1 - *us2);
		us1++;
		us2++;
		n--;
	}
	if (n)
		return (*us1 - *us2);
	return (0);
}
