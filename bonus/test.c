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
	int i = 1;
	int	curr_pipe = 0;
	char **paths = get_possible_paths(envp);
	int	pids[argc - 1];

	while (i < argc)
	{
		if (pipe(fd[curr_pipe]) < 0)
			exit(1);
		pids[i - 1] = fork();
		if (pids[i - 1] < 0)
			exit(1);
		if (pids[i - 1] == 0)
		{
			if (i > 1)
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
			char **cmd_v = ft_split(argv[i], ' ');
			char *cmd_p = get_cmd_path(paths, cmd_v[0]);
			execve(cmd_p, cmd_v, envp);
			exit(1);
		}
		close(fd[1 - curr_pipe][0]);
		close(fd[curr_pipe][1]);
		curr_pipe = 1 - curr_pipe;
		i++;
	}
	close(fd[1 - curr_pipe][0]);
	while (i--)
		waitpid(pids[i - 1], 0, 0);
	return (0);
}