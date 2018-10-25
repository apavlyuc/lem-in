/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:46:14 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:46:30 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

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
