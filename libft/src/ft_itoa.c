/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:57:34 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:26:19 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	len(int n)
{
	int		i;

	i = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*pos(int n)
{
	int		i;
	char	*str;
	int		l;

	i = 0;
	l = len(n);
	str = ft_memalloc(l + 1);
	if (str == NULL)
		return (NULL);
	while (l > 0)
	{
		str[l - 1] = '0' + (n % 10);
		n = n / 10;
		l--;
	}
	return (str);
}

static char	*neg(int n)
{
	int		i;
	char	*str;
	int		l;

	i = 0;
	l = len(n);
	str = ft_memalloc(l + 2);
	if (str == NULL)
		return (NULL);
	n = -n;
	while (l > 0)
	{
		str[l] = '0' + (n % 10);
		n = n / 10;
		l--;
	}
	str[0] = '-';
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;

	if (n == -2147483648)
	{
		str = ft_memalloc(11);
		if (str == NULL)
			return (NULL);
		ft_strcpy(str, "-2147483648");
		return (str);
	}
	else if (n == 0)
	{
		str = ft_memalloc(2);
		if (str == NULL)
			return (NULL);
		ft_strcpy(str, "0");
		return (str);
	}
	else if (n < 0)
		return (neg(n));
	else
		return (pos(n));
}
