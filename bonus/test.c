# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../includes/pipex_bonus.h"

int main(int argc, char *argv[], char *envp[])
{
	int fd[2][2] = { {-1, -1 }, {-1, -1 }};
	int i = 3;
	int	curr_pipe = 0;
	char **paths = get_possible_paths(envp);
	int	pids[argc - 3];
	int read_f, write_f;
	int j = 0;

	read_f = open(argv[1], O_RDONLY);
	write_f = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (i < argc)
	{
		if (pipe(fd[curr_pipe]) < 0)
			exit(1);
		pids[j] = fork();
		if (pids[j] < 0)
			exit(1);
		if (pids[j] == 0)
		{
			if (i == 3) //first command
			{
				dup2(read_f, STDIN_FILENO);
				close(read_f);
			}
			if (i > 3)
			{
				dup2(fd[1 - curr_pipe][0], STDIN_FILENO);
				close(fd[1 - curr_pipe][0]);
			}
			if (i < argc - 1)
			{
				dup2(fd[curr_pipe][1], STDOUT_FILENO);
				close(fd[curr_pipe][0]);
				close(fd[curr_pipe][1]);
			}
			if ( i == (argc - 1))
			{
				dup2(write_f, STDOUT_FILENO);
				close(write_f);
			}
			char **cmd_v = ft_split(argv[i - 1], ' ');
			char *cmd_p = get_cmd_path(paths, cmd_v[0]);
			execve(cmd_p, cmd_v, envp);
			exit(1);
		}
		close(fd[1 - curr_pipe][0]);
		close(fd[curr_pipe][1]);
		curr_pipe = 1 - curr_pipe;
		i++;
		j++;
	}
	close(fd[1 - curr_pipe][0]);
	while (j--)
		waitpid(pids[j], 0, 0);
	return (0);
}