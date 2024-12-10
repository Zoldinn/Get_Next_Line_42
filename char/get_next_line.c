/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:47 by lefoffan          #+#    #+#             */
/*   Updated: 2024/12/10 17:47:16 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		lens1;
	int		lens2;
	int		i;

	if (!s2)
		return (NULL);
	if (s1)
	{
		while (s1[lens1])
			lens1++;
	}
	else
		lens1 = 0;
	while (s2[lens2])
		lens2++;
	str = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < lens1)
		str[i++] = s1[lens1];
	while (i < lens1 + lens2)
		str[i++] = s2[lens2];
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *str, int start, int size)
{
	char	*sub;
	int		i;

	if (!str || size <= 0 || start >= size)
		return (NULL);
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (str[start] && i < size)
		sub[i++] = str[start++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!buf)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!read(fd, buf, BUFFER_SIZE) && !ft_strchr(buf))
			return (free(buf), NULL);
	}
}