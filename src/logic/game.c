#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"
#include <stdlib.h>
/*
**		here would be smth like that
**
**		1) convert lists to arrays (optional)
**		2) legacy "algorithm_big"
**		3) cycle-part of legacy "main"
**			3.1) legacy "find_ways" and "print_lem"
**				OR
**			3.2) legacy "print_lem"
*/
typedef struct	s_link {
	char		*name;
	int			id;
	struct s_link		*next;
}				t_link;

typedef struct	s_node {
	int			used;
	int			index;
	char		*name;
	t_link		*link;
	int			links_count;
	//t_node		*next;// может быть мусор
}				t_node;

typedef struct	s_path {
	int			length;
	int			id;
	//int			has_ant;
	int			amount;
	struct s_path		*step_forward;
	struct s_path		*next_branch;
}				t_path;

typedef struct	s_scenario {
	t_path		*paths;
	int			id;//?
	int			complexity;
}				t_scenario;

typedef struct	s_data {
	t_node		*nodes;
	int			count_of_nodes;
	t_path		*paths;
	int			count_of_paths;
	t_scenario	*bad_scenario;
	t_scenario	*scenarios;
	int			count_of_scenarios;
	int			mn_var;
}				t_data;

t_ull			get_list_size(t_list *lst)
{
	t_ull		ret;

	ret = 0;
	while (lst)
	{
		lst = lst->next;
		++ret;
	}
	return (ret);
}

int				get_node_id(t_data *data, char *name)
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
	exit(1);
}

t_link			*create_link(char *name, int id);
void			init_link_by_name(t_data *data, t_farm *farm, char *name, int i)
{
	ft_putendl("start:\t init_link_by_name");
	t_binding	*binding;
	t_list		*tmp;
	t_link		**link;
	//int			j;

	binding = find_binding(farm->links, name);
	data->nodes[i].links_count = 0;//get_list_size(binding->neighbours);
	//data->nodes[i].link = (t_link *)ft_memalloc(sizeof(t_link) * data->nodes[i].links_count);
	link = &data->nodes[i].link;
	tmp = binding->neighbours;
	//j = 0;
	while (tmp)
	{
		if (!*link)
		{
			//ft_putendl("ready to create... ");
			*link = create_link(ft_strdup((char *)tmp->content),\
			get_node_id(data, (char *)tmp->content));
			//ft_putendl("created");
		}
		//if (!*link)
		//ft_putendl("link == null");
		//data->nodes[i].link[j].name = ft_strdup((char *)tmp->content);
		//data->nodes[i].link[j].id = get_node_id(data, (char *)tmp->content);
		//data->nodes[i].link[j].next = data->nodes[i].links_count >= j + 1 ? 0 : &data->nodes[i].link[j + 1];
		printf("for node:[%s] -> add link[%s] with id[%d]\n", data->nodes[i].name, (*link)->name, (*link)->id);
		//++j;
		data->nodes[i].links_count++;
		tmp = tmp->next;
		//ft_putendl("before link++");
		//printf("%lu\n", (unsigned long int)*link);
		//printf("%lu\n", (unsigned long int)&(*link)->next);
		link = &((*link)->next);
		printf("end\n");
	}
	ft_putendl("start:\t init_link_by_name");
}

void			add_links(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t add_links");
	int			i;
	char		*name;

	i = 0;
	while (i < data->count_of_nodes)
	{
		name = data->nodes[i].name;
		init_link_by_name(data, farm, name, i);
		++i;
	}
	ft_putendl("end:\t add_links");
}

void			convert_from_list_to_vector(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t convert_from_list_to_vector");
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
			printf("add node: %s\n", data->nodes[0].name);
		}
		else if (ft_strequ(farm->finish_room_name, (char *)tmp->content))
		{
			data->nodes[1].name = ft_strdup((char *)tmp->content);
			data->nodes[1].link = 0;
			printf("add node: %s\n", data->nodes[1].name);
		}
		else
		{
			data->nodes[i].name = ft_strdup((char *)tmp->content);
			data->nodes[i].link = 0;
			printf("add node: %s\n", data->nodes[i].name);
			i++;
		}
		tmp = tmp->next;
	}
	add_links(data, farm);
	ft_putendl("end:\t convert_from_list_to_vector");
}

void			change_data_type(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t change_data_type");
	data->count_of_nodes = get_list_size(farm->rooms);
	printf("count of nodes: %d\n", data->count_of_nodes);
	data->nodes = (t_node *)ft_memalloc(sizeof(t_node) * data->count_of_nodes);
	convert_from_list_to_vector(data, farm);
	ft_putendl("start:\t change_data_type");
}





t_link			*create_link(char *name, int id)
{
	t_link		*ret;

	ret = (t_link *)ft_memalloc(sizeof(t_link));
	ret->name = name;
	ret->id = id;
	ret->next = 0;
	return (ret);
}

void			set_unused(t_node *node, int len)
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

void			append_to_link(t_link *link, t_link *new)
{
	while (link->next)
	{
		link = link->next;
	}
	link->next = new;
}

void			process_near(t_node *nodes, t_link *center, t_link *near)
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
	ft_putendl("start:\t reinit_nodes_indexs");
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
	ft_putendl("end:\t reinit_nodes_indexs");
}

void			append_path(t_data *data, t_path *new)
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
	ft_putendl("end: append_path");
}

t_path			*create_path(int length, int id, t_path *branch, t_path *step)
{
	t_path		*ret;

	ret = (t_path *)ft_memalloc(sizeof(t_path));
	ret->id = id;
	ret->length = length;
	ret->next_branch = branch;
	ret->step_forward = step;
	return (ret);
}

