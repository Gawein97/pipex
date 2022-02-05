/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:59:20 by inightin          #+#    #+#             */
/*   Updated: 2022/02/05 19:59:17 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	ft_execute_cmd(t_pipeline pipeline, char *argv, char *envp[])
{
	pipeline.cmd_v = ft_split(argv, ' ');
	if (!pipeline.cmd_v)
	{
		free_arrays(pipeline.cmd_v);
		free_arrays(pipeline.p_paths);
		free(pipeline.pids);
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
	if (argc < 5)
		error_exit("Incorrect number of arguments, expected at least 4\n", 'w');
	pipeline->read_file = open(argv[1], O_RDONLY);
	if (pipeline->read_file < 0)
		error_exit("Cannot read file", 'p');
	pipeline->write_file = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline->write_file < 0)
		error_exit("Cannot create or open file", 'p');
	return ;
}

static void	ft_descriptors_swap(t_pipeline pipeline, int i, int argc,
				int curr_pipe)
{
	if (i == 3)
		dup2_with_close(pipeline.read_file, STDIN_FILENO);
	if (i > 3)
		dup2_with_close(pipeline.fd[1 - curr_pipe][0], STDIN_FILENO);
	if (i < (argc - 1))
	{
		dup2(pipeline.fd[curr_pipe][1], STDOUT_FILENO);
		close(pipeline.fd[curr_pipe][0]);
		close(pipeline.fd[curr_pipe][1]);
	}
	if (i == (argc - 1))
		dup2_with_close(pipeline.write_file, STDOUT_FILENO);
	return ;
}

void	ft_multiple_cmds(t_pipeline *pipeline, int argc, char *argv[],
			char *envp[])
{
	int	i;

	i = 3;
	while (i < argc)
	{
		if (pipe(pipeline->fd[pipeline->curr_pipe]) < 0)
			error_exit("Pipe fail", 'p');
		pipeline->pids[pipeline->pid_indx] = fork();
		if (pipeline->pids[pipeline->pid_indx] < 0)
			error_exit_fork(pipeline->p_paths);
		if (pipeline->pids[pipeline->pid_indx] == 0)
		{
			ft_descriptors_swap(*pipeline, i, argc, pipeline->curr_pipe);
			ft_execute_cmd(*pipeline, argv[i - 1], envp);
		}
		close(pipeline->fd[1 - pipeline->curr_pipe][0]);
		close(pipeline->fd[pipeline->curr_pipe][1]);
		pipeline->curr_pipe = 1 - pipeline->curr_pipe;
		i++;
		pipeline->pid_indx++;
	}
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipeline	pipeline;
	int			i;

	i = 3;
	pipeline.pids = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
	if (!pipeline.pids)
		error_exit("Mem alloc fail\n", 'w');
	ft_init_pipeline(&pipeline);
	file_validation(argc, argv, &pipeline);
	pipeline.p_paths = get_possible_paths(envp);
	if (!pipeline.p_paths)
		error_exit("Cannot get env PATH\n", 'w');
	ft_multiple_cmds(&pipeline, argc, argv, envp);
	fd_pipeline_close(&pipeline);
	close(pipeline.fd[1 - pipeline.curr_pipe][0]);
	while (pipeline.pid_indx--)
		waitpid(pipeline.pids[pipeline.pid_indx], 0, 0);
	free_arrays(pipeline.p_paths);
	free(pipeline.pids);
	return (0);
}
