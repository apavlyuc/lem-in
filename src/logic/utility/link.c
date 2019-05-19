#include "../../../inc/lemin.h"
#include "../../../libft/inc/libft.h"

t_ull			get_list_size(t_list *lst)
{
	t_ull		ret;

	ret = 0;
	while (lst)
	{
		lst = lst->next;
		++ret;
	}
	return (ret);
}

t_link			*create_link(char *name, int id)
{
	t_link		*ret;

	ret = (t_link *)ft_memalloc(sizeof(t_link));
	ret->name = name;
	ret->id = id;
	ret->next = 0;
	return (ret);
}