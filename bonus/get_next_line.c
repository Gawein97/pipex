/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:45:06 by inightin          #+#    #+#             */
/*   Updated: 2022/02/06 19:08:08 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*ft_save_buffer(int fd, char *save, char *buf)
{
	int		ret;
	char	*tmp;

	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		if (!save)
			save = ft_strdup("");
		tmp = save;
		save = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(save, '\n') || BUFFER_SIZE > ft_strlen(buf))
			break ;
	}
	free(buf);
	return (save);
}

char	*ft_st_save(char *save)
{
	char	*tmp;
	int		i;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	tmp = ft_substr(save, i + 1, ft_strlen(save) - (i + 1));
	if (!tmp)
	{
		free(save);
		return (NULL);
	}
	free(save);
	return (tmp);
}

char	*ft_extract(char *save)
{
	char	*line;
	int		i;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	line = ft_substr(save, 0, i + 1);
	if (!line)
		return (NULL);
	if (line[0] == '\0')
	{
		free(line);
		return (0);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	save = ft_save_buffer(fd, save, buf);
	if (!save)
		return (NULL);
	line = ft_extract(save);
	save = ft_st_save(save);
	return (line);
}
