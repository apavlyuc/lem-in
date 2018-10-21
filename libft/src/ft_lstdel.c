/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:11:21 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:26:42 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *cursor;

	if (!alst || !del)
		return ;
	cursor = *alst;
	while (cursor != NULL)
	{
		cursor = cursor->next;
		ft_lstdelone(alst, del);
		*alst = cursor;
	}
	*alst = NULL;
}
