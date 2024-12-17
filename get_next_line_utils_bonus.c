/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:59:57 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/17 12:11:49 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free_list(t_list **list)
{
	t_list	*tmp;

	if (!(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->string)
		{
			free((*list)->string);
			(*list)->string = NULL;
		}
		free(*list);
		*list = tmp;
	}
	list = NULL;
}

t_list	*ft_lst_last(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

int	ft_strchr(char *str, char x)
{
	int	i;

	if (!str)
		return (-2);
	i = 0;
	while (str[i] && i < BUFFER_SIZE)
	{
		if (str[i] == x)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_size_line(t_list *list)
{
	int	size;

	size = 0;
	while (list && list->string && ft_strchr(list->string, '\n') < 0)
	{
		size += BUFFER_SIZE;
		list = list->next;
	}
	if (list && list->string && list->string[0] != '\0')
		size += ft_strchr(list->string, '\n');
	return (++size);
}

char	*ft_sub_str(char *str, int start)
{
	char	*sub;
	int		i;
	int		size;

	if (!str || start < 0)
		return (NULL);
	size = BUFFER_SIZE - start;
	if (size < 0)
		return (NULL);
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (str[start])
		sub[i++] = str[start++];
	sub[i] = '\0';
	return (sub);
}
