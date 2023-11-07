/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:58:37 by pgonzal2          #+#    #+#             */
/*   Updated: 2023/11/07 19:22:45 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	while (str[i] != (char)c)
	{
		if (!str[i])
			return (0);
		i++;
	}
	return (&str[i]);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		size;
	char	*s3;
	int		j;

	j = 0;
	i = ft_strlen(s1);
	size = i + ft_strlen(s2);
	s3 = malloc(sizeof(char) * size + 1);
	if (s3 == NULL)
		return (NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2 != NULL && s2[j] != '\0')
	{
		s3[i++] = s2[j++];
	}
	s3[size] = '\0';
	return (s3);
}

char	*ft_strlcpy(char *dest, const char *src, int dstsize)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		if (dstsize && src[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
