/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:55:17 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/05 18:02:48 by lefoffan         ###   ########.fr       */
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
	printf("(ft_free_list() call)\n");
}

int	ft_strchr(char *str, char needle)
{
	int	i;

	i = 0;
	if (!str)
		return (printf("Function ft_strchr() return an error !\n\t> There'isnt any string !\n"), -1);
	while (str[i] != needle)
	{
		if ((str[i] == '\0' && needle != '\0') || i >= BUFFER_SIZE)
			return (printf("Function ft_strchr() return there's no '\\n'.\n"), 0);
		i++;
	}
	return (printf("Function ft_strchr() return that there's a '\\n' at index : %d.\n", i), i);
}

t_list	*ft_get_last(t_list *list)
{
	if (!list)
		return (printf("Function ft_get_last() return NULL.\n\t> The list was NULL !\n"), NULL);
	while (list->next != NULL)
		list = list->next;
	return (printf("Function ft_get_last() return a node !\n\t-> \"%s\".\n", list->string), list);
}

// Return the size ('\n' NOT included) or -1 if error.
int	ft_size_line(t_list *list)
{
	int		i;

	i = 0;
	if (!list)
		return (printf("Function ft_size_line() return -1.\n\t> list was NULL !\n"), -1);
	while (list)
	{
		while (list->string[i] != '\n' && list->string[i])
			i++;
		list = list->next;
	}
	return (printf("Function ft_size_line() return a size : %d.\n", i), i);
}


char	*ft_get_line(t_list *list)
{
	int		i;
	int		j;
	int		size;
	char	*line;

	size = ft_size_line(list);
	if (size < 0)
		return (printf("Function ft_get_line() can't do a line, ft_size_line() return an error !\n"), NULL);
	line = malloc(sizeof(char) * (size + 2));
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
	return (printf("Function ft_get_line() return a line : \n\t> \"%s\"", line), line);
}

void	ft_print_list(t_list *list)
{
	int	i;

	i = 0;
	printf("\n--------------------\n");
	while (list)
	{
		printf("- node %d : %s\n", i++, list->string);
		list = list->next;
	}
	printf("\n--------------------\n");
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
