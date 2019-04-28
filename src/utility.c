#include "../libft/inc/libft.h"
#include "../inc/lemin.h"

void		add_room(t_farm **farm, char *room_name, int room_type)
{
	t_ull	size;

	if (room_type == 1)
		(*farm)->start_room_name = ft_strdup(room_name);
	else if (room_type == 2)
		(*farm)->finish_room_name = ft_strdup(room_name);
	size = ft_strlen(room_name);
	if ((*farm)->rooms == 0)
		(*farm)->rooms = ft_lstnew((void *)room_name, size + 1);
	else
		ft_lstadd_before(farm, ft_lstnew((void *)room_name, size + 1));
}