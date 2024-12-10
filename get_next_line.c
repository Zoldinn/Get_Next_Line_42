/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:07:34 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/10 17:56:57 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_make_list(t_list **list, int fd)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (!(*list))
		*list = node;
	else
	{
		ft_lst_last
	}
}

char	ft_get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (ft_free_list(&list), NULL);
	if (!list || (list && ft_strchr(list->string, '\n') && list->readed > 0))
	{
		list = ft_make_list(&list, fd);
		if (!list)
			return (ft_free_list(&list), NULL);
	}

}