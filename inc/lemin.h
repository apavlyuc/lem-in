#ifndef LEMIN_H
# define LEMIN_H

# include "../../libft/inc/libft_types.h"
# include <stdio.h>

typedef struct	s_binding
{
	char		*node;
	t_list		*neighbours;
}				t_binding;

typedef struct	s_farm
{
	t_list		*rooms;
	t_list		*links;
	char		*start_room_name;
	char		*finish_room_name;
	int			ants_count;
}				t_farm;

/*
**			parser/reader.c
*/
int				read_farm(t_farm *farm);
/*
**			parser/validator.c
*/
int				validate_farm(t_farm *farm);
int				is_valid_room(char *room);
int				is_valid_link(char *link);
int				is_valid_command(char *command);
int				is_valid_comment(char *comment);
/*
**			parser/getters.c
*/
int				get_next_room_type(char *line);
char			*get_room_name(char *line);
char			*get_link_part(char *link, int part);
/*
**			utility/farm.c
*/
int				add_room(t_farm *farm, char *room_name, int room_type);
int				add_link(t_farm *farm, char *link);
/*
**			utility/binding.c
*/
t_binding		*find_binding(t_list *links, char *node);
t_binding		*create_binding(char *node, char *neighbour);
void			add_neighbour(t_binding *binding, char *name);
void			add_binding(t_list **links, t_binding *binding);

#endif