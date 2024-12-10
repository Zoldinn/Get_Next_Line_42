/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:55:17 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/10 15:39:14 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_list(t_list **list)
{
	t_list	*tmp;

	if (!(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->string)
			free((*list)->string);
		free(*list);
		*list = tmp;
	}
	list = NULL;
}

/*
'-2' = erreur
-1 = pas trouver
i = trouver avec en bonus la pos
*/
int	ft_strchr(char *str, char needle)
{
	int	i;

	i = 0;
	if (!str)
		return (-2);
	while (str[i] != needle)
	{
		if ((str[i] == '\0' && needle != '\0') || i >= BUFFER_SIZE)
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

// Return the size ('\n' NOT included) or -1 if error.
int	ft_size_line(t_list *list)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!list)
		return (-1);
	while (list)
	{
		i = 0;
		while (list->string && list->string[i] && list->string[i] != '\n')
		{
			i++;
			size++;
		}
		if (list->string[i] == '\n' || list->string[i] == '\0')
			break ;
		list = list->next;
	}
	printf("size:%d\n", size);
	return (size);
}

char	*ft_get_line(t_list *list)
{
	int		i;
	int		j;
	int		size;
	char	*line;

	size = ft_size_line(list);
	if (size < 0)
		return (NULL);
	//line = ft_calloc(sizeof(char), (size + 2));
	printf("%d\n", size);
	line = malloc(sizeof(char) * (size + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (list)
	{
		i = 0;
		while (list->string[i] && list->string[i] != '\n' && i < BUFFER_SIZE)
		{
			line[j++] = list->string[i++];
			printf("test[%d]\n", i);
		}
		list = list->next;
	}
	// if (list->string[i] == '\n') //
	//printf("j:%d, string[i], %c\n", j, list->string[i]);
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

void	ft_print_list(t_list *list)
{
	int	i;

	i = 0;
	if (!list)
	{
		printf("Can't print, there's no list\n");
		return ;
	}
	printf("\n--- List actually ---\n");
	while (list)
	{
		printf("- node %d : <\"%s\">\n", i++, list->string);
		list = list->next;
	}
	printf("---------------\n");
}
