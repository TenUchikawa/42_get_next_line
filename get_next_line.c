/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:50:24 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/04/19 21:14:01 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = -1;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
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

char	*get_to_next_newline(int fd, char *static_char)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(static_char, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		static_char = ft_strjoin(static_char, buffer);
	}
	free(buffer);
	return (static_char);
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
char	*get_new_line(char *static_char)
{
	char	*newline_address;
	int		new_char_len;
	char	*new_char;

	newline_address = ft_strchr(static_char, '\n');
	if (!newline_address)
	{
		free(static_char);
		return (NULL);
	}
	new_char_len = ft_strlen(newline_address + 1);
	new_char = (char *)malloc(sizeof(char) * (new_char_len + 1));
	ft_memcpy(new_char, newline_address + 1, (new_char_len));
	free(static_char);
	new_char[new_char_len] = '\0';
	return (new_char);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_char;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_char = get_to_next_newline(fd, static_char);
	if (!static_char)
		return (NULL);
	line = get_line(static_char);
	static_char = get_new_line(static_char);
	if (!line || line[0] == '\0')
		return (NULL);
	return (line);
}

// int	main(void)
// {
// 	int fd = open("gnlTester/files/41_with_nl", O_RDONLY);
// 	char *line;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		line = get_next_line(fd);
// 	}

// 	free(line);
// 	close(fd);
// 	return (0);
// }