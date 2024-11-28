/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:37:50 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/28 16:03:03 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# define BUFFER_SIZE 100

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
t_list	*ft_node_line(int fd, t_list **lst);

#endif