/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:50:24 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/04/19 21:32:16 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

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

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_char[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_char[fd] = get_to_next_newline(fd, static_char[fd]);
	if (!static_char[fd])
		return (NULL);
	line = get_line(static_char[fd]);
	static_char[fd] = get_new_line(static_char[fd]);
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