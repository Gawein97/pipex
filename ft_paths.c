/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:36:45 by inightin          #+#    #+#             */
/*   Updated: 2022/02/03 22:49:25 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

char	**get_possible_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strstr(envp[i], "PATH"))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char **p_paths, char *cmd)
{
	char	*tmp;
	char	*cmd_p;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (p_paths[i])
	{
		tmp = ft_strjoin(p_paths[i], "/");
		cmd_p = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_p, X_OK) != -1)
			return (cmd_p);
		free(cmd_p);
		i++;
	}
	return (NULL);
}
