/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dominicasal <dominicasal@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:18:06 by dasal             #+#    #+#             */
/*   Updated: 2024/05/11 17:14:19 by dominicasal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char const *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)str + i);
	return (NULL);
}

char	*ft_strxjoin(char *s1, char *s2)
{
	size_t	buffer_len;
	size_t	content_len;
	char	*result;
	char	*result_ptr;
	char	*src;

	buffer_len = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		buffer_len = ft_strlen(s1);
	content_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (buffer_len + content_len + 1));
	if (!result)
		return (NULL);
	result_ptr = result;
	src = s1;
	while (src && *src)
		*result_ptr++ = *src++;
	src = (char *)s2;
	while (src && *src)
		*result_ptr++ = *src++;
	*result_ptr = '\0';
	free(s1);
	return (result);
}

/* ssize_t	ft_strlen(char const *str)
{
	ssize_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
} */

char	*ft_substring(char *str)
{
	ssize_t	i;
	char	*result;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free (str);
		return (NULL);
	}
	result = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!result)
		return (NULL);
	i++;
	ft_strlcpy(result, str + i, ft_strlen(str) - i + 1);
	free (str);
	return (result);
}

/* size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (src[i] != '\0')
		i++;
	if (size == 0)
		return (i);
	while (src[j] != '\0' && j < size - 1)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (i);
} */
