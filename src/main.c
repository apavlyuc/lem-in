#include "../libft/inc/libft.h"
#include "../inc/lemin.h"

static void		set_to_zero_state(t_farm *farm)
{
	farm->ants_count = 0;
	farm->links = 0;
	farm->rooms = 0;
	farm->start_room_name = 0;
	farm->finish_room_name = 0;
}

int				main(int ac, char **av)
{
	t_farm		game_info;

	(void)ac;
	(void)av;
	turn_on_garbage_collector();
	set_to_zero_state(&game_info);
	if (read_farm(&game_info) == 0)
	{
		clear_garbage_collector();
		return (1);
	}
	if (validate_farm(&game_info) == 0)
	{
		ft_putendl("ERROR");
		clear_garbage_collector();
		return (2);
	}
	play_game(&game_info);
	clear_garbage_collector();
	return (0);
}
