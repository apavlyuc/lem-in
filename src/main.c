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

static void		delete_link_binding(t_list *link)
{
	t_binding	*binding;

	if (!link || !link->content)
		return;
	binding = (t_binding *)link->content;
	ft_memdel((void **)&(binding->node));
	ft_lstdel(&(binding->neighbours), ft_del_handler);
}

static void		delete_farm_fields(t_farm *farm)
{
	t_list		*link_to_clean;

	ft_memdel((void **)&farm->start_room_name);
	ft_memdel((void **)&farm->finish_room_name);
	ft_lstdel(&(farm->rooms), ft_del_handler);
	link_to_clean = farm->links;
	while (link_to_clean)
	{
		delete_link_binding(link_to_clean);
		link_to_clean = link_to_clean->next;
	}
	ft_lstdel(&(farm->links), ft_del_handler);
}

int				main(int ac, char **av)
{
	t_farm		game_info;

	(void)ac;
	(void)av;
	set_to_zero_state(&game_info);
	if (read_farm(&game_info) == 0)
	{
		delete_farm_fields(&game_info);
		return (1);
	}
	if (validate_farm(&game_info) == 0)
	{
		ft_putendl("ERROR");
		delete_farm_fields(&game_info);
		return (2);
	}
	ft_putendl("DEBUG: valid");
	//print_all(&game_info);
	play_game(&game_info);
	delete_farm_fields(&game_info);
	return (0);
}