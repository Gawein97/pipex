/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:45:25 by inightin          #+#    #+#             */
/*   Updated: 2022/01/06 04:39:01 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

int main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	char	*path_var;
	char	**paths;
	char *cmd1 = "ping";
	char *cmd2 = "grep";
	char *whereis = "/whereis";
	cmd1 = ft_strjoin("/", cmd1);
	cmd2 = ft_strjoin("/", cmd2);
	while (*envp != NULL)
	{
		if (ft_strstr(*envp, "PATH"))
			path_var = *envp;
		envp++;
	}
	paths = ft_split(path_var + 5, ':');
	// printf("%s\n", path_var);
	int i = 0;
	// while (paths[i] != NULL)
	// {
	// 	printf("%s\n", paths[i]);
	// 	i++;
	// }
	i = 0;
	while (paths[i] != NULL)
	{
		char	*cmd1_path = ft_strjoin(paths[i], cmd1);
		char	*cmd2_path = ft_strjoin(paths[i], cmd2);
		char	*whereis_path = ft_strjoin(paths[i], whereis);
		if (access(cmd1_path, X_OK) != -1)
		{
			printf("Paths for %s is %s\n",cmd1, cmd1_path);
		}
		if (access(cmd2_path, X_OK) != -1)
		{
			printf("Paths for %s is %s\n",cmd2, cmd2_path);
		}
		if (access(whereis_path, X_OK) != -1)
		{
			printf("Paths for %s is %s\n",whereis, whereis_path);
		}
		i++;
	}
	return (0);
}