#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

int				add_room(t_farm *farm, char *room, int room_type)
{
	char		*room_name;
	t_ull		size;

	if (room_type == 1 && farm->start_room_name)
		return (0);
	if (room_type == 2 && farm->finish_room_name)
		return (0);
	room_name = get_room_name(room);
	if (room_type == 1)
		farm->start_room_name = ft_strdup(room_name);
	else if (room_type == 2)
		farm->finish_room_name = ft_strdup(room_name);
	size = ft_strlen(room_name);
	if (farm->rooms == 0)
		farm->rooms = ft_lstnew((void *)room_name, size + 1);
	else
		ft_lstadd_before(&(farm->rooms), ft_lstnew((void *)room_name, size + 1));
	ft_memdel((void **)&room_name);
	return (1);
}

void			process_room(t_list **links, char *room, char *neighbour)
{
	t_binding	*binding;

	if (!(binding = find_binding(*links, room)))
	{
		add_binding(links, create_binding(room, neighbour));
	}
	else
	{
		add_neighbour(binding, neighbour);
	}
}

int				add_link(t_farm *farm, char *link)
{
	char		*room1;
	char		*room2;

	room1 = get_link_part(link, 1);
	room2 = get_link_part(link, 2);
	process_room(&(farm->links), room1, room2);
	process_room(&(farm->links), room2, room1);
	ft_memdel((void **)&room1);
	ft_memdel((void **)&room2);
	return (1);
}