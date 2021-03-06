/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:16:41 by inightin          #+#    #+#             */
/*   Updated: 2022/02/06 22:56:43 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
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
	int		read_file;
	int		write_file;
	int		fd[2][2];
	int		curr_pipe;
	int		pid_indx;
	int		*pids;
	int		here_doc;
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
void	free_cmd_pipeline(t_pipeline *pipeline);
void	error_exit(char *msg, char c);
void	free_arrays(char **arr);
void	fd_pipeline_close(t_pipeline *pipeline);
void	error_exit_fork(char **ptr);
void	ft_init_pipeline(t_pipeline *pipeline);
void	dup2_with_close(int fd1, int fd2);
void	ft_here_doc(t_pipeline *pipeline, char *argv);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_save_buffer(int fd, char *save, char *buf);
char	*ft_st_save(char *save);
char	*ft_extract(char *save);
char	*get_next_line(int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	error_heredoc(char *str, char c);
#endif
