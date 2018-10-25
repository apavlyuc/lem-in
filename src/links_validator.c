/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:55:52 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:12:39 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>

static void			add_link(t_list **list, char *name)
{
	if (*list == NULL)
		*list = ft_lstnew(name, ft_strlen(name));
	else
	{
		while ((*list)->next)
		{
			if (ft_strequ((char *)((*list)->content), name))
				return;
			*list = (*list)->next;
		}
		(*list)->next = ft_lstnew(name, ft_strlen(name));
	}
}

static char			check_links(t_list *rooms, char **names)
{
	t_list			*tmp1;
	t_list			*tmp2;

	tmp1 = find_element(rooms, names[0]);
	tmp2 = find_element(rooms, names[1]);
	if (tmp1 && tmp2)
	{
		add_link(&((t_lem_in_room *)tmp1->content)->neighbors, names[1]);
		add_link(&((t_lem_in_room *)tmp2->content)->neighbors, names[0]);
	}
	free(names[0]);
	free(names[1]);
	free(names);
	return ((!tmp1 || !tmp2) ? 1 : 0);
}

char				parse_neighbors(t_lem_in_data *data, char *line)
{
	int				ret;
	int				gnl;

	ret = 0;
	if (line[0] != '#')
		ret = check_links(data->rooms, ft_strsplit(line, '-'));
	data->full_input = ft_strjoin_nl_with_free_dst(data->full_input, line);
	ft_strdel(&line);
	gnl = 1;
	while (ret != 1 && (gnl = get_next_line(0, &line)) > 0)
	{
		data->full_input = ft_strjoin_nl_with_free_dst(data->full_input, line);
		if (is_valid_link(line))
		{
			if (line[0] != '#')
				ret = check_links(data->rooms, ft_strsplit(line, '-'));
		}
		else
			ret = 1;
		ft_strdel(&line);
	}
	return (ret);
}
