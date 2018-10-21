/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 16:18:39 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:27:22 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void		*ft_memalloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL || size < 1)
		return (NULL);
	ft_bzero(result, size);
	return (result);
}
