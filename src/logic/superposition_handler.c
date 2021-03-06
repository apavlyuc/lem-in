/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superposition_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:40 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/05/25 16:22:27 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

static void		first_path_in_scenario(\
					t_data *data, int index, t_path *path, int ants)
{
	data->count_of_scenarios++;
	data->scenarios[index].paths = path;
	data->scenarios[index].complexity = 1;
	data->scenarios[index].id = path->length + ants - 1;
	if (data->mn_var < 0 || data->mn_var > data->scenarios[index].id)
		data->mn_var = data->scenarios[index].id;
}

static int		try_add_path_to_scenario(\
					t_data *data, t_farm *farm, t_path *path)
{
	t_path		*tmp;
	int			i;

	i = -1;
	while (++i < data->count_of_scenarios)
	{
		if (compare(data->scenarios + i, path))
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

void			add_path(t_data *data, t_path *to_add, t_farm *farm)
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
			del_steps(to_add);
	}
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
				return (1);
			if (run_from_norme1(data, &tmp, &path, &prev))
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
