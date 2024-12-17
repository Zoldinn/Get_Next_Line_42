/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:57:38 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/17 12:11:48 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // a retirer
# include <fcntl.h> // a retirer

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*string;
	int				readed;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	ft_free_list(t_list **list);
t_list	*ft_lst_last(t_list *list);
int		ft_strchr(char *str, char x);
t_list	*ft_lst_last(t_list *list);
int		ft_size_line(t_list *list);
char	*ft_get_line(t_list *list);
t_list	*ft_cut_list(t_list **list);
char	*ft_sub_str(char *str, int start);
void	*ft_calloc(size_t count, size_t size);

#endif