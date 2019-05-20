#include "../../../libft/inc/libft.h"
#include "../../../inc/lemin.h"

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

void			del_steps(t_path *path)
{
	t_path *tmp;

	while (path)
	{
		tmp = path->step_forward;
		ft_memdel((void **)&path);
		path = tmp;
	}
}