/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:50:24 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/04/14 20:26:13 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

int	read_buffer(int fd, char *buffer, int buffer_size)
{
	int	bytes_read;

	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, buffer_size);
	return (bytes_read);
}

int	find_newline(char *buffer, size_t bytes_read)
{
	size_t	i;

	i = 0;
	while (i < bytes_read)
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	static int	static_buffer_size;
	char		*new_buffer;
	char		*buffer;
	char		*line;
	int			bytes_read;
	int			newline_index;
	int			line_length;
	int			new_size;

	if (BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (1)
	{
		bytes_read = read_buffer(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(static_buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		newline_index = find_newline(buffer, bytes_read);
		if (newline_index >= 0)
		{
			line_length = static_buffer_size + newline_index;
			// printf("mallocLen %ld\n", sizeof(char) * (line_length + 1));
			line = (char *)malloc(sizeof(char) * (line_length + 1));
			if (!line)
			{
				free(buffer);
				free(static_buffer);
				return (NULL);
			}
			if (static_buffer_size > 0)
				ft_memcpy(line, static_buffer, static_buffer_size);
			if (newline_index > 0)
				ft_memcpy(line + static_buffer_size, buffer, newline_index);
			line[line_length] = '\0';
			static_buffer_size = bytes_read - (newline_index + 1);
			new_buffer = (char *)malloc(sizeof(char) * (static_buffer_size
						+ 1));
			if (!new_buffer)
			{
				free(buffer);
				free(static_buffer);
				free(line);
				return (NULL);
			}
			ft_memcpy(new_buffer, buffer + newline_index + 1,
				static_buffer_size);
			new_buffer[static_buffer_size] = '\0';
			free(static_buffer);
			static_buffer = new_buffer;
			break ;
		}
		else
		{
			new_size = static_buffer_size + bytes_read;
			new_buffer = (char *)malloc(sizeof(char) * (new_size + 1));
			if (!new_buffer)
			{
				free(buffer);
				free(static_buffer);
				return (NULL);
			}
			if (static_buffer_size > 0)
				ft_memcpy(new_buffer, static_buffer, static_buffer_size);
			ft_memcpy(new_buffer + static_buffer_size, buffer, bytes_read);
			new_buffer[new_size] = '\0';
			free(static_buffer);
			static_buffer = new_buffer;
			static_buffer_size = new_size;
		}
	}
	free(buffer);
	if (static_buffer_size > 0)
	{
		if (!line)
		{
			line = (char *)malloc(sizeof(char) * (static_buffer_size + 1));
			if (!line)
			{
				free(static_buffer);
				return (NULL);
			}
			printf("\nline: %s\n", line);
			printf("\nstatic_buffer: %s\n", static_buffer);
			printf("\nstatic_buffer_size: %d\n", static_buffer_size);
			ft_memcpy(line, static_buffer, static_buffer_size);
			line[static_buffer_size] = '\0';
		}
		free(static_buffer);
	}
	return (line);
}

// int	main(void)
// {
// 	int fd = open("gnlTester/files/41_no_nl", O_RDONLY);
// 	char *line;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s\n", line);
// 		line = get_next_line(fd);
// 	}

// 	free(line);
// 	close(fd);
// 	return (0);
// }