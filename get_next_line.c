/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:07:34 by lefoffan          #+#    #+#             */
/*   Updated: 2025/02/12 13:25:57 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	if (count * size == 0)
		return (malloc(0));
	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < (count * size))
		mem[i++] = '\0';
	return (mem);
}

t_gnl	*ft_cut_gnl(t_gnl **list)
{
	t_gnl	*new_head;
	char	*buf;

	new_head = malloc(sizeof(t_gnl));
	if (!new_head || !ft_lst_last(*list))
		return (NULL);
	buf = ft_lst_last(*list)->string;
	if (!buf)
		return (NULL);
	new_head->string = ft_sub_str(buf, ft_strchr(buf, '\n') + 1);
	if (!new_head->string || (new_head->string && !new_head->string[0]))
	{
		free(new_head->string);
		free(new_head);
		return (ft_free_list(list), NULL);
	}
	new_head->next = NULL;
	new_head->readed = ft_lst_last(*list)->readed;
	return (ft_free_list(list), new_head);
}

char	*ft_get_line(t_gnl *list)
{
	char	*line;
	int		i;
	int		j;

	if (list && list->string && list->string[0] == '\0')
		return (NULL);
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

t_gnl	*ft_make_list(t_gnl **list, int fd)
{
	t_gnl	*node;

	node = malloc(sizeof(t_gnl));
	if (!node)
		return (NULL);
	if (!(*list))
		*list = node;
	else
		ft_lst_last(*list)->next = node;
	node->string = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!node->string)
		return (NULL);
	node->readed = read(fd, node->string, BUFFER_SIZE);
	if (node->readed == -1)
		return (NULL);
	node->string[node->readed] = '\0';
	node->next = NULL;
	if (node->readed > 0 && (ft_strchr(node->string, '\n') < 0))
		ft_make_list(list, fd);
	return (*list);
}

char	*get_next_line(int fd)
{
	static t_gnl	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0
		|| (list && list->readed <= 0))
		return (ft_free_list(&list), NULL);
	if (!list || (list && ft_strchr(list->string, '\n') < 0
			&& list->readed > 0))
	{
		list = ft_make_list(&list, fd);
		if (!list)
			return (ft_free_list(&list), NULL);
	}
	line = ft_get_line(list);
	if (!line)
		return (ft_free_list(&list), NULL);
	list = ft_cut_gnl(&list);
	return (line);
}

/*   ---  TESTS  ---   */

/* int	main(void)
{
	char	*line;
	int		fd;

	fd = open("files/42_with_nl", O_RDONLY);
	if (fd < 0)
		printf("fd = %d\n", fd);
	
	printf("--------------------------------\n");
	line = get_next_line(fd);
	if (!line)
		return (printf("null\n"), 1);
	printf("%s", line);
	free(line);

	printf("--------------------------------\n");
	line = get_next_line(fd);
	if (!line)
		return (printf("null\n"), 1);
	printf("%s", line);
	free(line);
	close(fd);

	return (0);
} */

/* void	ft_print_gnl(t_gnl *list)
{
	if (!list)
	{
		printf("ft_print_gnl : error.\n");
		return ;
	}
	while (list)
	{
		printf("%s", list->string);
		list = list->next;
	}
	printf("\n--------------------\n");
} */
