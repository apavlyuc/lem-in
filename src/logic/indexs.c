#include "../../inc/lemin.h"
#include "../../libft/inc/libft.h"

static void		set_unused(t_node *node, int len)
{
	int			i;

	i = -1;
	while (++i < len)
	{
		if (node[i].used == 9)
			continue;
		node[i].used = 0;
		node[i].index = 0;
	}
}

static void		process_near(t_node *nodes, t_link *center, t_link *near)
{
	int			near_index;
	int			main_index;

	near_index = nodes[near->id].index;
	main_index = nodes[center->id].index;
	if (near_index == 0 || near_index > main_index + 1)
	{
		if (nodes[near->id].used != 9)
			nodes[near->id].index = main_index + 1;
	}
	if (nodes[near->id].used == 0)
	{
		nodes[near->id].used = 1;
		append_to_link(center, create_link(0, near->id));
	}
}

void			reinit_nodes_indexs(t_data *data, t_farm *farm, t_link *near)
{
	t_link		*center;

	(void)farm;
	set_unused(data->nodes, data->count_of_nodes);
	data->nodes[0].used = 1;
	center = create_link(0, 0);
	while (center)
	{
		near = data->nodes[center->id].link;
		while (near)
		{
			process_near(data->nodes, center, near);
			near = near->next;
		}
		near = center->next;
		ft_memdel((void **)&center);
		center = near;
	}
	data->nodes[0].index = 0;
}