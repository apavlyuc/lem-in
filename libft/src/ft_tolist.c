/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:01 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:35:09 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	del(void *content, size_t size)
{
	if (size == 0 || !content)
		return ;
	free(&(*content));
	content = NULL;
}

static void	*ft_free(t_list *head)
{
	ft_lstdel(&head, del);
	return (NULL);
}

t_list		*ft_tolist(char **array)
{
	int		i;
	t_list	*head;
	t_list	*cursor;
	t_list	*node;

	i = 0;
	head = NULL;
	cursor = NULL;
	while (array != NULL && array[i] != NULL)
	{
		if (!(node = ft_lstnew(array[i], (1 + ft_strlen(&array[i][0])))))
			return (ft_free(head));
		if (head == NULL)
		{
			head = node;
			cursor = head;
		}
		else
		{
			cursor->next = node;
			cursor = cursor->next;
		}
		i++;
	}
	return (head);
}
