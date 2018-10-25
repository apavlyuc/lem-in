/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 10:21:33 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:31:32 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>

static void			init_nulls(t_lem_in_data *data)
{
	data->full_input = NULL;
	data->rooms = NULL;
	data->start_name = NULL;
	data->end_name = NULL;
}

int					main()
{
	t_lem_in_data	data;
	int				err;

	init_nulls(&data);
	err = parse(&data);
	if (!err)
		print_all(&data);
	else	
		delete_all(&data);
	//system("leaks lem-in");
	return (0);
}