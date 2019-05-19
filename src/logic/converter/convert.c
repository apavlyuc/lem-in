#include "../../../inc/lemin.h"
#include "../../../libft/inc/libft.h"
#include <stdlib.h>

static int		get_node_id(t_data *data, char *name)
{
	int			i;

	i = 0;
	while (i < data->count_of_nodes)
	{
		if (ft_strequ(data->nodes[i].name, name))
			return (i);
		++i;
	}
	ft_putendl("::get_node_id error");
	//add deleters
	exit(1);
}

static void		init_link_by_name(t_data *data, t_farm *farm, char *name, int i)
{
	t_binding	*binding;
	t_list		*tmp;
	t_link		**link;

	binding = find_binding(farm->links, name);
	data->nodes[i].links_count = 0;
	link = &data->nodes[i].link;
	tmp = binding->neighbours;
	while (tmp)
	{
		if (!*link)
		{
			*link = create_link(ft_strdup((char *)tmp->content),\
			get_node_id(data, (char *)tmp->content));
		}
		data->nodes[i].links_count++;
		tmp = tmp->next;
		link = &((*link)->next);
	}
}

static void		add_links(t_data *data, t_farm *farm)
{
	int			i;
	char		*name;

	i = 0;
	while (i < data->count_of_nodes)
	{
		name = data->nodes[i].name;
		init_link_by_name(data, farm, name, i);
		++i;
	}
}

static void		convert_from_list_to_vector(t_data *data, t_farm *farm)
{
	int			i;
	t_list		*tmp;

	i = 2;
	tmp = farm->rooms;
	while (tmp)
	{
		if (ft_strequ(farm->start_room_name, (char *)tmp->content))
		{
			data->nodes[0].name = ft_strdup((char *)tmp->content);
			data->nodes[0].link = 0;
		}
		else if (ft_strequ(farm->finish_room_name, (char *)tmp->content))
		{
			data->nodes[1].name = ft_strdup((char *)tmp->content);
			data->nodes[1].link = 0;
		}
		else
		{
			data->nodes[i].name = ft_strdup((char *)tmp->content);
			data->nodes[i].link = 0;
			i++;
		}
		tmp = tmp->next;
	}
	add_links(data, farm);
}

void			change_data_type(t_data *data, t_farm *farm)
{
	data->count_of_nodes = get_list_size(farm->rooms);
	data->nodes = (t_node *)ft_memalloc(sizeof(t_node) * data->count_of_nodes);
	convert_from_list_to_vector(data, farm);
}
