#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

int				is_valid_room(char *room)
{
	t_ull		size;
	char		*x_entry_point;
	char		*y_entry_point;

	size = ft_strlen(room);
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

int				is_valid_comment(char *comment)
{
	(void)comment;
	return (1);
}

int				is_valid_link(char *link)
{
	(void)link;
	return (1);
}

int				validate_farm(t_farm *farm)
{
	(void)farm;
	return (1);
}