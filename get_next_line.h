/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:03:49 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/09 12:15:23 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 45
# endif

typedef struct s_list
{
	char			*string;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
int		ft_strchr(char *str, char needle);
char	*ft_get_line(t_list *list);
void	ft_free_list(t_list **list);
t_list	*ft_make_list(t_list **list, int fd);
t_list	*ft_cut_list(t_list *list);
t_list	*ft_get_last(t_list *list);
void	*ft_calloc(size_t count, size_t size);
int		ft_size_line(t_list *list);

#endif
