/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:16:41 by inightin          #+#    #+#             */
/*   Updated: 2022/02/04 03:57:41 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pipeline {
	char	**p_paths;
	char	*cmd_path;
	char	**cmd_v;
	pid_t	pid1;
	pid_t	pid2;
	int		read_file;
	int		write_file;
	int		fd[2];
}t_pipeline;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char const *s1, char const *s2);
char	**get_possible_paths(char **envp);
char	*get_cmd_path(char **p_paths, char *cmd);
char	*ft_strstr(char *str, char *to_find);
char	**get_possible_paths(char **envp);
char	*get_cmd_path(char **p_paths, char *cmd);
void	ft_child_process(t_pipeline pipeline, char *argv, char *envp[],
			char flag);
void	free_cmd_pipeline(t_pipeline *pipeline);
void	error_exit(char *msg, char c);
void	free_arrays(char **arr);
void	fd_pipeline_close(t_pipeline *pipeline);
#endif
