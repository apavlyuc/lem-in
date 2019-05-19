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
	int			ant;
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
	t_farm		*farm;
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
	printf("start:\t create_path\n");
	t_path		*ret;

	ret = (t_path *)ft_memalloc(sizeof(t_path));
	ret->id = id;
	ret->length = length;
	ret->next_branch = branch;
	ret->step_forward = step;
	printf("end:\t create_path\n");
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

	path = create_path(data->nodes[1].index, 1, 0, 0);
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


int				get_amount(t_path *path, int len)
{
	int res;

	res = 0;
	while (path)
	{
		if (path->amount == -1)
			break ;
		res += len - path->length;
		path = path->next_branch;
	}
	return (res);
}




void			set_paths_amount(t_data *data, int index)
{
	t_path		*tmp;
	//t_path		*tmp1;

	tmp = data->scenarios[index].paths;
	tmp->amount = 0;
	tmp = tmp->next_branch;
	printf("index = %d\n", index);
	while (tmp)
	{
		//tmp1 = tmp;
		//while (tmp1)
		//{
		//}
		tmp->amount = -1;
		tmp->amount = get_amount(data->scenarios[index].paths, tmp->length);
		tmp = tmp->next_branch;
		//printf("prt: %lu\n", (unsigned long int)tmp->next_branch);
	}
}

void			shuffle_party(t_data *data, t_farm *farm, int index)
{
	printf("start:\t shuffle_party\n");
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
	printf("end:\t shuffle_party\n");
}

void			process_parties(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t process_parties");
	data->scenarios = (t_scenario *)ft_memalloc(sizeof(t_scenario));
	
	data->scenarios->paths = data->paths;
	data->scenarios->complexity = data->count_of_paths;
	//printf("%d\n", data->count_of_paths);
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




void			print_item(int ant, char *name)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
	//printf("WTF");
	//printf("L%d-%s ", ant, name);
}

int				print_round(t_data *data, t_path *path, int ant, int total)
{
	int			tmp_amount;

	tmp_amount = path->amount;
	while (path->step_forward)
	{
		if (path->step_forward->ant > 0)//?
		{
			//printf("IN IF: L%d-%s ", path->step_forward->ant, data->nodes[path->id].name);
			print_item(path->step_forward->ant, data->nodes[path->id].name);
			path->ant = path->step_forward->ant;
			path->step_forward->ant = 0;
		}
		else if (!path->step_forward->id)
		{
			if (total - ant + 1 > tmp_amount && total >= ant)
			{
				print_item(ant, data->nodes[path->id].name);
				path->ant = ant++;
			}
		}
		path = path->step_forward;
	}
	return (ant);
}

void			just_print_scenario(t_data *data, t_farm *farm, int index)
{
	ft_putendl("start:\t just_print_scenario");
	t_scenario	*scenario;
	t_path		*path;
	int			lines;
	int			ant;

	ant = 1;
	lines = 0;
	scenario = index == -1 ? data->bad_scenario : data->scenarios + index;
	printf("here, index = %d\n", index);
	//if ((data->scenarios + index)->paths->amount)
	//	printf("a\n");
	scenario->paths->amount = 0;
	//data->scenarios[index].paths->amount = 0;
	printf("here\n");
	//printf("paths = %d\n", data->scenarios[index].id);
	//exit(1);
	while (scenario->id-- > 0)
	//while (data->scenarios[index].id-- > 0)
	{
		path = scenario->paths;
		//path = data->scenarios[index].paths;
		while (path)
		{
			ant = print_round(data, path, ant, farm->ants_count);
			path = path->next_branch;
		}
		ft_putchar('\n');
		//printf("\n");
		lines++;
	}
	//printf("\nLines: %d\n", lines);
	ft_putstr("\nLines: ");
	ft_putnbr(lines);
	ft_putchar('\n');
	//exit(1);
	ft_putendl("end:\t just_print_scenario");
}





void			del_path(t_path *path)
{
	t_path *tmp;

	while (path)
	{
		tmp = path->step_forward;
		free(path);
		path = tmp;
	}
}

void			delete_path(t_path **path)
{
	t_path		*branch;
	t_path		*step;
	t_path		*tmp;

	branch = *path;
	while (branch)
	{
		step = branch->step_forward;
		while (step)
		{
			tmp = step->step_forward;
			free(step);
			step = tmp;
		}
		tmp = branch->next_branch;
		free(branch);
		branch = tmp;
	}
}

