#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"
#include <stdlib.h>

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







// void			run_clever_print(t_data *data, t_farm *farm)
// {
// 	ft_putendl("start:\t run_clever_print");
// 	int			i;

// 	i = 0;
// 	while (i < data->count_of_scenarios)
// 	{
// 		if (data->scenarios[i].id == data->mn_var)
// 			just_print_scenario(data, farm, i);
// 		++i;
// 	}
// 	ft_putendl("end:\t run_clever_print");
// }

// void			choose_printing_logic(t_data *data, t_farm *farm)
// {
// 	ft_putendl("start:\t choose_printing_logic");
// 	if (data->count_of_paths < 4)
// 	{
// 		handle_superposition(data, farm);
// 		printf("%d %d\n", data->mn_var, data->bad_scenario->id);
// 		if (data->mn_var == -1 || data->mn_var > data->bad_scenario->id)
// 			just_print_scenario(data, farm, -1);
// 		else
// 			run_clever_print(data, farm);
// 	}
// 	else
// 	{
// 		just_print_scenario(data, farm, 0);
// 	}
// 	ft_putendl("end:\t choose_printing_logic");
// }





static void		init_data(t_data *data)
{
	data->nodes = 0;
	data->paths = 0;
	data->scenarios = 0;
	data->bad_scenario = 0;
	data->farm = 0;
	data->count_of_nodes = 0;
	data->count_of_paths = 0;
	data->count_of_scenarios = 0;
	data->mn_var = -1;
}

void			play_game(t_farm *farm)
{
	t_data		data;

	init_data(&data);
	data.farm = farm;
	change_data_type(&data, farm);
	if (find_simple_path(&data, farm))
		ft_putendl("ERROR: isn't enough information");
	else
		choose_printing_logic(&data, farm);
	clear_data(&data);
}
