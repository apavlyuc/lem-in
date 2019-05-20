#include "../../../libft/inc/libft.h"
#include "../../../inc/lemin.h"

void			clear_data(t_data *data)
{
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
}

void			clear_path(t_path **path)
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
			ft_memdel((void **)&step);
			step = tmp;
		}
		tmp = branch->next_branch;
		ft_memdel((void **)&branch);
		branch = tmp;
	}
}
