/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:59:59 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:29:01 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_omit(char *s, char ch)
{
	int		i;
	int		c;
	int		j;
	char	*str;

	i = 0;
	c = 0;
	j = 0;
	if (!s || ch == '\0')
		return (NULL);
	while (s[i++] != '\0')
	{
		if (s[i - 1] == ch)
			c++;
	}
	if (!(str = ft_memalloc(ft_strlen(s) - c + 1)))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ch)
			str[j++] = s[i];
		i++;
	}
	return (str);
}
