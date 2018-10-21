/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 19:24:58 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 19:57:36 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <libft.h>

static int	ft_print_text(char *dst, const char **string, int in)
{
	int		len;

	len = get_text_len(*string);
	if (len)
		ft_memcpy(dst + in, *string, len);
	*string += len;
	return (len);
}

static int	ft_print_param(char *buf, int in, const char **string,
							va_list *args)
{
	int		ret;
	char	*dst;
	t_param	param;

	if ((ret = update_param(string, args, &param)) < 0)
		return (ret);
	dst = 0;
	ret = create_param(&dst, args, &param);
	if (ret > 0 && dst)
	{
		ft_memcpy(buf + in, dst, ret);
		free(dst);
	}
	return (ret);
}

int			ft_sprintf(char *dst, const char *string, ...)
{
	int		ret;
	int		tmp_ret;
	va_list	args;

	ret = 0;
	va_start(args, string);
	while (*string)
	{
		ret += ft_print_text(dst, &string, ret);
		if (*string == '%')
		{
			string++;
			if ((tmp_ret = ft_print_param(dst, ret, &string, &args)) < 0)
			{
				ret = tmp_ret;
				break ;
			}
			ret += tmp_ret;
		}
	}
	va_end(args);
	return (ret);
}
