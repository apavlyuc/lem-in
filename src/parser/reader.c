
#include "../../../libft/inc/libft.h"
#include "../../inc/lemin.h"

static int		read_ants(t_farm *farm)
{
	char		*line;

	if (get_next_line(0, &line) == -1)
		return (0);
	ft_putstr(line);
	farm->ants_count = ft_atoi(line);
	ft_memdel((void **)&line);
	return (1);
}

static int		read_rooms(t_farm *farm)
{
	(void)farm;
	return (1);
}

static int		read_links(t_farm *farm)
{
	(void)farm;
	return (1);
}

int				read_farm(t_farm *farm)
{
	if (read_ants(farm) == 0)
		return (0);
	if (read_rooms(farm) == 0)
		return (0);
	if (read_links(farm) == 0)
		return (0);
	return (1);
}