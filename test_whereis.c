/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_whereis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 04:01:31 by inightin          #+#    #+#             */
/*   Updated: 2022/01/25 21:50:49 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include <fcntl.h>

char	*find_path_var(char *envp[])
{
	char	*path_var;
	while (*envp != NULL)
	{
		if (ft_strstr(*envp, "PATH"))
			path_var = *envp;
		envp++;
	}
	return (path_var);
}

char	*whereis_path(char *where, char **paths)
{
	int	i;
	char	*whereis_path;
	i = 0;
	while (paths[i] != NULL)
	{
		whereis_path = ft_strjoin(paths[i], where);
		if (access(whereis_path, X_OK) != -1)
		{
			return (whereis_path);
		}
		i++;
	}
	return (NULL);
}

char	*cmd_path(char	*whereis, char	*cmd, char	**envp)
{
	char	*cmd_path = (char *)malloc(sizeof(char) * 100);
	int	fd[2];
	char    *arg[] = {
		"whereis",
		cmd,
        NULL
    };

	if (pipe(fd) == -1)
        return (NULL);
	int pid1 = fork();
    if (pid1 < 0)
        return (NULL);
	if (pid1 == 0)
    {
		close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(whereis, arg, envp);
    }
	else
	{
		wait(NULL);
		close(fd[1]);
		read(fd[0], cmd_path, 100);
		close(fd[0]);
	}
	close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
	return (cmd_path);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)	argc;
	(void)	argv;
	char	**paths = ft_split(find_path_var(envp) + 5, ':');
	char	*whereis = whereis_path("/whereis", paths);
	char	*cmd_p;
	char    **cmd1 = ft_split(argv[1], ' ');
    char    **cmd2 = ft_split(argv[2], ' ');
    int fd[2];
	int file = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		printf("Cannot open file\n");
		return (1);
	}
	//cmd_p = cmd_path(whereis, cmd, envp);
	//cmd_p[ft_strlen(cmd_p) - 1] = '\0';
    if (pipe(fd) == -1)
        return (1);
    int pid1 = fork();
    if (pid1 < 0)
        return (2);
    if (pid1 == 0)
    {
        // Child process 1 for (ping) command
		cmd_p = cmd_path(whereis, cmd1[0], envp);
		cmd_p[ft_strlen(cmd_p) - 1] = '\0';
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        execve(cmd_p, cmd1, envp);
		write(2, "e\n", 2);
		exit(1);
    }
    int pid2 = fork();
    if (pid2 < 0)
        return (3);
    if (pid2 == 0)
    {
        // Child process 2 for (grep) command
		cmd_p = cmd_path(whereis, cmd2[0], envp);
		cmd_p[ft_strlen(cmd_p) - 1] = '\0';
        dup2(fd[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        execve(cmd_p, cmd2, envp);
    }
	//int wstatus;
	// waitpid(pid2, &wstatus, 0);
	// if (WIFEXITED(wstatus))
	// {
	// 	if (WEXITSTATUS(wstatus) != 0)
	// 	{
	// 		perror("Cannot execute command");
	// 		return (1);
	// 	}
	// }
	// else
	// 	return (1);
	close(fd[0]);
	close(fd[1]);
	close(file);
	return (0);
}