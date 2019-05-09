#include "../libft/inc/libft.h"
#include "../inc/lemin.h"

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

t_binding		*find_binding(t_list *links, char *node)
{
	t_binding	*ret;

	ret = 0;
	while (links)
	{
		ret = (t_binding *)links->content;
		if (ft_strequ(ret->node, node))
			break;
		links = links->next;
		ret = 0;
	}
	return (ret);
}

t_binding		*create_binding(char *node, char *neighbour)
{
	t_binding	*ret;

	ret = (t_binding *)ft_memalloc(sizeof(t_binding));
	ret->node = ft_strdup(node);
	ret->neighbours = ft_lstnew(neighbour, ft_strlen(neighbour));
	return (ret);
}

void			add_neighbour(t_binding *binding, char *name)
{
	t_list		*new_neighbour;

	if (!binding || !(binding->neighbours))
		return;
	new_neighbour = ft_lstnew(name, ft_strlen(name));
	ft_lstadd_before(&binding->neighbours, new_neighbour);
}

void			add_binding(t_list **links, t_binding *binding)
{
	t_list		*new_item;

	new_item = ft_lstnew(0, 0);
	new_item->content = binding;
	new_item->content_size = sizeof(*binding);
	if (!*links)
		*links = new_item;
	else
		ft_lstadd_before(links, new_item);
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
	return (1);
}