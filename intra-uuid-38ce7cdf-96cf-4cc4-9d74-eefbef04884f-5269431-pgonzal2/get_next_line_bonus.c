/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:00:56 by pgonzal2          #+#    #+#             */
/*   Updated: 2023/11/15 16:34:53 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_read(int fd, char *estatic)
{
	int		nbytes;
	char	*buffer;

	nbytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&estatic));
	buffer[0] = '\0';
	while (nbytes > 0 && !ft_strchr(buffer, '\n'))
	{
		nbytes = read (fd, buffer, BUFFER_SIZE);
		if (nbytes > 0)
		{
			buffer[nbytes] = '\0';
			estatic = ft_strjoin(estatic, buffer);
		}
	}
	free(buffer);
	if (nbytes == -1)
		return (ft_free(&estatic));
	return (estatic);
}

char	*ft_get_line(char *estatic)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(estatic, '\n');
	len = (ptr - estatic) + 1;
	line = ft_substr(estatic, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_new_estatic(char *estatic)
{
	char	*new_estatic;
	char	*ptr;
	int		len;

	ptr = ft_strchr(estatic, '\n');
	if (!ptr)
	{
		new_estatic = NULL;
		return (ft_free(&estatic));
	}
	else
		len = (ptr - estatic) + 1;
	if (!estatic[len])
		return (ft_free(&estatic));
	new_estatic = ft_substr(estatic, len, ft_strlen(estatic) - len);
	ft_free(&estatic);
	if (!new_estatic)
		return (NULL);
	return (new_estatic);
}

char	*get_next_line(int fd)
{
	static char	*estatic[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_free(&estatic[fd]));
	estatic[fd] = ft_read (fd, estatic[fd]);
	if (!estatic[fd])
		return (NULL);
	line = ft_get_line(estatic[fd]);
	if (!line)
		return (ft_free(&estatic[fd]));
	estatic[fd] = ft_new_estatic(estatic[fd]);
	return (line);
}
/* int main(void) 
{
	int fd = open("archivo.txt", O_RDONLY, "archivo2.txt", O_RDONLY);
	char *line;
//	atexit(leaks);
	line = get_next_line(fd);
	printf("line: %s\n", line);
	free (line);
	line = get_next_line(fd);
	printf("line2: %s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("line3: %s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("line4: %s\n", line);
	free(line); 
}   */