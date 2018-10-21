/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:05:35 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/09 18:51:07 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int				count_length(int value, int base, int *move)
{
	int					length;

	length = (base == 10 && value < 0) ? 1 : 0;
	*move = (base == 10 && value < 0) ? 1 : 0;
	while (value)
	{
		length++;
		value /= base;
	}
	return (length);
}

char					*ft_itoa_base(int value, int base)
{
	char				*ascii;
	int					length;
	int					digit;
	int					move;
	int					i;

	length = count_length(value, base, &move);
	if (!(ascii = (char *)malloc(sizeof(char) * length)))
		return (NULL);
	i = 0;
	if (move)
		ascii[i++] = '-';
	while (i < length)
	{
		digit = (value % base) < 0 ? -(value % base) : (value % base);
		ascii[length - i++ - ((move) ? (0) : (1))] = (digit > 9)
			? ('A' + digit)
			: ('0' + digit);
		value /= base;
	}
	ascii[i] = 0;
	return (ascii);
}
