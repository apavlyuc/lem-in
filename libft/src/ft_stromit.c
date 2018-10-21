/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stromit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:44:43 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:34:05 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_n(char *s, char *omit)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (ft_strnstr(&s[i], omit, ft_strlen(omit)) != NULL)
		{
			n++;
			i += ft_strlen(omit);
		}
		else
			i++;
	}
	return (n);
}

char		*ft_stromit(char *s, char *omit)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s || !omit)
		return (NULL);
	str = ft_memalloc(ft_strlen(s) - (ft_strlen(omit) * ft_n(s, omit)) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (ft_strnstr(&s[i], omit, ft_strlen(omit)) != NULL)
		{
			i += ft_strlen(omit);
		}
		else
		{
			str[j] = s[i];
			j++;
			i++;
		}
	}
	return (str);
}
