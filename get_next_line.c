/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:02:23 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/04 11:00:32 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cut_list(t_list *list)
{
	t_list	*new_head;
	t_list	*last;
	int		i;
	int		j;

	new_head = malloc(sizeof(t_list));
	if (!new_head)
		return ;
	last = ft_get_last(list);
	i = 0;
	j = 0;
	while (last->string[j] != '\n')
		j++;
	while (last->string[j] != '\0')
		new_head->string[i++] = last->string[j++];
	new_head->string[i] = '\0';
	ft_free_list(list);
	list = new_head;
}

int	ft_make_list(t_list *list, int fd)
{
	t_list	*node;
	t_list	*last;
	int		readed;
	char	*buf;

	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	if (!list)
		list = node;
	else
	{
		last = ft_get_last(list);
		last->next = node;
	}
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	readed = read(fd, buf, BUFFER_SIZE);
	buf[BUFFER_SIZE + 1] = '\0';
	node->string = buf;
	node->next = NULL;
	if (!ft_strchr(node->string, '\n'))
		readed += ft_make_list(list, fd);
	return (readed);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;
	int				check_making_list;

	if (!list || !ft_strchr(list->string, '\n'))
	{
		check_making_list = ft_make_list(list, fd);
		if (check_making_list == -1)
		{
			ft_free_list(list);
			return (NULL);
		}
	}
	line = ft_get_line(list);
	ft_cut_list(list);
	return (line);
}

/* ---------- TESTS ---------- */

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("./testfile", O_RDONLY);
	if (fd < 1)
		return (1);
	i = 0;
	while (++i <= 1)
	{
		line = get_next_line(fd);
		if (!line)
			return (printf("There's no line !\n"));
		printf("line %d : %s\n", i, line);
	}
	close(fd);
	free(line);
	return (0);
}
