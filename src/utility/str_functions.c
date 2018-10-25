/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:47:45 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:47:53 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

char				*ft_strjoin_nl_with_free_dst(char *dst, char *new_part)
{
	char			*tmp;

	tmp = dst;
	dst = ft_strjoin(tmp, new_part);
	ft_strdel(&tmp);
	tmp = dst;
	dst = ft_strjoin(tmp, "\n");
	ft_strdel(&tmp);
	return (dst);
}
