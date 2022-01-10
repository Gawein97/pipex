/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:24:34 by inightin          #+#    #+#             */
/*   Updated: 2022/01/06 03:56:59 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"

int main(int argc, char *argv[], char *envp[])
{
    // Execute with ping -c 2 gogle.com grep avg
    (void) argc;
    (void) argv;
    // char    *arg1[] = {
    //     "ping",
    //     "-c",
    //     "2",
    //     "google.com",
    //     NULL
    // };
    // char    *arg2[] = {
    //     "grep",
    //     "avg",
    //     NULL
    // };
    char    **cmd1;
    char    **cmd2;
    cmd1 = ft_split(argv[1], ' ');
    cmd2 = ft_split(argv[2], ' ');
    int fd[2];
    // fd[0] - read end
    // fd[1] - write end
    if (pipe(fd) == -1)
    {
        return (1);
    }

    int pid1 = fork();
    if (pid1 < 0)
        return (2);
    if (pid1 == 0)
    {
        // Child process 1 for (ping) command
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        execve("/sbin/ping", cmd1, envp);
    }
    
    int pid2 = fork();
    if (pid2 < 0)
        return (3);
    if (pid2 == 0)
    {
        // Child process 2 for (grep) command
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        execve("/usr/bin/grep", cmd2, envp);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid2, NULL, 0);
    waitpid(pid1, NULL, 0);
    return (0);
}