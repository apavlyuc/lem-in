/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:44:22 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:45:05 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

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
	if (ends == NULL || (lens[1] = ft_strlen(line) - ft_strlen(ends) -
		lens[0]) < 1)
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
