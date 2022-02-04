/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:59:20 by inightin          #+#    #+#             */
/*   Updated: 2022/02/04 23:47:45 by inightin         ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipeline	pipeline;
	pid_t		pids[argc - 3];
	int			i;
	int			curr_pipe;
	int			cmd;

	i = 1;
	curr_pipe = 0;
	cmd = 2;
	file_validation(argc, argv, &pipeline);
	pipeline.p_paths = get_possible_paths(envp);
	if (!pipeline.p_paths)
		error_exit("Cannot get env PATH\n", 'w');
	if (pipe(pipeline.fd[curr_pipe]) == -1)
		error_exit("Pipe fail", 'p');
	while (i < argc - 2)
	{
		if (pipe(pipeline.fd[curr_pipe]) < 0)
			error_exit("Pipe fail", 'p');
		pids[i - 1] = fork();
		if (pids[i - 1] < 0)
			error_exit_fork(pipeline.p_paths);
		if (pids[i - 1] == 0)
		{
			if (i > 1)
			{
				dup2(pipeline.fd[1 - curr_pipe][0], STDIN_FILENO);
				close(pipeline.fd[1 - curr_pipe][0]);
			}
			if (i < argc - 2)
			{
				dup2(pipeline.fd[curr_pipe][1], STDOUT_FILENO);
				close(pipeline.fd[curr_pipe][0]);
				close(pipeline.fd[curr_pipe][1]);
			}
			pipeline.cmd_v = ft_split(argv[cmd], ' ');
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
			//ft_child_process(pipeline, argv[cmd], envp);
		}
		close(pipeline.fd[1 - curr_pipe][0]);
		close(pipeline.fd[curr_pipe][1]);
		curr_pipe = 1 - curr_pipe;
		i++;
		cmd++;
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
	close(pipeline.fd[1 - curr_pipe][0]);
	while (i--)
		waitpid(pids[i - 2], 0, 0);
	fd_pipeline_close(&pipeline);
	free_arrays(pipeline.p_paths);
	return (0);
}
