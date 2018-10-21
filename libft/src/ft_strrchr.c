/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:52:33 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:34:13 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	ch;
	size_t	i;

	str = (char *)s;
	ch = (char)c;
	i = ft_strlen(str);
	if (c == '\0')
		return (&str[i]);
	while (i > 0 && s[i] != ch)
		i--;
	if (str[i] == ch)
		return (&str[i]);
	else
		return (NULL);
}
