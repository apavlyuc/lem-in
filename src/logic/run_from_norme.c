/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_from_norme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:17:10 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/05/25 16:21:10 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lemin.h"

int			run_from_norme1(\
					t_data *data, t_path **t, t_path **pt, t_path **pr)
{
	if (check_is_amount(data, t, pt, pr))
		return (1);
	if (check_paths(data, t, pt, pr))
		return (1);
	return (0);
}
