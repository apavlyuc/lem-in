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