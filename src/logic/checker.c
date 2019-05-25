/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:53:02 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/05/25 15:56:40 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

static void		clone_except_last(t_path **path, t_path *tmp, int id)
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

static int		check_node_in_path(t_data *data, t_path **path, t_path *tmp, int id)
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

int				compare(t_scenario *scen, t_path *path)
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
					return (1);
				new = new->step_forward;
			}
			step = step->step_forward;
		}
		tmp = tmp->next_branch;
	}
	return (0);
}

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

int				check_paths(t_data *data, t_path **tmp, t_path **path, t_path **prev)
{
	t_path		*step;

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
