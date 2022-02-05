/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:59:20 by inightin          #+#    #+#             */
/*   Updated: 2022/02/05 14:10:35 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_child_process(t_pipeline pipeline, char *argv, char *envp[])
{
	pipeline.cmd_v = ft_split(argv, ' ');
	if (!pipeline.cmd_v)
	{
		free_arrays(pipeline.cmd_v);
		free_arrays(pipeline.p_paths);
		error_exit("Mem alloc fail\n", 'w');
	}
	pipeline.cmd_path = get_cmd_path(pipeline.p_paths, pipeline.cmd_v[0]);
	if (!pipeline.cmd_path)
	{
		free_cmd_pipeline(&pipeline);
		error_exit("Command exec fail", 'p');
	}
	execve(pipeline.cmd_path, pipeline.cmd_v, envp);
	free_cmd_pipeline(&pipeline);
	error_exit("Command exec fail", 'p');
}

static void	file_validation(int argc, char *argv[], t_pipeline *pipeline)
{
	// if (argc != 5)
	// 	error_exit("Incorrect number of arguments, expected 4\n", 'w');
	pipeline->read_file = open(argv[1], O_RDONLY);
	if (pipeline->read_file < 0)
		error_exit("Cannot read file", 'p');
	pipeline->write_file = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline->write_file < 0)
		error_exit("Cannot create or open file", 'p');
	return ;
}

static void	error_exit_fork(char **ptr)
{
	free_arrays(ptr);
	error_exit("Fork fail", 'p');
	return ;
}
#include <stdio.h>
int	main(int argc, char *argv[], char *envp[])
{
	t_pipeline	pipeline;
	pid_t		pids[argc - 3];
	int			i;
	int			curr_pipe;
	int			pid_indx;
	i = 3;
	curr_pipe = 0;
	pid_indx = 0;
	pipeline.fd[0][0] = -1;
	pipeline.fd[0][1] = -1;
	pipeline.fd[1][0] = -1;
	pipeline.fd[1][1] = -1;
	file_validation(argc, argv, &pipeline);
	pipeline.p_paths = get_possible_paths(envp);
	if (!pipeline.p_paths)
		error_exit("Cannot get env PATH\n", 'w');
	while (i < argc)
	{
		if (pipe(pipeline.fd[curr_pipe]) < 0)
			error_exit("Pipe fail", 'p');
		pids[pid_indx] = fork();
		if (pids[pid_indx] < 0)
			error_exit_fork(pipeline.p_paths);
		if (pids[pid_indx] == 0)
		{
			if (i == 3) //first command
			{
				dup2(pipeline.read_file, STDIN_FILENO);
				close(pipeline.read_file);
			}
			if (i > 3)
			{
				dup2(pipeline.fd[1 - curr_pipe][0], STDIN_FILENO);
				close(pipeline.fd[1 - curr_pipe][0]);
			}
			if (i < (argc - 1))
			{
				dup2(pipeline.fd[curr_pipe][1], STDOUT_FILENO);
				close(pipeline.fd[curr_pipe][0]);
				close(pipeline.fd[curr_pipe][1]);
			}
			if ( i == (argc - 1))
			{
				dup2(pipeline.write_file, STDOUT_FILENO);
				close(pipeline.write_file);
			}
			pipeline.cmd_v = ft_split(argv[i - 1], ' ');
			if (!pipeline.cmd_v)
			{
				free_arrays(pipeline.cmd_v);
				free_arrays(pipeline.p_paths);
				error_exit("Mem alloc fail\n", 'w');
			}
			pipeline.cmd_path = get_cmd_path(pipeline.p_paths, pipeline.cmd_v[0]);
			if (!pipeline.cmd_path)
			{
				free_cmd_pipeline(&pipeline);
				error_exit("Command exec fail", 'p');
			}
			execve(pipeline.cmd_path, pipeline.cmd_v, envp);
			free_cmd_pipeline(&pipeline);
			error_exit("Command exec fail", 'p');
		}
		close(pipeline.fd[1 - curr_pipe][0]);
		close(pipeline.fd[curr_pipe][1]);
		curr_pipe = 1 - curr_pipe;
		i++;
		pid_indx++;
	}
	// if (pipe(pipeline.fd) == -1)
	// 	error_exit("Pipe fail", 'p');
	// pipeline.pid1 = fork();
	// if (pipeline.pid1 < 0)
	// 	error_exit_fork(pipeline.p_paths);
	// if (pipeline.pid1 == 0)
	// 	ft_child_process(pipeline, argv[2], envp);
	// pipeline.pid2 = fork();
	// if (pipeline.pid2 < 0)
	// 	error_exit_fork(pipeline.p_paths);
	// if (pipeline.pid2 == 0)
	// 	ft_child_process(pipeline, argv[3], envp);
	close(pipeline.read_file);
	close(pipeline.write_file);
	close(pipeline.fd[1 - curr_pipe][0]);
	while (pid_indx--)
		waitpid(pids[pid_indx], 0, 0);
	free_arrays(pipeline.p_paths);
	return (0);
}
