/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 01:30:05 by inightin          #+#    #+#             */
/*   Updated: 2022/02/04 21:12:14 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static size_t	ft_w_count(char const *s, char c)
{
	size_t	count;
	int		flag;
	size_t	i;

	i = 0;
	flag = 1;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag)
		{
			count++;
			flag = 0;
		}
		else if (s[i] == c)
			flag = 1;
		i++;
	}
	return (count);
}

char	*ft_create_word(char const *s, char c)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (0);
	while (s[j] != c && s[j] != '\0')
	{
		ptr[j] = s[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		flag;
	int		i;
	char	**words;
	int		w_count;

	i = 0;
	flag = 1;
	w_count = ft_w_count(s, c);
	words = malloc(sizeof(char *) * (w_count + 1));
	while (*s != '\0')
	{
		if (*s != c && flag)
		{
			words[i] = ft_create_word(s, c);
			i++;
			flag = 0;
		}
		else if (*s == c)
			flag = 1;
		s++;
	}
	words[i] = 0;
	return (words);
}
