/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:42:52 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:34:41 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	if (!s)
		return (NULL);
	sub = ft_memalloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	if (sub == NULL)
		return (NULL);
	while (len > 0)
	{
		sub[i] = s[start];
		len--;
		start++;
		i++;
	}
	return (sub);
}
