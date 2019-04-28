#ifndef LEMIN_H
# define LEMIN_H

# include "../../libft/inc/libft_types.h"

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

#endif