/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 13:18:56 by vonischu          #+#    #+#             */
/*   Updated: 2018/10/25 15:53:28 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

char				*get_line(char **s)
{
	char	*line;
	size_t	size;
	int		flag;

	flag = 0;
	if (ft_strchr(*s, '\n'))
	{
		size = ft_strchr(*s, '\n') - *s;
		flag = 1;
	}
	else
		size = ft_strlen(*s);
	line = ft_strncpy(ft_strnew(size), *s, size);
	*s += (size + flag);
	return (line);
}

t_list				*handle_file(t_list **all, int fd)
{
	t_list	*f;
	t_f		temp;

	f = *all;
	while (f)
	{
		if (((t_f*)f->content)->fd == fd)
			return (f);
		f = f->next;
	}
	temp.s = ft_strnew(1);
	temp.start = temp.s;
	temp.fd = fd;
	ft_lstadd(all, ft_lstnew((void*)&temp, sizeof(t_f)));
	return (*all);
}

int					get_next_line(int fd, char **line)
{
	static t_list	*all;
	t_list			*f;
	char			buf[BUFF_SIZE + 1];
	size_t			count;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	f = handle_file(&all, fd);
	while ((count = read(fd, buf, BUFF_SIZE)))
	{
		buf[count] = '\0';
		if (!(((t_f*)f->content)->s = ft_strjoin(((t_f*)f->content)->s, buf)))
			return (-1);
		ft_strdel(&((t_f*)f->content)->start);
		((t_f*)f->content)->start = ((t_f*)f->content)->s;
		if (ft_strchr(((t_f*)f->content)->s, '\n'))
			break ;
	}
	if (count < BUFF_SIZE && !ft_strlen(((t_f*)f->content)->s))
		return (0);
	if (!(*line = get_line(&((t_f*)f->content)->s)))
		return (-1);
	return (1);
}
