/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:59:20 by inightin          #+#    #+#             */
/*   Updated: 2022/02/04 00:23:33 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

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

void	ft_first_child_process(t_pipeline pipeline, char *argv[], char *envp[])
{
	pipeline.cmd1_v = ft_split(argv[2], ' ');
	if (!pipeline.cmd1_v)
	{
		write(2, "Allocation fail\n", 17);
		free_arrays(pipeline.cmd1_v);
		free_arrays(pipeline.p_paths);
		exit(1);
	}
	// Child process for 1 command
	pipeline.cmd_paths[0] = get_cmd_path(pipeline.p_paths, pipeline.cmd1_v[0]);
	if (!pipeline.cmd_paths[0])
	{
		perror("Command execution fail cmd1");
		free(pipeline.cmd_paths[0]);
		free_arrays(pipeline.p_paths);
		free_arrays(pipeline.cmd1_v);
		exit(1);
	}
	dup2(pipeline.fd[1], STDOUT_FILENO);
	close(pipeline.fd[0]);
	close(pipeline.fd[1]);
	dup2(pipeline.read_file, STDIN_FILENO);
	execve(pipeline.cmd_paths[0], pipeline.cmd1_v, envp);
	free(pipeline.cmd_paths[0]);
	free_arrays(pipeline.p_paths);
	free_arrays(pipeline.cmd1_v);
	perror("Comand execution fail");
	exit(1);
}

void	ft_second_child_process(t_pipeline pipeline, char *argv[], char *envp[])
{
	pipeline.cmd2_v = ft_split(argv[3], ' ');
	if (!pipeline.cmd2_v)
	{
		write(2, "Allocation fail\n", 17);
		free_arrays(pipeline.cmd2_v);
		free_arrays(pipeline.p_paths);
		exit(1);
	}
	// Child process for second command
	pipeline.cmd_paths[1] = get_cmd_path(pipeline.p_paths, pipeline.cmd2_v[0]);
	if (!pipeline.cmd_paths[1])
	{
		perror("Command execution fail cmd2");
		free(pipeline.cmd_paths[1]);
		free_arrays(pipeline.p_paths);
		free_arrays(pipeline.cmd2_v);
		exit(1);
	}
	dup2(pipeline.fd[0], STDIN_FILENO);
	dup2(pipeline.write_file, STDOUT_FILENO);
	close(pipeline.fd[0]);
	close(pipeline.fd[1]);
	execve(pipeline.cmd_paths[1], pipeline.cmd2_v, envp);
	free(pipeline.cmd_paths[1]);
	free_arrays(pipeline.p_paths);
	free_arrays(pipeline.cmd1_v);
	perror("Comand execution fail");
	exit(1);
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipeline	pipeline;

	if (argc != 5)
	{
		write(2, "Incorrect number of arguments, expected 4\n", 43);
		return (1);
	}
	pipeline.read_file = open(argv[1], O_RDONLY);
	if (pipeline.read_file < 0)
	{
		perror("Cannot read file");
		exit(1);
	}
	pipeline.write_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline.write_file < 0)
	{
		perror("Cannot create or open file");
		exit(1);
	}
	pipeline.p_paths = get_possible_paths(envp);
	if (!pipeline.p_paths)
	{
		write(2, "Cannot receive  envp PATH\n", 27);
		exit(1);
	}
	if (pipe(pipeline.fd) == -1)
    {
		perror("Pipe fail");
		exit(1);
	}
	pipeline.pid1 = fork();
	if (pipeline.pid1 < 0)
	{
		perror("Process fail:");
		free_arrays(pipeline.p_paths);
		free_arrays(pipeline.cmd1_v);
		free_arrays(pipeline.cmd2_v);
		exit(1);
	}
	if (pipeline.pid1 == 0)
		ft_first_child_process(pipeline, argv, envp);
	pipeline.pid2 = fork();
	if (pipeline.pid2 < 0)
	{
		perror("Process fail");
		exit(1);
	}
	if (pipeline.pid2 == 0)
		ft_second_child_process(pipeline, argv, envp);
	close(pipeline.write_file);
	close(pipeline.read_file);
	close(pipeline.fd[0]);
	close(pipeline.fd[1]);
	free_arrays(pipeline.p_paths);
	// free_arrays(pipeline.cmd1_v);
	// free_arrays(pipeline.cmd2_v);
	// free(pipeline.cmd_paths[0]);
	// free(pipeline.cmd_paths[1]);
	waitpid(pipeline.pid2, NULL, 0);
	waitpid(pipeline.pid1, NULL, 0);
	return (0);
}