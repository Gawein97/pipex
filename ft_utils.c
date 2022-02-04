/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 03:45:29 by inightin          #+#    #+#             */
/*   Updated: 2022/02/04 03:57:34 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

// depending on the char writes message with errno or without
void	error_exit(char *msg, char c)
{
	if (c == 'p')
		perror(msg);
	else if (c == 'w')
		write(2, msg, ft_strlen(msg));
	exit(1);
}

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

void	fd_pipeline_close(t_pipeline *pipeline)
{
	close(pipeline->write_file);
	close(pipeline->read_file);
	close(pipeline->fd[0]);
	close(pipeline->fd[1]);
	return ;
}
