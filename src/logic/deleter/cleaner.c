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