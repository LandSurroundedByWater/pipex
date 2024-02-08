/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:33:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/08 15:35:15 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void execute(char *cmd_path, char **cmd_args, char **envp)
{

	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror("execve");
		ft_free(cmd_args);
		exit(EXIT_FAILURE);
	}
	ft_free(cmd_args);
}
void parse_command_paths(char *cmd, char **envp)
{
	char **cmd_args;
	char *cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	cmd_path = parse_path(cmd_args[0], envp);
	if (cmd_path == NULL)
	{
		perror("ft_plit");
		exit(EXIT_FAILURE);
	}

	execute(cmd_path, cmd_args, envp);
}



void child_process(int *end, char **argv, char **envp)
{
	int fd_ch;

	fd_ch =  open(argv[1], O_RDONLY);
	if (fd_ch < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_ch, 0);
	dup2(end[1], 1);
	close(end[0]);
	parse_command_paths(argv[2], envp);
}

void parent_process(int *end, char **argv, char **envp)
{
	int fd_pr;

	fd_pr = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_pr < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_pr, 1);
	dup2(end[0], 0);
	close(end[1]);
	parse_command_paths(argv[3], envp);
}

int main(int argc, char **argv, char **envp)
{
	int end[2];
	pid_t pid1;

	if (argc == 5)
	{
		if (pipe(end) == -1) {
			perror("Pipe");
			exit(EXIT_FAILURE);
		}
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("Fork");
			exit(EXIT_FAILURE);
		}
		if (!pid1)
			child_process(end, argv, envp);
		parent_process(end, argv, envp);
	}
	else
	{
		printf("Give exactly four arguments");
		exit(1);
	}
	return (0);
}
