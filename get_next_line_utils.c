/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:38:06 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/27 11:31:25 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
 * return the size of the line,
 * passing trough all the strings in the linked list,
 * '\n' included.
 */
size_t	ft_size_line(t_list *list)
{
	int	i;
	size_t	size;

	size = 0;
	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->string[i++] && i < BUFFER_SIZE)
		{
			if (list->string[i] == '\n')
				return (++size);
			size++;
		}
		list = list->next;
	}
	return (0);
}

/*
* return the string from beginning (beginning of file or '\n' from the end of the previous line),
* until '\n'.
*/
char	*ft_get_string(t_list *list)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_size_line(list) + 1));
	i = 0;
	if (!list)
		return (NULL);
	while (list)
	{
		j = 0;
		while (list->string[j] && j < BUFFER_SIZE)
			str[i++] = list->string[j++];
		list = list->next;
	}
	str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

int	ft_strchr(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

/*
 * Must free : the list->string and the list.
*/
void	ft_free_list(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->string);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}
