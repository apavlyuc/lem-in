#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

static void		append_path(t_data *data, t_path *new)
{
	t_path		*tmp;

	data->count_of_paths++;
	if (data->paths == 0)
	{
		data->paths = new;
		return;
	}
	tmp = data->paths;
	while (tmp->next_branch)
	{
		tmp = tmp->next_branch;
	}
	tmp->next_branch = new;
}

static void		delete_first_link_by_id(t_data *data, int id, t_link *prev, t_link *next)
{
	t_link		*tmp;

	prev = 0;
	next = 0;
	tmp = data->nodes[0].link;
	while (tmp)
	{
		if (tmp->id == id)
		{
			next = tmp->next;
			break;
		}
		else
			prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		ft_memdel((void **)&tmp->name);
		ft_memdel((void **)&tmp);
		if (prev)
			prev->next = next;
		else
			data->nodes[0].link = next;
	}
}

static void		process_parties(t_data *data, t_farm *farm)
{
	data->scenarios = (t_scenario *)ft_memalloc(sizeof(t_scenario));
	data->scenarios->paths = data->paths;
	data->scenarios->complexity = data->count_of_paths;
	shuffle_party(data, farm, 0);
}

static int		get_potential_id(t_node *nodes, t_link *curr, int ret, int id)
{
	static int	mark;

	if ((id == 0 && mark == 1) || curr->id == 0 || nodes[ret].used == 9 ||
	(nodes[curr->id].index < nodes[ret].index && nodes[curr->id].used != 9))
	{
		if (id != 1 || curr->id != 0 || mark != 1)
			ret = curr->id;
		if (id == 0 && curr->id == 0 && mark == 0)
			++mark;
	}
	return (ret);
}

static void		go_to_next_node(t_data *data, t_path *path, int id)
{
	int			ret;
	int			i;

	ret = data->nodes[id].link->id;
	i = 0;
	while (i < data->nodes[id].links_count)
	{
		ret = get_potential_id(data->nodes, get_link_at(data->nodes + id, i), ret, id);
		++i;
	}
	path->step_forward = create_path(0, ret, 0, 0);
	if (ret)
	{
		data->nodes[ret].used = 9;
		go_to_next_node(data, path->step_forward, ret);
	}
}

static t_path	*get_path(t_data *data)
{
	t_path		*path;

	path = create_path(data->nodes[1].index, 1, 0, 0);
	go_to_next_node(data, path, 1);
	return (path);
}

int				find_simple_path(t_data *data, t_farm *farm)
{
	while (1)
	{
		reinit_nodes_indexs(data, farm, 0);
		if (data->nodes[1].index == 0)
			break;
		append_path(data, get_path(data));
		if (data->nodes[1].index == 1)
			delete_first_link_by_id(data, 1, 0, 0);
	}
	if (!data->count_of_paths)
		return (1);
	process_parties(data, farm);
	return (0);
}