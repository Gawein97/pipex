/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:59:20 by inightin          #+#    #+#             */
/*   Updated: 2022/01/30 22:20:42 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include <stdio.h>
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
	while(p_paths[i])
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

void free_arrays(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

int main(int argc, char *argv[], char *envp[])
{
	char	**p_paths;
	char	*cmd_paths[2];
	char	**cmd1_v;
	char	**cmd2_v;
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		write(2, "Incorrect number of arguments, expected 4\n", 43);
		return (1);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
	{
		perror("Infile:");
		exit(1);
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
	{
		perror("Outfile:");
		exit(1);
	}
	p_paths = get_possible_paths(envp);
	if (!p_paths)
	{
		write(2, "Cannot receive  envp PATH\n", 27);
		exit(1);
	}
	cmd1_v = ft_split(argv[2], ' ');
	cmd2_v = ft_split(argv[3], ' ');
	//printf("%s\n %s\n", cmd1_v[0], cmd2_v[0]);
	if (cmd1_v == NULL | cmd2_v == NULL)
	{
		write(2, "Allocation fail\n", 17);
		free_arrays(p_paths);
		exit(1);
	}
	//cmd_paths[0] = get_cmd_path(p_paths, cmd1_v[0]);
	//cmd_paths[1] = get_cmd_path(p_paths, cmd2_v[0]);
	//printf("%s\n %s\n", cmd_paths[0], cmd_paths[1]);
	// if (!cmd_paths[0] | !cmd_paths[1])
	// {
	// 	perror("Command fails:");
	// 	exit(1);
	// }
	if (pipe(fd) == -1)
    {
		perror("Pipe fail:");
		exit(1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Process fail:");
		free_arrays(p_paths);
		free_arrays(cmd1_v);
		free_arrays(cmd2_v);
		exit(1);
	}
	if (pid1 == 0)
	{
		// Child process for 1 command
		cmd_paths[0] = get_cmd_path(p_paths, cmd1_v[0]);
		if (!cmd_paths[0])
		{
			write(2, "Command execution fail cmd1\n", 29);
			free(cmd_paths[0]);
			free_arrays(p_paths);
			free_arrays(cmd1_v);
			exit(1);
		}
		dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
		close(fd[1]);
		dup2(infile, STDIN_FILENO);
        execve(cmd_paths[0], cmd1_v, envp);
		free(cmd_paths[0]);
		free_arrays(p_paths);
		free_arrays(cmd1_v);
		perror("Comand execution fail");
		exit(1);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Process fail");
		exit(1);
	}
	if (pid2 == 0)
    {
        // Child process for second command
		cmd_paths[1] = get_cmd_path(p_paths, cmd2_v[0]);
		if (!cmd_paths[1])
		{
			write(2, "Command execution fail cmd2\n", 29);
			free(cmd_paths[1]);
			free_arrays(p_paths);
			free_arrays(cmd2_v);
			exit(1);
		}
        dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
        close(fd[0]);
		close(fd[1]);
        execve(cmd_paths[1], cmd2_v, envp);
		free(cmd_paths[1]);
		free_arrays(p_paths);
		free_arrays(cmd1_v);
		perror("Comand execution fail");
		exit(1);
    }
	close(outfile);
	close(infile);
	close(fd[0]);
	close(fd[1]);
	free_arrays(p_paths);
	free_arrays(cmd1_v);
	free_arrays(cmd2_v);
	free(cmd_paths[0]);
	free(cmd_paths[1]);
	waitpid(pid2, NULL, 0);
	waitpid(pid1, NULL, 0);
	return (0);
}