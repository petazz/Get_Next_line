/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:00:07 by pgonzal2          #+#    #+#             */
/*   Updated: 2023/11/07 19:03:16 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_file_read(char *estatic, int fd)
{
	char	*buffer;
	int		nread;
	char	*line = malloc(1);
	
	if (estatic != NULL)
		line = estatic;
	while (!ft_strchr(line, '\n'))
	{
		buffer = malloc(sizeof(char) * (ft_strlen(line) + BUFFER_SIZE + 1));
		if (buffer == NULL)
			return (NULL);
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread < 0)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[nread] = '\0';
		line = ft_strjoin(line, buffer);//si tienes leaks comprueba que line sea liberado antes del join
	}
	free(buffer);
	return (line);
}

char	*ft_get_line(char *estatic)
{
	char	*line;
	char	*aux;
	int		i;

	i = 0;
	if (estatic[0] == '\0')
		return (NULL);
	while (estatic[i] != '\0' && estatic[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + (estatic[i] == '\n') + 1));
	if (!line)
		return (NULL);
	aux = ft_strlcpy(line, estatic, 1);
	return (line);
}

char	*ft_new_line(char *estatic)
{
	int		i;
	int		j;
	int		size;
	char	*aux;

	j = 0;
	i = 0;
	while (estatic[i] != '\n')
		i++;
	if (estatic[i] == '\n')
		i++;
	size = ft_strlen(estatic) - i + 1;
	aux = malloc(sizeof(char) * size + 1);
	if (!aux)
	{
		free(aux);
		return (NULL);
	}
	while (estatic[i] != '\0')
	{
		aux[j] = estatic[i];
		i++;
		j++;
	}
	free (estatic);
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*estatic;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &estatic, 0) < 0)
		return (NULL);
	estatic = ft_file_read(estatic, fd);
	if (estatic == NULL)
		return (NULL);
	line = ft_get_line(estatic);
	printf("ey:	%s\n", estatic);
	estatic = ft_new_line(estatic);
	printf("eyeyeyeye:	%s\n", estatic);
	return (line);
}
int main(void)
{
	int fd = open("archivo.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("line: %s\n", line);
	line = get_next_line(fd);
	printf("line2: %s\n", line);
}
