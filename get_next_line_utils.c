/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:55:17 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/04 10:58:34 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_list(t_list *list)
{
	t_list	*tmp;

	if (!(list))
		return ;
	while (list)
	{
		tmp = (list)->next;
		if ((list)->string)
			free((list)->string);
		free(list);
		list = tmp;
	}
}

int	ft_strchr(char *str, char needle)
{
	int	i;

	i = 0;
	while (str[i] != needle)
	{
		if (str[i] == '\0' && needle != '\0')
			return (-1);
		i++;
	}
	return (i);
}

t_list	*ft_get_last(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

/*
 * Count the size of the line.
 * Copy until the '\n' or BUFFER_SIZE or '\0'
 * Return the size included the '\n' or -1 if error.
*/
char	*ft_get_line(t_list *list)
{
	int		i;
	int		j;
	int		size;
	char	*line;
	t_list	*tmp;

	tmp = list;
	size = 0;
	while (tmp)
	{
		size += ft_strchr(tmp->string, '\n');
		tmp = tmp->next;
	}
	line = malloc(sizeof(char) * (size + 1));
	j = 0;
	while (list)
	{
		i = 0;
		while (list->string[i] && list->string[i] != '\n' && i < BUFFER_SIZE)
			line[j++] = list->string[i++];
		list = list->next;
	}
	line[j] = '\n';
	line[++j] = '\0';
	return (line);
}



// ------------ TESTS ------------- //

/*int	main(void)
{
	t_list	test;
	t_list	test2;
	t_list	*last;

	test.string = "hello";
	test.next = &test2;
	test2.string = "world";
	test2.next = NULL;
	last = ft_get_last(&test);
	printf("%s\n", last->string);
}*/
