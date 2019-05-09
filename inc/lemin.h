#ifndef LEMIN_H
# define LEMIN_H

# include "../../libft/inc/libft_types.h"

typedef struct	s_graph
{
	char		*node;
	t_list		*neighbours;
}				t_graph;

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
/*
**			utility.c
*/
int				add_room(t_farm *farm, char *room_name, int room_type);
int				add_link(t_farm *farm, char *link);

#endif