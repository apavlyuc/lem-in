#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"
#include <stdlib.h>

static void		init_data(t_data *data)
{
	data->nodes = 0;
	data->paths = 0;
	data->scenarios = 0;
	data->bad_scenario = 0;
	data->farm = 0;
	data->count_of_nodes = 0;
	data->count_of_paths = 0;
	data->count_of_scenarios = 0;
	data->mn_var = -1;
}

void			play_game(t_farm *farm)
{
	t_data		data;

	init_data(&data);
	data.farm = farm;
	change_data_type(&data, farm);
	if (find_simple_path(&data, farm))
		ft_putendl("ERROR: isn't enough information");
	else
		choose_printing_logic(&data, farm);
	clear_data(&data);
}
