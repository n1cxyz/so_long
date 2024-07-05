/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dominicasal <dominicasal@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:58:47 by dominicasal       #+#    #+#             */
/*   Updated: 2024/05/11 17:00:55 by dominicasal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_stash(char *stash, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strxjoin(stash, buffer);
	}
	free (buffer);
	return (stash);
}

char	*str_snip(char *str)
{
	size_t	i;
	char	*result;
	size_t	len;

	len = 0;
	if (!str[len])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	result = (char *)malloc(sizeof(char) * len + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		result[i] = str[i];
		i++; 
	}
	if (str[i] == '\n')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*result;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	stash = ft_get_stash(stash, fd);
	if (!stash)
		return (NULL);
	result = str_snip(stash);
	stash = ft_substring(stash);
	return (result);
}

/* int	main(void)
{
	ssize_t		fd;
	char	*result;

	fd = open("text1.txt", O_RDONLY);
	

	while ((result = get_next_line(fd)) != NULL)
	{
		printf("%s", result);
		free (result);
	}

	close(fd);
	
	return (0);
} */