void			first_path_in_scenario(t_data *data, int index, t_path *path, int ants)//first_way_in_group
{
	printf("start:\t first_path_in_scenario\n");
	data->count_of_scenarios++;
	data->scenarios[index].paths = path;
	data->scenarios[index].complexity = 1;
	data->scenarios[index].id = path->length + ants - 1;
	if (data->mn_var < 0 || data->mn_var > data->scenarios[index].id)
		data->mn_var = data->scenarios[index].id;
	printf("end:\t first_path_in_scenario\n");
}

int				cmp_path_with_scenario(t_scenario *scen, t_path *path)
{
	printf("start:\t cmp_path_with_scenario\n");
	t_path *tmp;
	t_path *step;
	t_path *new;

	tmp = scen->paths;
	while (tmp)
	{
		step = tmp->step_forward;
		while (step->step_forward)
		{
			new = path->step_forward;
			while (new->step_forward)
			{
				if (new->id == step->id)
				{
					printf("end:\t cmp_path_with_scenario\n");
					return (1);
				}
				new = new->step_forward;
			}
			step = step->step_forward;
		}
		tmp = tmp->next_branch;
	}
	printf("end:\t cmp_path_with_scenario\n");
	return (0);
}

int				try_add_path_to_scenario(t_data *data, t_farm *farm, t_path *path)
{
	printf("start:\t try_add_path_to_scenario\n");
	t_path		*tmp;
	int			i;

	i = -1;
	while (++i < data->count_of_scenarios)
	{
		if (cmp_path_with_scenario(data->scenarios + i, path))
			continue;
		printf("1. %lu\n", (unsigned long int)data->scenarios[1].paths);
		printf("1. %lu\n", (unsigned long int)data->scenarios[1].paths->next_branch);
		//printf("1. %lu\n", (unsigned long int)data->scenarios[1].paths->next_branch->next_branch);
		tmp = data->scenarios[i].paths;
		data->scenarios[i].complexity++;
		while (tmp->next_branch)
			tmp = tmp->next_branch;
		tmp->next_branch = path;
		printf("i = %d\n", i);
		printf("2. %lu\n", (unsigned long int)data->scenarios[1].paths);
		printf("2. %lu\n", (unsigned long int)data->scenarios[1].paths->next_branch);
		printf("2. %lu\n", (unsigned long int)data->scenarios[1].paths->next_branch->next_branch);
		shuffle_party(data, farm, i);
		printf("end:\t try_add_path_to_scenario\n");
		return (0);
	}
	printf("end:\t try_add_path_to_scenario\n");
	return (1);
}

void			add_path(t_data *data, t_path *to_add, t_farm *farm)//add_way_in_struct
{
	printf("start:\t add_path\n");
	static int	i;
	//t_path		*tmp;

	to_add->next_branch = 0;
	if (i == 0)
	{
		data->scenarios = (t_scenario *)ft_memalloc(sizeof(t_scenario) * 4);
		first_path_in_scenario(data, i++, to_add, farm->ants_count);
	}
	else if (try_add_path_to_scenario(data, farm, to_add))
	{
		if (i < 4)
			first_path_in_scenario(data, i++, to_add, farm->ants_count);
		else
		{
			del_path(to_add);
		}
	}
	printf("end:\t add_path\n");
}

// ↑ ::add_way_in_struct
// ↓ ::check_all_ways


int				check_is_amount(t_data *data, t_path **tmp, t_path **path, t_path **prev)
{
	t_path		*step;

	if ((*tmp)->amount == 0)
		return (0);
	step = (*tmp)->next_branch;
	add_path(data, *tmp, data->farm);
	if (*tmp == *path)
		*path = step;
	else
		(*prev)->next_branch = step;
	*tmp = step;
	return (1);
}

int				is_node_in_path(t_path *path, int id)
{
	while (path)
	{
		if (path->id == id)
			return (1);
		path = path->step_forward;
	}
	return (0);
}

void			add_node_to_path(t_path *path, int id)
{
	if (id == 0)
		path->amount = 1;
	path->length++;
	while (path->step_forward)
		path = path->step_forward;
	path->step_forward = create_path(0, id, 0, 0);
}

