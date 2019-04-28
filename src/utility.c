#include "../libft/inc/libft.h"
#include "../inc/lemin.h"

int		add_room(t_farm **farm, char *room, int room_type)
{
	char	*room_name;
	t_ull	size;

	if (room_type == 1 && (*farm)->start_room_name)
		return (0);
	if (room_type == 2 && (*farm)->finish_room_name)
		return (0);
	room_name = get_room_name(room);
	if (room_type == 1)
		(*farm)->start_room_name = ft_strdup(room_name);
	else if (room_type == 2)
		(*farm)->finish_room_name = ft_strdup(room_name);
	size = ft_strlen(room_name);
	if ((*farm)->rooms == 0)
		(*farm)->rooms = ft_lstnew((void *)room_name, size + 1);
	else
		ft_lstadd_before(&((*farm)->rooms), ft_lstnew((void *)room_name, size + 1));
	ft_memdel((void **)&room_name);
	return (1);
}