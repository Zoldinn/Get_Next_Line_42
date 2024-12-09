/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:02:23 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/09 12:15:23 by lefoffan         ###   ########.fr       */
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

t_list	*ft_cut_list(t_list *list)
{
	t_list	*new_head;
	t_list	*last;
	int		i;
	int		j;

	new_head = ft_calloc(sizeof(t_list), 1);
	if (!new_head)
		return (NULL);
	last = ft_get_last(list);
	if (!last)
		return (free(new_head), NULL);
	new_head->string = ft_calloc(sizeof(char), (ft_size_line(last) + 1));
	if (!new_head->string)
		return (free(new_head), NULL);
	i = 0;
	j = 0;
	while (last->string[j] != '\n' && j < BUFFER_SIZE)
		j++;
	if (last->string[j] == '\n')
		j++;
	while (last->string[j] != '\0' && j < BUFFER_SIZE)
		new_head->string[i++] = last->string[j++];
	new_head->string[i] = '\0';
	return (ft_free_list(&list), new_head);
}

/*
- leaks are surely here
*/
t_list	*ft_make_list(t_list **list, int fd, int *readed)
{
	t_list	*node;
	t_list	*last;
	char	*buf;

	node = ft_calloc(sizeof(t_list), 1);
	if (!node)
		return (NULL);
	if (!(*list))
		*list = node;
	else
	{
		last = ft_get_last(*list);
		last->next = node;
	}
	buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buf)
		return (free(node), NULL);
	*readed = read(fd, buf, BUFFER_SIZE);
	node->string = buf;
	node->next = NULL;
	if (ft_strchr(node->string, '\n') == -1 && *readed > 0)
		ft_make_list(list, fd);
	return (*list);
}

/*
- Must free the static when the file have been entirely readed
*/
char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;
	int				readed;

	readed = 0;
	if (fd <= 0)
		return (ft_free_list(&list), NULL);
	if (!list || ft_strchr(list->string, '\n') < 0)
	{
		list = ft_make_list(&list, fd, &readed);
		if (!list)
			return (ft_free_list(&list), NULL);
	}
	line = ft_get_line(list);
	if (!line)
		return (ft_free_list(&list), NULL);
	list = ft_cut_list(list);
	if (!list)
		return (free(line), ft_free_list(&list), NULL);
	if 
	return (line);
}

/* ---------- TESTS ---------- */

int	main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		i;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 1)
			return (printf("Open the file, failed\n"), 1);
		i = 0;
		while (++i <= 10)
		{
			line = get_next_line(fd);
			if (!line)
				return (printf("Gnl did not return a line\n"), 1);
			printf("Gnl return : %s", line);
			//sleep(1);
		}
		close(fd);
		free(line);
		return (0);
	}
	return (printf("Error : no file\n"), 1);
}

/*
- pb : calloc make a node full of '\0'
--> even if there's no line, it fill it with '\0' so gnl return a line of buffer size full of '\0'
*/