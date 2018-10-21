/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:05:46 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:34:22 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	words(char *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			words++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (words);
}

static void	*ft_free(char **array)
{
	free(array);
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	char	*wd;
	int		i;
	int		b;
	int		j;

	if (!s)
		return (NULL);
	array = ft_memalloc(sizeof(char **) * (words((char *)s, c) + 1));
	i = 0;
	j = 0;
	while ((words((char *)s, c) - j > 0) && array != NULL)
	{
		while (s[i] == c)
			i++;
		b = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (!(wd = ft_strsub(s, b, (i - b))))
			return (ft_free(array));
		array[j++] = wd;
	}
	return (array);
}
