/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:43:21 by inightin          #+#    #+#             */
/*   Updated: 2022/02/05 19:59:20 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// depending on the char writes message with errno or without
void	error_exit(char *msg, char c)
{
	if (c == 'p')
		perror(msg);
	else if (c == 'w')
		write(2, msg, ft_strlen(msg));
	exit(1);
}

void	error_exit_fork(char **ptr)
{
	free_arrays(ptr);
	error_exit("Fork fail", 'p');
	return ;
}
