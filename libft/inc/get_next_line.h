/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:13:06 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 18:59:26 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFF_SIZE  1024

typedef struct		s_data
{
	int				fd;
	char			buff[BUFF_SIZE + 1];
	char			*p;
	struct s_data	*next;
}					t_dat;

int					get_next_line(const int fd, char **line);

#endif
