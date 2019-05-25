/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:54:11 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/05/25 15:54:12 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/inc/libft.h"
#include "../../../inc/lemin.h"

static void			print_item(int ant, char *name)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}

static int		print_round(t_data *data, t_path *path, int ant, int total)
{
	int			tmp_amount;

	tmp_amount = path->amount;
	while (path->step_forward)
	{
		if (path->step_forward->ant > 0)
		{
			print_item(path->step_forward->ant, data->nodes[path->id].name);
			path->ant = path->step_forward->ant;
			path->step_forward->ant = 0;
		}
		else if (!path->step_forward->id)
		{
			if (total - ant + 1 > tmp_amount && total >= ant)
			{
				print_item(ant, data->nodes[path->id].name);
				path->ant = ant++;
			}
		}
		path = path->step_forward;
	}
	return (ant);
}

static void		just_print_scenario(t_data *data, t_farm *farm, int index)
{
	t_scenario	*scenario;
	t_path		*path;
	int			lines;
	int			ant;

	ant = 1;
	scenario = index == -1 ? data->bad_scenario : data->scenarios + index;
	lines = scenario->id;
	scenario->paths->amount = 0;
	while (scenario->id-- > 0)
	{
		path = scenario->paths;
		while (path)
		{
			ant = print_round(data, path, ant, farm->ants_count);
			path = path->next_branch;
		}
		ft_putchar('\n');
	}
	ft_putstr("\nLines: ");
	ft_putnbr(lines);
	ft_putchar('\n');
}

static void		run_clever_print(t_data *data, t_farm *farm)
{
	int			i;

	i = 0;
	while (i < data->count_of_scenarios)
	{
		if (data->scenarios[i].id == data->mn_var)
			just_print_scenario(data, farm, i);
		++i;
	}
}

void			choose_printing_logic(t_data *data, t_farm *farm)
{
	if (data->count_of_paths < 4)
	{
		handle_superposition(data, farm);
		if (data->mn_var == -1 || data->mn_var > data->bad_scenario->id)
			just_print_scenario(data, farm, -1);
		else
			run_clever_print(data, farm);
	}
	else
	{
		just_print_scenario(data, farm, 0);
	}
}
