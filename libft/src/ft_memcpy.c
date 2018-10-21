/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 12:34:35 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:28:01 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str;
	unsigned int	i;

	str = (unsigned char *)src;
	i = 0;
	while (n > 0)
	{
		ft_memset(&dst[i], str[i], 1);
		i++;
		n--;
	}
	return (dst);
}
