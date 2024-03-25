/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:06:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/22 13:17:54 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_free(char **s)
{
	if (*s)
		free(*s);
	*s = NULL;
	return (NULL);
}

char	*consume_and_resize(char **line_buf, size_t line_len)
{
	size_t	new_line_len;
	char	*new_buf;
	char	*line;

	line = malloc(line_len + 1);
	if (!line)
		return (0);
	ft_memcpy(line, *line_buf, line_len);
	line[line_len] = '\0';
	new_line_len = ft_strlen(*line_buf + line_len);
	new_buf = 0;
	if (new_line_len)
	{
		new_buf = malloc(new_line_len + 1);
		if (!new_buf)
			return (ft_free(&line));
		ft_memcpy(new_buf, *line_buf + line_len, new_line_len + 1);
	}
	free(*line_buf);
	*line_buf = new_buf;
	return (line);
}

size_t	find_newline(char *buf, size_t *len)
{
	*len = 0;
	if (!buf)
		return (0);
	while (buf[*len])
	{
		if (buf[(*len)++] == '\n')
			return (*len);
	}
	return (*len = 0);
}

char	read_and_fill(int fd, char **line_buf, size_t *line_len)
{
	char	read_buf[BUFFER_SIZE + 1];
	int		read_len;
	char	*temp;

	read_len = BUFFER_SIZE;
	while (!find_newline(*line_buf, line_len) && read_len > 0)
	{
		read_len = read(fd, read_buf, BUFFER_SIZE);
		if (read_len < 0)
			return (*line_len = 0);
		read_buf[read_len] = 0;
		if (!*line_buf)
			*line_buf = ft_strdup(read_buf);
		else
		{
			temp = *line_buf;
			*line_buf = ft_strjoin(*line_buf, read_buf);
			free(temp);
		}
		if (!*line_buf)
			return (*line_len = 0);
	}
	if (!*line_len)
		*line_len = ft_strlen(*line_buf);
	return (*line_len);
}

char	*get_next_line(int fd)
{
	static char		*line_buf[4096];
	size_t			line_len;
	char			*out;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 4096)
		return (0);
	read_and_fill(fd, &line_buf[fd], &line_len);
	if (!line_len)
		return (ft_free(&line_buf[fd]));
	out = consume_and_resize(&line_buf[fd], line_len);
	if (!out)
		ft_free(&line_buf[fd]);
	return (out);
}
