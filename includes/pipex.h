/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:16:41 by inightin          #+#    #+#             */
/*   Updated: 2022/01/30 22:15:27 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char const *s1, char const *s2);
char	**get_possible_paths(char **envp);
char	*get_cmd_path(char **p_paths, char *cmd);
char	*ft_strstr(char *str, char *to_find);
#endif
