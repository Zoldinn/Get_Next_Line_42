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

////////////////////////////////////
void	ft_print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", list->string);
		list = list->next;
	}
}
////////////////////////////////////

/*
 * Once having line, line + begin of the next. Must cut all things next '\n'.
 * And save into another node, which will become the new head of the list.
 *
 * The last node, should contain end of line and begin of the next one.
 * So take the last, find the '\n', dup into another node,
 * free the anciant linked list and return the node.
*/
void	ft_cut_list(t_list **list)
{
	t_list	*new_head;
	t_list	*last_node;
	int		i;
	int		curs;
	
	new_head = malloc(sizeof(t_list));
	if (!new_head)
		return ;
	last_node = ft_last_node(*list);
	if (!last_node)
		return ;
	curs = 0;
	while (last_node->string[curs] != '\n')
		curs++;
	i = 0;
	new_head->string = malloc(sizeof(char) * (ft_size_line(*list) + 1));
	if (!new_head->string)
		return ;
	while (last_node->string[++curs])
		new_head->string[i++] = last_node->string[curs];
	new_head->string[i] = '\0';
	ft_free_list(*list);
	list = &new_head;
}

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
 *   into the futur head of the list for the next call of gnl (ft_cut_list).
 *   Don't need join -> ft_get_string, copy/join all strings of all nodes.
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
	list = ft_cut_list(&list);
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
	while (++i <= 4)
	{
		line = get_next_line(fd);
		printf("%s", line);
		sleep(1);
	}
	close(fd);
	free(line);
	return (0);
}

