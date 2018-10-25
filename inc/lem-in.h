/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 10:20:13 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:01:37 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <libft.h>

# ifndef LEM_IN_DATA
#  define LEM_IN_DATA
typedef struct	s_lem_in_data
{
	char		*full_input;
	int			ants;
	t_list		*rooms;
	char		*start_name;
	char		*end_name;
}				t_lem_in_data;
# endif

# ifndef LEM_IN_ROOM
#  define LEM_IN_ROOM
typedef struct	s_lem_in_room
{
	char		*name;
	int			x;
	int			y;
	t_list		*neighbors;
}				t_lem_in_room;
# endif
/*
**				parse.c
*/
char			parse(t_lem_in_data *dst);
/*
**				links_validator.c
*/
char			parse_neighbors(t_lem_in_data *data, char *link);
/*
**				utility.c
*/
t_lem_in_room	make_room(char *name, int x, int y, t_list *neighbors);
char			*get_name(char *line);
int				get_coord(char *line, char variant);
char			is_valid_room(char *line);
char			is_valid_link(char *line);
char			has_element(t_list *list, t_lem_in_room *room);
t_list			*find_element(t_list *list, char *name);
char			*ft_strjoin_nl_with_free_dst(char *dst, char *new_part);
/*
**				print.c
*/
void			print_all(t_lem_in_data *data);
/*
**				delete.c
*/
void			delete_all(t_lem_in_data *data);
#endif