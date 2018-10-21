/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toarray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:23:24 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:34:59 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_count(t_list *head)
{
	int		i;

	i = 0;
	while (head != NULL)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char		**ft_toarray(t_list *head)
{
	char	**array;
	int		i;

	i = 0;
	array = malloc((sizeof(char *)) * (1 + ft_count(head)));
	if (head == NULL)
		return (NULL);
	while (head != NULL)
	{
		array[i] = head->content;
		head = head->next;
		i++;
	}
	return (array);
}
