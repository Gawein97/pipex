/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inightin <inightin@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:50:03 by inightin          #+#    #+#             */
/*   Updated: 2022/01/06 04:38:56 by inightin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd[2];
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1)
    {
        printf("Error with opening the pipe\n");
        return (1);
    }
    int id = fork();
    if (id == -1)
    {
        printf("Failde to create fork process");
        return (1);
    }
    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("Input value of x: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            printf("Error in write\n");
            return (2);
        }
        close(fd[1]);
    }
    else
    {     
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            printf("Error in read\n");
            return (3);
        }
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }
    
    return (0);
}