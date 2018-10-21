/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 20:04:50 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:32:29 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(dst);
	if (dstsize > len)
	{
		ft_strncat(dst, src, (dstsize - len - 1));
		ft_memset(&dst[dstsize - 1], '\0', 1);
	}
	if (dstsize < len)
		return (dstsize + ft_strlen(src));
	else
		return (len + ft_strlen(src));
}
