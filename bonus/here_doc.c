/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:19:55 by inightin          #+#    #+#             */
/*   Updated: 2022/02/06 22:57:25 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_here_doc(t_pipeline *pipeline, char *argv)
{
	char	*buf;
	int		here_doc;

	here_doc = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc < 0)
		error_exit("Heredoc error", 'p');
	while (1)
	{
		write(1, "here_doc>", 10);
		buf = get_next_line(0);
		if (!buf)
			error_heredoc("\nHeredoc error\n", 'w');
		if (!ft_strncmp(buf, argv, ft_strlen(argv))
			&& (ft_strlen(buf) - 1 == ft_strlen(argv)))
			break ;
		write(here_doc, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(here_doc);
	pipeline->read_file = open(".here_doc", O_RDONLY);
	if (pipeline->read_file < 0)
		error_heredoc("Heredoc error", 'p');
}
