
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

static int		read_rooms(t_farm *farm, char **line)
{
	int			gnl_ret_code;
	int			room_type;

	room_type = 0;
	while ((gnl_ret_code = get_next_line(0, line)))
	{
		if (is_valid_room(*line))
		{
			add_room(&farm, get_room_name(*line), room_type);
		}
		else if (is_valid_comment(*line))
		{
			room_type = get_next_room_type(*line);
		}
		else
			break;
		ft_memdel((void **)line);
	}
	if (gnl_ret_code == -1)
		return (0);
	return (1);
}

static int		read_links(t_farm *farm, char **first_link)
{
	(void)farm;
	(void)first_link;
	return (1);
}

int				read_farm(t_farm *farm)
{
	char		*first_link;

	if (read_ants(farm) == 0)
		return (0);
	if (read_rooms(farm, &first_link) == 0)
		return (0);
	if (read_links(farm, &first_link) == 0)
		return (0);
	return (1);
}