/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:44:42 by oelbied           #+#    #+#             */
/*   Updated: 2024/12/26 13:08:33 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*test_nuwline(char *buffer, int fd)
{
	char		*line;
	ssize_t		size;
	char		*temp;

	line = (char *)malloc(((size_t)BUFFER_SIZE + 1) * (sizeof(char)));
	if (!line)
		return (NULL);
	size = 1;
	while (!ft_strchr(buffer, '\n') && size != 0)
	{
		size = read(fd, line, BUFFER_SIZE);
		if (size < 0)
			return (free (line), free (buffer), NULL);
		line[size] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, line);
		if (!buffer)
			return (free(temp), free(line), NULL);
		free(temp);
	}
	return (free(line), buffer);
}

char	*tst_finel_line(char *buffer, int i)
{
	char	*line;
	int		j;

	j = 0;
	if (buffer[i] == '\n')
	{
		line = (char *)malloc((i + 2) * sizeof(char));
		if (!line)
			return (NULL);
		while (buffer[j] != '\n')
		{
			line[j] = buffer[j];
			j++;
		}
		line[j] = '\n';
		line[j + 1] = '\0';
	}
	else
	{
		line = (char *)malloc((i + 1) * sizeof(char));
		if (!line)
			return (NULL);
		line = ft_strcpy(line, buffer);
	}
	return (line);
}

char	*test_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!buffer || *buffer == '\0')
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = tst_finel_line(buffer, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*remove_line(char *buffer)
{
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!buffer || *buffer == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	while (buffer[j])
		j++;
	if (buffer[i] == '\n')
		i++;
	temp = (char *)malloc((j - i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ft_strcpy(temp, &buffer[i]);
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX
		|| BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer[fd] = test_nuwline(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = test_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	buffer[fd] = remove_line(buffer[fd]);
	return (line);
}
