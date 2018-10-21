/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:11:07 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:37:33 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_replace(char *s, char from, char to)
{
	int i;

	i = 0;
	if (from == '\0' || to == '\0' || !from || !to || !s)
		return ;
	while (s[i] != '\0')
	{
		if (s[i] == from)
			ft_memset(&s[i], to, 1);
		i++;
	}
}
