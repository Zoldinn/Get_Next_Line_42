/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:38:06 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/27 11:31:25 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_list	*ft_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	ft_size_line(t_list *list)
{
	int	i;
	int	size;

	size = 0;
	while (list)
	{
		i = 0;
		while (list->string[i++])
		{
			if (list->string[i] == '\n')
				return (++size);
			size++;
		}
		list = list->next;
	}
}

char	*ft_get_string(t_list *list)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (list)
	{
		j = 0;
		while (list->string[j])
			str[i++] = list->string[j++]
		list = list->next;
	}
}
