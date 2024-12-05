/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:02:23 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/05 18:26:39 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_cut_list(t_list *list)
{
	t_list	*new_head;
	t_list	*last;
	int		i;
	int		j;

	new_head = malloc(sizeof(t_list));
	if (!new_head)
		return (printf("Malloc the new head, failed\n"), ft_free_list(list), NULL);
	last = ft_get_last(list);
	if (!last)
		return (printf("Getting the last node, failed\n"), ft_free_list(list), NULL);
	new_head->string = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new_head)
		return (NULL);
	i = 0;
	j = 0;
	while (last->string[j] != '\n' && j < BUFFER_SIZE)
		j++;
	while (last->string[j] != '\0' && j < BUFFER_SIZE && i < BUFFER_SIZE)
		new_head->string[i++] = last->string[j++];
	new_head->string[i] = '\0';
	ft_free_list(list);
	return (printf("The linked list has been cut !\n"), new_head);
}

t_list	*ft_make_list(t_list *list, int fd)
{
	t_list	*node;
	t_list	*last;
	int		readed;
	char	*buf;

	node = malloc(sizeof(t_list));
	if (!node)
		return (printf("Malloc the node, failed\n"), NULL);
	if (!list)
		list = node;
	else
	{
		last = ft_get_last(list);
		last->next = node;
	}
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (printf("Malloc the buf, failed\n"), NULL);
	readed = read(fd, buf, BUFFER_SIZE);
	buf[BUFFER_SIZE] = '\0';
	node->string = buf;
	node->next = NULL;
	if (!ft_strchr(node->string, '\n'))
	{
		printf("Adding a node... (recursion)\n");
		ft_make_list(list, fd);
	}
	if (!list)
		return (printf("Function ft_make_list() failed to make the list\n"), NULL);
	else
		ft_print_list(list);
	return (printf("Making list succesfully !\n"), list);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (!list || 0 > ft_strchr(list->string, '\n'))
	{
		list = ft_make_list(list, fd);
		if (!list)
		{
			ft_free_list(list);
			return (printf("Making list, failed\n"), NULL);
		}
	}
	ft_print_list(list);
	line = ft_get_line(list);
	if (!line)
		return (printf("Get line, failed\n"), NULL);
	list = ft_cut_list(list);
	if (!list)
		return (printf("Cuting list, failed\n"), NULL);
	return (printf("Line returned !\n"), line);
}

/* ---------- TESTS ---------- */

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("./testfile.txt", O_RDONLY);
	if (fd < 1)
		return (printf("Open the file, failed\n"), 1);
	i = 0;
	while (++i <= 10)
	{
		line = get_next_line(fd);
		if (!line)
			return (printf("Gnl did not return a line\n"), 1);
		printf("line %d : %s\n", i, line);
	}
	close(fd);
	free(line);
	return (printf("SUCCESS !!!\n"), 0);
}
