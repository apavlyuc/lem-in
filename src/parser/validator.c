/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:54:02 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/05/25 15:29:24 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

int				is_valid_room(char const *room)
{
	t_ull const	size = ft_strlen(room);
	char		*x_entry_point;
	char		*y_entry_point;

	if (size == 0 || *room == '#' || *room == 'L')
		return (0);
	x_entry_point = ft_strchr(room, ' ');
	if (!x_entry_point || !ft_isdigit(*(++x_entry_point)))
		return (0);
	y_entry_point = ft_strchr(x_entry_point, ' ');
	if (!y_entry_point || !ft_isdigit(*(++y_entry_point)))
		return (0);
	return (1);
}

int				is_valid_command(char const *command)
{
	t_ull const	size = ft_strlen(command);

	if (size < 2)
		return (0);
	if (command[0] != '#' || command[1] != '#')
		return (0);
	return (1);
}

int				is_valid_comment(char const *comment)
{
	t_ull const	size = ft_strlen(comment);

	if (size < 1)
		return (0);
	if (comment[0] == '#' && comment[1] != '#')
		return (1);
	return (0);
}

int				is_valid_link(char const *link)
{
	t_ull const	size = ft_strlen(link);

	if (size < 3)
		return (0);
	if (*link == '#' || *link == 'L')
		return (0);
	if (ft_strchr(link, '-') == 0)
		return (0);
	return (1);
}

int				validate_farm(t_farm *farm)
{
	if (!farm->start_room_name || !farm->finish_room_name)
		return (0);
	if (!farm->rooms || !farm->links)
		return (0);
	if (!find_binding(farm->links, farm->start_room_name) ||
		!find_binding(farm->links, farm->finish_room_name))
		return (0);
	return (1);
}
