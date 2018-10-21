/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:55:21 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:34:49 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	end(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && (s[i] == '\t' || s[i] == '\n' || s[i] == ' '))
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}

static int	size(const char *s)
{
	int		i;
	int		j;

	i = 0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == ' ')
		i++;
	if (s[i] == '\0')
		j = -1;
	else
	{
		j = ft_strlen(&s[i]) - 1;
		while (s[i + j] == '\t' || s[i + j] == '\n' || s[i + j] == ' ')
			j--;
	}
	return (j + 1);
}

char		*ft_strtrim(char const *s)
{
	int		c;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	c = size(s);
	str = ft_memalloc(c + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && (s[i] == '\t' || s[i] == '\n' || s[i] == ' '))
		i++;
	while (end(&s[i]) == 0)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	return (str);
}
