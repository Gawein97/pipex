/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:38:18 by inightin          #+#    #+#             */
/*   Updated: 2022/02/06 18:34:19 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (*(s + i))
	{
		if ((char)*(s + i) == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)*(s + i) == (char)c)
		return ((char *)(s + i));
	return (0);
}

char	*ft_strdup(const char *src)
{
	char	*ptr;
	int		i;

	ptr = NULL;
	i = 0;
	ptr = malloc(sizeof(*src) * ft_strlen(src) + 1);
	if (ptr != NULL)
	{
		while (*(src + i) != '\0')
		{
			*(ptr + i) = *(src + i);
			i++;
		}
		*(ptr + i) = '\0';
	}
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	while (s[start] && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = 0;
	return (sub);
}
