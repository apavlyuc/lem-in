
#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

static int		read_ants(t_farm *farm)
{
	char		*line;

	if (get_next_line(0, &line) == -1)
		return (0);
	ft_putendl(line);
	farm->ants_count = ft_atoi(line);
	ft_memdel((void **)&line);
	return (farm->ants_count > 0 ? 1 : 0);
}

static int		read_rooms(t_farm *farm, char **line)
{
	int			gnl_ret_code;
	int			room_type;

	room_type = 0;
	while ((gnl_ret_code = get_next_line(0, line)) >= 0)
	{
		ft_putendl(*line);
		if (is_valid_room(*line))
		{
			if (add_room(farm, *line, room_type) == 0)
				break;
			room_type = 0;
		}
		else if (is_valid_command(*line))
		{
			room_type = get_next_room_type(*line);
		}
		else if (!is_valid_comment(*line))
			break;
		ft_memdel((void **)line);
	}
	return (gnl_ret_code == -1 ? 0 : 1);
}

static int		read_links(t_farm *farm)
{
	char		*line;
	int			gnl_ret_code;

	while ((gnl_ret_code = get_next_line(0, &line)) >= 0)
	{
		ft_putendl(line);
		if (is_valid_link(line))
		{
			add_link(farm, line);
		}
		else if (!is_valid_comment(line) && !is_valid_command(line))
		{
			ft_memdel((void **)&line);
			return (1);
		}
		ft_memdel((void **)&line);
	}
	ft_putendl("");
	return (1);
}

int				read_farm(t_farm *farm)
{
	char		*first_link;

	if (read_ants(farm) == 0)
		return (0);
	if (read_rooms(farm, &first_link) == 0)
		return (0);
	if (is_valid_link(first_link))
	{
		add_link(farm, first_link);
		ft_memdel((void **)&first_link);
		if (read_links(farm) == 0)
		{
			ft_putendl("ERROR");
			return (0);
		}
		return (1);
	}
	ft_memdel((void **)&first_link);
	return (0);
}