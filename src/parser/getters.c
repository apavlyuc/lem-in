#include "../../libft/inc/libft.h"

int				get_next_room_type(char *line)
{
	(void)line;
	return (1);
}

char			*get_room_name(char *line)
{
	char		*name;
	char		*first_space_entry;

	first_space_entry = ft_strchr(line, ' ');
	name = ft_strsub(line, 0, first_space_entry - line);
	return (name);
}