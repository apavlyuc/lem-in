#include "../../libft/inc/libft.h"

int				get_next_room_type(char *line)
{
	if (ft_strequ(line, "##start"))
		return (1);
	if (ft_strequ(line, "##end"))
		return (2);
	return (3);
}

char			*get_room_name(char *line)
{
	char		*name;
	char		*first_space_entry;

	first_space_entry = ft_strchr(line, ' ');
	name = ft_strsub(line, 0, first_space_entry - line);
	return (name);
}