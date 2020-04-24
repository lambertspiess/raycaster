/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:31:58 by lspiess           #+#    #+#             */
/*   Updated: 2019/08/24 19:02:33 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** counts the number of chars inside a string (null-term excluded)
*/

int		ft_istrlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
