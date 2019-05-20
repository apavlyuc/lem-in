#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

static void		first_path_in_scenario(t_data *data, int index, t_path *path, int ants)
{
	data->count_of_scenarios++;
	data->scenarios[index].paths = path;
	data->scenarios[index].complexity = 1;
	data->scenarios[index].id = path->length + ants - 1;
	if (data->mn_var < 0 || data->mn_var > data->scenarios[index].id)
		data->mn_var = data->scenarios[index].id;
}

static int		cmp_path_with_scenario(t_scenario *scen, t_path *path)
{
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
					return (1);
				}
				new = new->step_forward;
			}
			step = step->step_forward;
		}
		tmp = tmp->next_branch;
	}
	return (0);
}

static int		try_add_path_to_scenario(t_data *data, t_farm *farm, t_path *path)
{
	t_path		*tmp;
	int			i;

	i = -1;
	while (++i < data->count_of_scenarios)
	{
		if (cmp_path_with_scenario(data->scenarios + i, path))
			continue;
		tmp = data->scenarios[i].paths;
		data->scenarios[i].complexity++;
		while (tmp->next_branch)
			tmp = tmp->next_branch;
		tmp->next_branch = path;
		shuffle_party(data, farm, i);
		return (0);
	}
	return (1);
}

static void		add_path(t_data *data, t_path *to_add, t_farm *farm)
{
	static int	i;

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
			del_steps(to_add);
		}
	}
}

static int		check_is_amount(t_data *data, t_path **tmp, t_path **path, t_path **prev)
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

static int		check_paths(t_data *data, t_path **tmp, t_path **path, t_path **prev)
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
	del_steps(*tmp);
	if (*tmp == *path)
		*path = step;
	else
		(*prev)->next_branch = step;
	*tmp = step;
	return (1);
}

static int		follow_the_paths(t_data *data, t_farm *farm, t_path *path)
{
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
				return (1);
			}
			if (check_paths(data, &tmp, &path, &prev))
				continue;
			prev = tmp;
			tmp = tmp->next_branch;
		}
	}
	return (0);
}

void			handle_superposition(t_data *data, t_farm *farm)
{
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
	if (follow_the_paths(data, farm, new))
		clear_path(&new);
}