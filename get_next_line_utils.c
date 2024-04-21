/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:24:08 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/04/22 00:40:49 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	target;

	if (!s)
		return (0);
	target = (char)c;
	str = (char *)s;
	while (*str != target)
	{
		if (!(*str))
			return (NULL);
		str++;
	}
	return (str);
}

char	*ft_create_s1(char *s1)
{
	if (s1)
		return (s1);
	s1 = (char *)malloc(1 * sizeof(char));
	if (!s1)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = -1;
	if (!s1)
		s1 = ft_create_s1(s1);
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1[++j])
		ptr[i++] = s1[j];
	j = -1;
	while (s2[++j])
		ptr[i++] = s2[j];
	ptr[i] = 0;
	free(s1);
	return (ptr);
}

char	*get_line(char *static_char)
{
	char	*newline_address;
	int		strlen;
	char	*line;

	if (!static_char || static_char[0] == '\0')
		return (NULL);
	newline_address = ft_strchr(static_char, '\n');
	if (!newline_address)
	{
		line = (char *)malloc(sizeof(int) * (ft_strlen(static_char) + 1));
		ft_memcpy(line, static_char, ft_strlen(static_char));
		line[ft_strlen(static_char)] = '\0';
		return (line);
	}
	strlen = newline_address - static_char + 1;
	line = (char *)malloc(sizeof(int) * (strlen + 1));
	ft_memcpy(line, static_char, strlen);
	line[strlen] = '\0';
	return (line);
}