int				get_potential_id(t_node *nodes, t_link *curr, int ret, int id)
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

t_link			*get_link_at(t_node *node, int index)
{
	int			i;
	t_link		*ret;

	i = 0;
	ret = node->link;
	while (i < index && ret)
	{
		ret = ret->next;
		++i;
	}
	return (index == i ? ret : 0);
}

void			go_to_next_node(t_data *data, t_path *path, int id)
{
	int			ret;
	int			i;

	ret = data->nodes[id].link->id;
	i = 0;
	while (i < data->nodes[id].links_count)
	{
		//ret = get_potential_id(data->nodes, data->nodes[id].link + i, ret, id);
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

t_path			*get_path(t_data *data)
{
	ft_putendl("start:\t get_path");
	t_path		*path;

	path = create_path(1, data->nodes[1].index, 0, 0);
	go_to_next_node(data, path, 1);
	ft_putendl("end:\t get_path");
	return (path);
}

void			delete_first_link_by_id(t_data *data, int id, t_link *prev, t_link *next)
{
	ft_putendl("start:\t delete_first_link_by_id");
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
	ft_putendl("end:\t delete_first_link_by_id");
}



void			set_paths_amount(t_data *data, int index)
{
	t_path		*tmp;
	//t_path		*tmp1;

	data->scenarios[index].paths->amount = 0;
	tmp = data->scenarios[index].paths->next_branch;
	while (tmp)
	{
		//tmp1 = tmp;
		//while (tmp1)
		//{
		//}
		tmp->amount = -1;
		//tmp->amount = -1;//::count_steps
		tmp = tmp->next_branch;
	}
}

void			shuffle_party(t_data *data, t_farm *farm, int index)
{
	int			ants_count;
	int			used_paths_count;
	t_path		*tmp;

	set_paths_amount(data, index);
	ants_count = farm->ants_count;
	used_paths_count = data->scenarios[index].paths->length - 1;
	while (ants_count)
	{
		++used_paths_count;
		tmp = data->scenarios[index].paths;
		while (tmp)
		{
			if (ants_count > tmp->amount)
				--ants_count;
			tmp = tmp->next_branch;
		}
	}
	data->scenarios[index].id = used_paths_count;
	data->mn_var = data->mn_var > used_paths_count ? used_paths_count : data->mn_var;
}

void			process_parties(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t process_parties");
	data->scenarios = (t_scenario *)ft_memalloc(sizeof(t_scenario));
	data->scenarios->paths = data->paths;
	data->scenarios->complexity = data->count_of_paths;
	shuffle_party(data, farm, 0);
	ft_putendl("end:\t process_parties");
}

int				collect_paths(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t collect_paths");
	while (1)
	{
		reinit_nodes_indexs(data, farm, 0);
		if (data->nodes[1].index == 0)
			break;
		append_path(data, get_path(data));
		if (data->nodes[1].index == 1)
		{
			delete_first_link_by_id(data, 1, 0, 0);
			ft_putendl("BREAK");
			//break;//DELETE
		}
	}
	if (!data->count_of_paths)
		return (1);
	process_parties(data, farm);
	ft_putendl("end:\t collect_paths");
	return (0);
}




void			just_print_scenario(t_data *data, t_farm *farm, int index)
{
	(void)data;
	(void)farm;
	(void)index;
}

void			follow_the_path(t_data *data, t_farm *farm, t_path *path)
{
	(void)data;
	(void)farm;
	(void)path;
}

void			run_finder(t_data *data, t_farm *farm)
{
	t_path		*new;
	int			i;

	i = 0;
	while (i < data->count_of_nodes)
	{
		data->nodes[i].index = 0;
		data->nodes[i].used = 0;
	}
	data->paths = 0;
	data->bad_scenario = data->scenarios;
	data->scenarios = 0;
	new = create_path(1, 0, 0, 0);
	follow_the_path(data, farm, new);
}

void			run_clever_print(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t run_clever_print");
	int			i;

	i = 0;
	while (i < data->count_of_scenarios)
	{
		if (data->scenarios[i].complexity == data->mn_var)
			just_print_scenario(data, farm, i);
		++i;
	}
	ft_putendl("end:\t run_clever_print");
}

void			choose_printing_logic(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t choose_printing_logic");
	if (data->count_of_paths < 4)
	{
		run_finder(data, farm);
		if (data->mn_var == -1 || data->mn_var > data->bad_scenario->complexity)
			just_print_scenario(data, farm, -1);
		else
			run_clever_print(data, farm);
	}
	else
	{
		just_print_scenario(data, farm, 0);
	}
	ft_putendl("end:\t choose_printing_logic");
}




void			clear_data(t_data *data)
{
	ft_putendl("start:\t clear_data");
	int			i;
	t_link		*tmp;

	i = 0;
	while (i < data->count_of_nodes)
	{
		ft_memdel((void **)&data->nodes[i].name);
		tmp = data->nodes[i].link;
		while (tmp)
		{
			ft_memdel((void **)&tmp->name);
			tmp = tmp->next;
		}
		ft_memdel((void **)&data->nodes[i].link);
		++i;
	}
	ft_memdel((void **)&data->nodes);
	ft_putendl("end:\t clear_data");
}




void			play_game(t_farm *farm)
{
	t_data		data;

	data.nodes = 0;
	data.paths = 0;
	data.mn_var = -1;
	change_data_type(&data, farm);
	if (collect_paths(&data, farm))
		ft_putendl("ERROR: isn't enough information");
	else
		choose_printing_logic(&data, farm);
	clear_data(&data);
}
