#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

static int		get_amount(t_path *path, int len)
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

static void		set_paths_amount(t_data *data, int index)
{
	t_path		*tmp;

	tmp = data->scenarios[index].paths;
	tmp->amount = 0;
	tmp = tmp->next_branch;
	while (tmp)
	{
		tmp->amount = -1;
		tmp->amount = get_amount(data->scenarios[index].paths, tmp->length);
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