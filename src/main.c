#include "../libft/inc/libft.h"
#include "../inc/lemin.h"

void			print_all(t_farm *farm)
{
	printf("ants: %d\n", farm->ants_count);
	printf("start_room: %s\n", farm->start_room_name);
	printf("finish_room: %s\n", farm->finish_room_name);
	printf("\nrooms:\n");
	t_list *tmp_room = farm->rooms;
	while (tmp_room)
	{
		printf("%s\t", (char *)tmp_room->content);
		tmp_room = tmp_room->next;
	}
	printf("\n\nlinks:\n");
	t_list *tmp_link = farm->links;
	while (tmp_link)
	{
		t_binding *tmp = (t_binding *)tmp_link->content;
		printf("bind: %s -> [", tmp->node);
		t_list *tmp_neighbour = tmp->neighbours;
		while (tmp_neighbour)
		{
			printf(" %s ", (char *)tmp_neighbour->content);
			tmp_neighbour = tmp_neighbour->next;
		}
		printf("]\n");
		tmp_link = tmp_link->next;
	}
	printf("nice :3\n");
}

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
