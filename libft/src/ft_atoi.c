/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:54:04 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/09/23 16:25:16 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int			toolong(unsigned char *str, int sign)
{
	int				i;
	int				flag;

	i = 0;
	flag = 0;
	while (ft_isdigit(str[i]))
	{
		flag++;
		i++;
	}
	if (flag > 19 && sign == 1)
		return (-1);
	else if (flag > 19 && sign == -1)
		return (0);
	else
		return (10);
}

int					ft_atoi(const char *str)
{
	long long int	result;
	unsigned char	*s;
	long long int	i;
	long long int	dude;
	int				flag;

	s = (unsigned char *)str;
	i = 0;
	result = 0;
	flag = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ' || s[i] == '	')
		i++;
	dude = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] == '0')
		i++;
	if (toolong(&s[i], dude) != 10)
		return (toolong(&s[i], dude));
	while (ft_isdigit(s[i]) == 1)
	{
		result = result * 10 + s[i] - '0';
		i++;
	}
	return (result * dude);
}
