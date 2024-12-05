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
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct		s_list
{
	char			*string;
	struct s_list	*next;
}					t_list;

void	ft_cut_list(t_list *list);
void	ft_make_list(t_list **list, int fd);
char	*get_next_line(int fd);
t_list	*ft_last_node(t_list *list);
size_t	ft_size_line(t_list *list);
char	*ft_get_string(t_list *list);
int		ft_strchr(char *str);
void	ft_free_list(t_list *list);

#endif
