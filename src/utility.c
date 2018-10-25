/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 11:35:05 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:01:40 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>

t_lem_in_room		make_room(char *name, int x, int y, t_list *neighbors)
{
	t_lem_in_room	ret;

	ret.name = name;
	ret.x = x;
	ret.y = y;
	ret.neighbors = neighbors;
	return (ret);
}

char				*get_name(char *line)
{
	char			*ends;
	int				len;

	ends = ft_strchr(line, ' ');
	if (ends == NULL)
		return (NULL);
	len = ft_strlen(line) - ft_strlen(ends);
	if (len < 1)
		return (NULL);
	return (ft_strsub(line, 0, len));
}

int					get_coord(char *line, char variant)
{
	char			*ends;
	int				lens[3];

	ends = ft_strchr(line, ' ');
	if (ends == NULL || (lens[0] = ft_strlen(line) - ft_strlen(ends)) < 1)
		return (-1);
	if (variant == 1)
		return (ft_atoi(ends + 1));
	ends = ft_strchr(ends + 1, ' ');
	if (ends == NULL || (lens[1] = ft_strlen(line) - ft_strlen(ends) - lens[0]) < 1)
		return (-1);
	if (variant == 2)
		return (ft_atoi(ends + 1));
	return (-1);
}

char				is_valid_room(char *line)
{
	size_t			i;
	size_t			len;

	if (line[0] == '#')
		return (1);
	if (line[0] == 'L')
		return (0);
	i = 0;
	len = ft_strlen(line);
	while (i < len && line[i] != ' ')
		++i;
	if (i == len)
		return (0);
	++i;
	while (i < len && ft_isdigit(line[i]))
		++i;
	if (i == len || line[i] != ' ')
		return (0);
	++i;
	if (!ft_isdigit(line[i]))
		return (0);
	while (i < len && ft_isdigit(line[i]))
		++i;
	return (i == len ? 1 : 0);
}

char				is_valid_link(char *line)
{
	size_t			i;
	size_t			len;

	if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		return (0);
	if (line[0] == '#')
		return (1);
	if (line[0] == 'L')
		return (0);
	i = 0;
	len = ft_strlen(line);
	while (i < len && line[i] != '-')
		++i;
	if (i == len || line[i + 1] == '\0')
		return (0);
	return (1);
}

char				has_element(t_list *list, t_lem_in_room *room)
{
	t_lem_in_room	*tmp;

	while (list && room)
	{
		tmp = (t_lem_in_room *)list->content;
		if (ft_strequ(tmp->name, room->name) && tmp->x == room->x
			&& tmp->y == room->y)
			return (1);
		if (ft_strequ(tmp->name, room->name))
			return (2);
		list = list->next;
	}
	return (0);
}

t_list				*find_element(t_list *list, char *name)
{
	while (list)
	{
		if (ft_strequ(((t_lem_in_room *)list->content)->name, name))
			return (list);
		list = list->next;
	}
	return (NULL);
}

char				*ft_strjoin_nl_with_free_dst(char *dst, char *new_part)
{
	char			*tmp;

	tmp = dst;
	dst = ft_strjoin(tmp, new_part);
	ft_strdel(&tmp);
	tmp = dst;
	dst = ft_strjoin(tmp, "\n");
	ft_strdel(&tmp);
	return (dst);
}