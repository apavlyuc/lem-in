/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:44:34 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/08 19:34:28 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strdup(const char *s1)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (1 + ft_strlen(s1)));
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s1, (1 + ft_strlen(s1)));
	return (dup);
}
