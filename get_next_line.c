/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:07:34 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/12 15:47:31 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < (count * size))
		mem[i++] = '\0';
	return (mem);
}

t_list	*ft_cut_list(t_list **list)
{
	t_list	*new_head;
	char	*buf;

	new_head = malloc(sizeof(t_list));
	if (!new_head)
		return (NULL);
	buf = ft_lst_last(*list)->string;
	new_head->string = ft_sub_str(buf, ft_strchr(buf) + 1);
	if (!new_head->string)
		return (NULL);
	new_head->next = NULL;
	new_head->readed = ft_lst_last(*list)->readed;
	return (ft_free_list(list), new_head);
}

char	*ft_get_line(t_list *list)
{
	char	*line;
	int		i;
	int		j;

	line = ft_calloc(sizeof(char), (ft_size_line(list) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (list)
	{
		j = 0;
		while (list->string[j] != '\n' && list->string[j])
			line[i++] = list->string[j++];
		if (list->string[j] == '\n')
			break ;
		list = list->next;
	}
	if (list && list->string[j] == '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return (line);
}

t_list	*ft_make_list(t_list **list, int fd)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (!(*list))
		*list = node;
	else
		ft_lst_last(*list)->next = node;
	node->string = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!node->string)
		return (free(node), NULL);
	node->readed = read(fd, node->string, BUFFER_SIZE);
	node->string[BUFFER_SIZE] = '\0';
	node->next = NULL;
	if (node->readed > 0 && ft_strchr(node->string) < 0)
		ft_make_list(list, fd);
	return (*list);
}

/* Tout les ft_free_list doivent etre fait ici.
*/
char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) <= 0 ||
		(list && list->readed <= 0 && ft_strchr(list->string) < 0))
		return (ft_free_list(&list), NULL);
	if (!list || (list && ft_strchr(list->string) < 0 && list->readed > 0))
	{
		list = ft_make_list(&list, fd);
		if (!list)
			return (ft_free_list(&list), NULL);
	}
	line = ft_get_line(list);
	list = ft_cut_list(&list);
	return (line);
}

/*   ---  TESTS  ---   */

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("empty", O_RDONLY);
	i = 0;
	while (++i <= 15)
	{
		line = get_next_line(fd);
		if (!line)
			return (printf("gnl : nothing returned.\n"), 1);
		printf("%d| %s\n", i, line);
		free(line);
	}
	close(fd);
	return (0);
}

/* void	ft_print_list(t_list *list)
{
	if (!list)
	{
		printf("ft_print_list : error.\n");
		return ;
	}
	while (list)
	{
		printf("%s", list->string);
		list = list->next;
	}
	printf("\n--------------------\n");
} */