/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:59:20 by inightin          #+#    #+#             */
/*   Updated: 2022/02/04 03:27:55 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	free_arrays(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

void	free_cmd_pipeline(t_pipeline *pipeline)
{
	free(pipeline->cmd_path);
	free_arrays(pipeline->p_paths);
	free_arrays(pipeline->cmd_v);
	return ;
}

// depending on the char writes message with errno or without
void	error_exit(char *msg, char c)
{
	if (c == 'p')
		perror(msg);
	else if (c == 'w')
		write(2, msg, ft_strlen(msg));
	exit(1);
}

void	ft_child_process(t_pipeline pipeline, char *argv, char *envp[],
			char flag)
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
	if (flag == 0)
	{
		dup2(pipeline.read_file, STDIN_FILENO);
		dup2(pipeline.fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(pipeline.fd[0], STDIN_FILENO);
		dup2(pipeline.write_file, STDOUT_FILENO);
	}
	close(pipeline.fd[0]);
	close(pipeline.fd[1]);
	execve(pipeline.cmd_path, pipeline.cmd_v, envp);
	free_cmd_pipeline(&pipeline);
	error_exit("Command exec fail", 'p');
}

// void	ft_second_child_process(t_pipeline pipeline, char *argv[], char *envp[])
// {
// 	pipeline.cmd2_v = ft_split(argv[3], ' ');
// 	if (!pipeline.cmd2_v)
// 	{
// 		write(2, "Allocation fail\n", 17);
// 		free_arrays(pipeline.cmd2_v);
// 		free_arrays(pipeline.p_paths);
// 		exit(1);
// 	}
// 	// Child process for second command
// 	pipeline.cmd_path = get_cmd_path(pipeline.p_paths, pipeline.cmd2_v[0]);
// 	if (!pipeline.cmd_path)
// 	{
// 		perror("Command execution fail cmd2");
// 		free(pipeline.cmd_path);
// 		free_arrays(pipeline.p_paths);
// 		free_arrays(pipeline.cmd2_v);
// 		exit(1);
// 	}
// 	dup2(pipeline.fd[0], STDIN_FILENO);
// 	dup2(pipeline.write_file, STDOUT_FILENO);
// 	close(pipeline.fd[0]);
// 	close(pipeline.fd[1]);
// 	execve(pipeline.cmd_path, pipeline.cmd2_v, envp);
// 	free(pipeline.cmd_path);
// 	free_arrays(pipeline.p_paths);
// 	free_arrays(pipeline.cmd_v);
// 	perror("Comand execution fail");
// 	exit(1);
// }
int	main(int argc, char *argv[], char *envp[])
{
	t_pipeline	pipeline;

	if (argc != 5)
		error_exit("Incorrect number of arguments, expected 4\n", 'w');
	pipeline.read_file = open(argv[1], O_RDONLY);
	if (pipeline.read_file < 0)
		error_exit("Cannot read file", 'p');
	pipeline.write_file = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline.write_file < 0)
		error_exit("Cannot create or open file", 'p');
	pipeline.p_paths = get_possible_paths(envp);
	if (!pipeline.p_paths)
		error_exit("Cannot get env PATH\n", 'w');
	if (pipe(pipeline.fd) == -1)
		error_exit("Pipe fail", 'p');
	pipeline.pid1 = fork();
	if (pipeline.pid1 < 0)
	{
		free_arrays(pipeline.p_paths);
		error_exit("Fork fail", 'p');
	}
	if (pipeline.pid1 == 0)
		ft_child_process(pipeline, argv[2], envp, 0);
	pipeline.pid2 = fork();
	if (pipeline.pid2 < 0)
	{
		free_arrays(pipeline.p_paths);
		error_exit("Fork fail", 'p');
	}
	if (pipeline.pid2 == 0)
		ft_child_process(pipeline, argv[3], envp, 1);
	close(pipeline.write_file);
	close(pipeline.read_file);
	close(pipeline.fd[0]);
	close(pipeline.fd[1]);
	waitpid(pipeline.pid2, NULL, 0);
	waitpid(pipeline.pid1, NULL, 0);
	free_arrays(pipeline.p_paths);
	return (0);
}
