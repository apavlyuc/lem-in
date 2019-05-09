#include "../../libft/inc/libft.h"

int				get_next_room_type(char *line)
{
	if (ft_strequ(line, "##start"))
		return (1);
	if (ft_strequ(line, "##end"))
		return (2);
	return (3);
}

char			*get_room_name(char *line)
{
	char		*name;
	char		*first_space_entry;

	first_space_entry = ft_strchr(line, ' ');
	name = ft_strsub(line, 0, first_space_entry - line);
	return (name);
}

char			*get_link_part(char *link, int part)
{
	char		*ret;
	t_ull		len_to_cut;
	t_ull		cut_from;

	ret = 0;
	if (part == 1)
	{
		cut_from = 0;
		len_to_cut = ft_strlen(link) - ft_strlen(ft_strchr(link, '-'));
		ret = ft_strsub(link, cut_from, len_to_cut);
	}
	else if (part == 2)
	{
		cut_from = ft_strlen(link) - ft_strlen(ft_strchr(link, '-')) + 1;
		len_to_cut = ft_strlen(link) - cut_from;
		ret = ft_strsub(link, cut_from, len_to_cut);
	}
	return (ret);
}