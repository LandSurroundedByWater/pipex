/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:33:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/04/09 07:55:56 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_1_process(int fd_in, int *end, char **argv, char **envp)
{
	check_cmd(argv[2]);
	dup2(end[1], 1);
	close(end[0]);
	dup2(fd_in, STDIN_FILENO);
	parse_command_paths(argv[2], envp);
	close(fd_in);
	exit(0);
}

static void	child_2_process(int fd_out, int *end, char **argv, char **envp)
{
	check_cmd (argv[3]);
	dup2(end[0], 0);
	close(end[1]);
	dup2(fd_out, STDOUT_FILENO);
	parse_command_paths(argv[3], envp);
	close(fd_out);
	exit(0);
}

static void	make_childs(char **argv, char **envp, int *fd, int *end)
{
	pid_t	pid[2];
	int		status;

	pid[0] = fork();
	if (pid[0] == -1)
		ft_error(ERR_FORK);
	if (pid[0] == 0)
	{
		if (fd[0] >= 0)
			child_1_process(fd[0], end, argv, envp);
	}
	else
	{
		pid[1] = fork();
		if (pid[1] == -1)
			ft_error(ERR_FORK);
		if (pid[1] == 0)
			child_2_process(fd[1], end, argv, envp);
	}
	close(end[0]);
	close(end[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (status)
		exit (status);
}

static void	pipe_and_fork(char **argv, char **envp, int *fd)
{
	int	end[2];

	if (envp == NULL)
		ft_error_cmd(ERR_CMD, argv[3]);
	if (pipe(end) == -1)
		ft_error(ERR_PIPE);
	make_childs(argv, envp, fd, end);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc != 5)
	{
		ft_error(ERR_ARG);
	}
	else
	{
		fd[0] = open(argv[1], O_RDONLY);
		if (fd[0] < 0)
			ft_infile_error(ERR_INFILE, argv[1]);
		fd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (fd[1] < 0)
		{
			ft_file_error(ERR_OUTFILE, argv[4]);
			exit (1);
		}
		pipe_and_fork(argv, envp, fd);
	}
	exit (0);
}
