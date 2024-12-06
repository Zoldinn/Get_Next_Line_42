/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:02:23 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/06 14:32:37 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
- pb de size line regler
--> pb a cut list : size line renvoie 0 car dans le node qu'il contient il a directe un '\n'.
*/

t_list	*ft_cut_list(t_list *list)
{
	t_list	*new_head;
	t_list	*last;
	int		i;
	int		j;

	new_head = malloc(sizeof(t_list));
	if (!new_head)
		return (ft_free_list(list), NULL);
	last = ft_get_last(list);
	if (!last)
		return (ft_free_list(list), NULL);
	new_head->string = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new_head)
		return (NULL);
	i = 0;
	j = 0;
	while (last->string[j] != '\n' && j < BUFFER_SIZE)
		j++;
	while (last->string[j] != '\0' && j < BUFFER_SIZE && i < BUFFER_SIZE)
		new_head->string[i++] = last->string[++j];
	new_head->string[i] = '\0';
	ft_free_list(list);
	printf("new_head-string = \"%s\"\n", new_head->string);
	return (new_head);
}

t_list	*ft_make_list(t_list **list, int fd)
{
	t_list	*node;
	t_list	*last;
	int		readed;
	char	*buf;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	last = ft_get_last(*list);
	if (!last)
		*list = node;
	else
		last->next = node;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	readed = read(fd, buf, BUFFER_SIZE);
	buf[BUFFER_SIZE] = '\0';
	node->string = buf;
	node->next = NULL;
	if (ft_strchr(node->string, '\n') == 0) // pb ici
		ft_make_list(list, fd);
	else if (ft_strchr(node->string, '\n') == -1)
		return (printf("Error making list\n"), NULL);
	return (*list);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (!list || ft_strchr(list->string, '\n') == 0)
	{
		list = ft_make_list(&list, fd);
		if (!list)
		{
			ft_free_list(list);
			return (NULL);
		}
	}
	line = ft_get_line(list);
	list = ft_cut_list(list);
	return (line);
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
		printf("\n------ GNL, call %d ------\n", i);
		line = get_next_line(fd);
		if (!line)
			return (printf("Gnl did not return a line\n"), 1);
		printf("\n-->line %d : <\"%s\">\n\n", i, line);
		sleep(1);
	}
	close(fd);
	free(line);
	return (0);
}
