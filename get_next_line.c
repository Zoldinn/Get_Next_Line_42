/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:36:45 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/02 13:20:23 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * create the list. If there's nothing, the new node become the head.
 * Otherwise, the new node is put at the end of the linked list.
 * Read and put the buf that contain the string readed into the new node.
 * If there's a '\n', stop. Otherwise, repeat until a '\n' founded.
 * -> If repeat, should put the another strings into another node at next.
*/
void	ft_make_list(t_list **list, int fd)
{
	ssize_t	readed;
	t_list	*new_node;
	t_list	*last_node;
	char	*buf;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!*list)
		*list = new_node;
	else
	{
		last_node = ft_last_node(*list);
		last_node->next = new_node;
	}
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	readed = read(fd, buf, BUFFER_SIZE);
	if (readed < 1)
		return ;
	buf[BUFFER_SIZE + 1] = '\0';
	new_node->string = buf;
	new_node->next = NULL;
	if (!ft_strchr(new_node->string))
		ft_make_list(list, fd);
}

/*
 * actually : must return a string that contain the line and the begin of the next
 * to do :
 *   - do the copy of the bit of next line contain in last node, to put it 
 *   into the futur head of the list for the next call of gnl
*/
char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (!list || !ft_strchr(list->string))
		ft_make_list(&list, fd);
	line = ft_get_string(list);
	if (!line)
		return (NULL);
	ft_free_list(&list);
	return (line);
}

////////////////////

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("./testfile", O_RDONLY);
	i = 0;
	while (++i <= 1)
	{
		line = get_next_line(fd);
		sleep(1);
		printf("%s", line);
	}
	close(fd);
	free(line);
	return (0);
}

