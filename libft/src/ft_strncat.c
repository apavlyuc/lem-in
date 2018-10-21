/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:28:16 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:33:08 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(s1);
	while (s1[i] != '\0')
		i++;
	ft_strncpy(&s1[i], s2, (1 + (ft_strlen(s2)) > n ? n : 1 + ft_strlen(s2)));
	ft_bzero(&s1[(1 + (ft_strlen(s2)) > n ? len + n : len + ft_strlen(s2))], 1);
	return (s1);
}
