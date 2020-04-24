/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:15:34 by lspiess           #+#    #+#             */
/*   Updated: 2019/11/15 21:16:45 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stringft.h"
#include "memft.h"

size_t		strlcpy(char *dst, const char *src, size_t maxlen)
{
	size_t		srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < maxlen)
	{
		ft_memcpy(dst, src, srclen + 1);
	}
	else if (maxlen != 0)
	{
		ft_memcpy(dst, src, maxlen - 1);
		dst[maxlen - 1] = '\0';
	}
	return (srclen);
}
