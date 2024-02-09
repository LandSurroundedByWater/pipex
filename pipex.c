/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:33:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/09 11:41:56 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(char *cmd_path, char **cmd_args, char **envp)
{
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_args[0], 2);
		ft_free(cmd_args);
		free(cmd_path);
		return (-1);
	}
	return (0);
}

void	parse_command_paths(char *cmd, char **envp)
{
	char	**cmd_args;
	char	**paths;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
	{
		ft_free(cmd_args);
		ft_error(ERR_MALLOC);
	}
	paths = parse_path(envp);
	cmd_path = check_access(paths, cmd_args[0]);
	if (cmd_path == NULL)
	{
		ft_free(cmd_args);
		ft_free(paths);
		free(cmd_path);
		ft_error(ERR_MALLOC);
	}
	if (execute(cmd_path, cmd_args, envp) == -1)
	{
		ft_free(paths);
		exit(1);
	}
}

void	child_process(int *end, char **argv, char **envp)
{
	int	fd_ch;

	fd_ch = open(argv[1], O_RDONLY);
	if (fd_ch < 0)
	{
		ft_error(ERR_INFILE);
	}
	dup2(fd_ch, 0);
	dup2(end[1], 1);
	close(end[0]);
	parse_command_paths(argv[2], envp);
}

void	parent_process(int *end, char **argv, char **envp)
{
	int	fd_pr;

	fd_pr = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd_pr, 1);
	dup2(end[0], 0);
	close(end[1]);
	parse_command_paths(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		end[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(end) == -1)
			ft_error(ERR_PIPE);
		pid1 = fork();
		if (pid1 == -1)
			ft_error(ERR_FORK);
		if (!pid1)
			child_process(end, argv, envp);
		parent_process(end, argv, envp);
	}
	else
	{
		ft_error(ERR_ARG);
		return (1);
	}
	exit (1);
}
