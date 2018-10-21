/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:29:10 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 19:00:28 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

static int			ft_copy(char *dup, t_dat *node)
{
	while (*node->p != '\0' && *node->p != '\n')
	{
		*dup = *node->p;
		node->p++;
		dup++;
	}
	return (*node->p == '\n' ? 2 : 3);
}

static int			ft_read(t_dat *node, char **dup, int res, int len)
{
	int				n;
	char			*big;

	*dup = ft_strnew(BUFF_SIZE);
	res = ft_copy(*dup, node);
	len = ft_strlen(*dup);
	while (res == 3)
	{
		ft_bzero(node->buff, BUFF_SIZE);
		if ((n = read(node->fd, node->buff, BUFF_SIZE)) == 0 && len == 0)
			return (0);
		if (n == -1)
			return (-1);
		node->p = node->buff;
		if (*node->p == '\0')
			return (1);
		big = ft_strnew(ft_strlen(*dup) + BUFF_SIZE);
		ft_strcpy(big, *dup);
		ft_strdel(dup);
		res = ft_copy(&big[len], node);
		len += node->p - node->buff;
		*dup = big;
	}
	*node->p == '\n' ? node->p++ : node->p;
	return (1);
}

static void			ft_null(t_dat *node, int fd)
{
	node->fd = fd;
	node->p = node->buff;
	ft_bzero(node->buff, BUFF_SIZE + 1);
	node->next = NULL;
}

static t_dat		*ft_set(t_dat **head, int fd)
{
	t_dat			*node;
	t_dat			*cursor;

	if (*head == NULL)
	{
		node = malloc(sizeof(t_data));
		ft_null(node, fd);
		*head = node;
		return (node);
	}
	cursor = *head;
	while (cursor != NULL && cursor->next != NULL && cursor->fd != fd)
		cursor = cursor->next;
	if (cursor->fd == fd)
		return (cursor);
	node = malloc(sizeof(t_data));
	cursor->next = node;
	ft_null(node, fd);
	return (node);
}

int					get_next_line(const int fd, char **line)
{
	static t_dat	*head = NULL;
	t_dat			*node;
	char			*dup;
	int				res;
	int				len;

	len = 0;
	res = 0;
	if (fd == -1 || line == NULL)
		return (-1);
	node = ft_set(&head, fd);
	res = ft_read(node, &dup, res, len);
	if (res == 1)
	{
		*line = dup;
		return (1);
	}
	ft_strdel(&dup);
	return (res == 0 ? 0 : -1);
}
