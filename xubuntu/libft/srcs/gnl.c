/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:48:22 by lspiess           #+#    #+#             */
/*   Updated: 2020/01/10 17:24:54 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000

int			gnl_strchr(char *s)
{
	unsigned	i;

	if (s == NULL)
		return (0);
	else
	{
		i = 0;
		while (s[i])
		{
			if (s[i] == '\n')
				return (1);
			i++;
		}
		return (0);
	}
}

void		gnl_getline(char **hpp, char **linep)
{
	size_t		i;
	char		*newheap;

	i = 0;
	while ((*hpp)[i])
	{
		if ((*hpp)[i] == '\n')
			break ;
		i++;
	}
	if (i == 0)
		*linep = ft_strdup("");
	else
		*linep = ft_strndup(*hpp, i);
	if (i == ft_strlen(*hpp))
	{
		free(*hpp);
		*hpp = NULL;
		return ;
	}
	newheap = ft_strdup(*hpp + i + 1);
	ft_free((void **)(hpp));
	*hpp = newheap;
}

void		gnl_strnjoin(char **hpp, char *app, int n)
{
	size_t		heaplen;
	char		*new;
	size_t		i;
	int			j;

	heaplen = ft_strlen(*hpp);
	new = malloc(heaplen + n + 1);
	i = 0;
	while (i < heaplen)
	{
		new[i] = (*hpp)[i];
		i++;
	}
	j = 0;
	while (j < n)
	{
		new[i] = app[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(*hpp);
	*hpp = new;
}

static int	gnl_end(char **heapp, char **linep)
{
	if (*heapp == NULL)
	{
		*linep = ft_strdup("");
		return (0);
	}
	gnl_getline(heapp, linep);
	if (*heapp == NULL)
		return (0);
	return (1);
}

int			get_next_line(char **linep, int fd)
{
	int			rdret;
	char		buf[BUFFER_SIZE];
	static char	*heap = NULL;

	if (read(fd, buf, 0) < 0 || linep == NULL)
		return (-1);
	if (heap != NULL && gnl_strchr(heap) == 1)
	{
		gnl_getline(&heap, linep);
		if (heap != NULL)
			return (1);
	}
	while (1)
	{
		rdret = read(fd, buf, BUFFER_SIZE);
		if (rdret <= 0)
			break ;
		if (heap == NULL)
			heap = ft_strndup(buf, rdret);
		else
			gnl_strnjoin(&heap, buf, rdret);
		if (gnl_strchr(heap) == 1)
			break ;
	}
	return (gnl_end(&heap, linep));
}
