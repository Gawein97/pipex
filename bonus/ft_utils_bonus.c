/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 03:45:29 by inightin          #+#    #+#             */
/*   Updated: 2022/02/05 17:48:40 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
	free(pipeline->pids);
	return ;
}

void	fd_pipeline_close(t_pipeline *pipeline)
{
	close(pipeline->write_file);
	close(pipeline->read_file);
	return ;
}

void	ft_init_pipeline(t_pipeline *pipeline)
{
	pipeline->curr_pipe = 0;
	pipeline->pid_indx = 0;
	pipeline->fd[0][0] = -1;
	pipeline->fd[0][1] = -1;
	pipeline->fd[1][0] = -1;
	pipeline->fd[1][1] = -1;
	return ;
}

void	dup2_with_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
	return ;
}
