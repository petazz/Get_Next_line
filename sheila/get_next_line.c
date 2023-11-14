/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:38:03 by sheferna          #+#    #+#             */
/*   Updated: 2023/11/14 20:55:56 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	// seguira leyendo hasta q encuentre en la lectura de 10 bytes un salto de linea
	// en el ejemplo q tenemos, hara los lecturas consecutivas, 
	// encuentra un salto de linea en la segunda, entonces para de leer
	while (nbytes > 0 && !ft_strchr(buffer, '\n'))
	{
		nbytes = read (fd, buffer, BUFFER_SIZE);
		if (nbytes > 0)
		{
			buffer[nbytes] = '\0';
			estatic = ft_strjoin_gnl(estatic, buffer);
		}
	}
	// liberamos el buffer xq ya no lo necesitamos
	free(buffer);
	// en caso de q read falle, liberamos la estatica
	if (nbytes == -1)
		return (ft_free(&estatic));
	return (estatic);
}

char	*ft_get_line(char *estatic)
{
	char	*line;
	char	*ptr;
	int		len;

	// ptr es un puntero a \n de la cadena de texto q contiene estatic
	ptr = ft_strchr(estatic, '\n');
	// len es la longitud desde el inicio de estatic hasta una posicion despues del salto de linea
	//len = (ft_strlen(ptr) - ft_strlen(estatic)) + 1;
	len = (ptr - estatic) + 1;
	// line contendrá el contenido de estatic desde cero hasta len bytes
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
	// ptr es un puntero a \n de la cadena de texto q contiene estatic
	ptr = ft_strchr(estatic, '\n');
	if (!ptr)
	{
		new_estatic = NULL;
		return (ft_free(&estatic));
	}
	else // estatic es un puntero al inicio de la cadena que contiene
		// len es la longitud desde el inicio de estatic hasta una posicion despues del salto de linea 
		//len = ft_strlen(ptr) - ft_strlen(estatic) + 1;
		len = (ptr - estatic) + 1; //es lo mismo, es la distancia entre los punteros dentro de la misma cadena
	if (!estatic[len])
		return (ft_free(&estatic));
	// len seria el start, y la longitud a obtener es la diferencia entre la longitud de estatic menos len
	// new_estatic contendrá desde la posicion de len q es un byte mas del salto de linea hasta el final
	new_estatic = ft_substr(estatic, len, ft_strlen(estatic) - len);
	// ya rescatamos en la nueva estatica el contenido sobrante tras el salto de linea
	// por tanto, liberamos la estatica antigua q no necesitamos
	ft_free(&estatic);
	if (!new_estatic)
		return (NULL);
	return (new_estatic);
}

char	*get_next_line(int fd)
{
	static char	*estatic[1026];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&estatic));
	// si hay estatica y no hay salto de linea o la estatica es nula q es lo q pasa al inicio
	if ((estatic && !ft_strchr(estatic, '\n')) || !estatic)
		estatic = ft_read (fd, estatic);
	// si no se ha guardado nada en estatica tras el read
	if (!estatic)
		return (NULL);
	// obtenemos el contenido de la linea
	line = ft_get_line(estatic);
	if (!line)
		return (ft_free(&estatic));
	// actualizamos el contenido de la estatica con el contenido sobrante
	// para que cuando llamemos la sig vez a la funcion, el contenido nuevo 
	// q lea se concatene con el join a este contenido sobrante de la lectura anterior
	estatic = ft_new_estatic(estatic);
	return (line);
}
/*  int main(void) 
{
	int fd = open("archivo.txt", O_RDONLY);
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