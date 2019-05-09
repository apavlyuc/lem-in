#include "../libft/inc/libft.h"
#include "../inc/lemin.h"

#include <unistd.h>

static void	set_to_zero_state(t_farm *farm)
{
	farm->ants_count = 0;
	farm->links = 0;
	farm->rooms = 0;
	farm->start_room_name = 0;
	farm->finish_room_name = 0;
}

static void	delete_farm_fields(t_farm *farm)
{
	ft_memdel((void **)&farm->start_room_name);
	ft_memdel((void **)&farm->finish_room_name);
	ft_lstdel(&(farm->rooms), ft_del_handler);
	ft_lstdel(&(farm->links), ft_del_handler);
}

int			main(int ac, char **av)
{
	t_farm	game_info;

	(void)ac;
	(void)av;
	set_to_zero_state(&game_info);
	if (read_farm(&game_info) == 0 || validate_farm(&game_info) == 0)
	{
		delete_farm_fields(&game_info);
		return (-1);
	}

	delete_farm_fields(&game_info);
	return (0);
}