void			clone_except_last(t_path **path, t_path *tmp, int id)
{
	t_path		*new;
	t_path		*ret;

	new = create_path(tmp->length, tmp->id, 0, 0);
	ret = new;
	tmp = tmp->step_forward;
	if (id == 0)
		new->amount = 1;
	while (tmp->step_forward)
	{
		new->step_forward = create_path(0, tmp->id, 0, 0);
		new = new->step_forward;
		tmp = tmp->step_forward;
	}
	new->step_forward = create_path(0, id, 0, 0);
	ret->next_branch = *path;
	*path = ret;
}

int				check_node_in_path(t_data *data, t_path **path, t_path *tmp, int id)
{
	t_link		*link;
	int			i;

	i = 0;
	link = data->nodes[id].link;
	while (link)
	{
		if(!is_node_in_path(tmp, link->id))
		{
			if (i == 0)
			{
				add_node_to_path(tmp, link->id);
				i++;
			}
			else
				clone_except_last(path, tmp, link->id);
		}
		link = link->next;
	}
	return (i);
}

int				check_paths(t_data *data, t_path **tmp, t_path **path, t_path **prev)
{
	t_path		*step;

	if (check_is_amount(data, tmp, path, prev))
		return (1);
	step = *tmp;
	while (step->step_forward)
		step = step->step_forward;
	if (check_node_in_path(data, path, *tmp, step->id))
		return (0);
	step = (*tmp)->next_branch;
	del_path(*tmp);
	if (*tmp == *path)
		*path = step;
	else
		(*prev)->next_branch = step;
	*tmp = step;
	return (1);
}

int				follow_the_paths(t_data *data, t_farm *farm, t_path *path)
{
	printf("start:\t follow_the_paths\n");
	t_path		*tmp;
	t_path		*prev;

	while (path)
	{
		prev = path;
		if (path->amount)
		{
			tmp = path->next_branch;
			add_path(data, path, farm);
			path = tmp;
			continue;
		}
		tmp = path;
		while (tmp)
		{
			if (data->mn_var > 0 && tmp->length >= data->mn_var)
			{
				printf("end:\t follow_the_paths RET\n");
				return (1);
			}
			if (check_paths(data, &tmp, &path, &prev))
				continue;
			prev = tmp;
			tmp = tmp->next_branch;
		}
	}
	printf("end:\t follow_the_paths\n");
	return (0);
}

void			handle_superposition(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t handle_superposition");
	t_path		*new;
	int			i;

	i = 0;
	while (i < data->count_of_nodes)
	{
		data->nodes[i].index = 0;
		data->nodes[i].used = 0;
		i++;
	}
	reinit_nodes_indexs(data, farm, 0);
	data->paths = 0;
	data->bad_scenario = data->scenarios;
	data->scenarios = 0;
	new = create_path(0, 1, 0, 0);
	if (follow_the_paths(data, farm, new))//cycle_way
		delete_path(&new);
	ft_putendl("end:\t handle_superposition");
}







void			run_clever_print(t_data *data, t_farm *farm)
{
	ft_putendl("start:\t run_clever_print");
	int			i;

	i = 0;
	while (i < data->count_of_scenarios)
	{
		if (data->scenarios[i].id == data->mn_var)
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
		handle_superposition(data, farm);
		printf("%d %d\n", data->mn_var, data->bad_scenario->id);
		if (data->mn_var == -1 || data->mn_var > data->bad_scenario->id)
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




void			print_all_data(t_data *data)
{
	t_path		*path1, *path2;

	path1 = path2 = data->scenarios[0].paths;
	while (path1)
	{
		while (path1)
		{
			printf("%s-", data->nodes[path1->id].name);
			path1 = path1->step_forward;
		}
		path1 = path2->next_branch;
		path2 = path1;
	}
	printf("\n");
}

void			play_game(t_farm *farm)
{
	t_data		data;

	data.nodes = 0;
	data.paths = 0;
	data.mn_var = -1;
	data.count_of_paths = 0;
	data.farm = farm;
	change_data_type(&data, farm);
	if (collect_paths(&data, farm))
		ft_putendl("ERROR: isn't enough information");
	else
	{
		//print_all_data(&data);
		choose_printing_logic(&data, farm);
	}
	clear_data(&data);
}
