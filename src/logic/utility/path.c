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