/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:31:54 by tsaari            #+#    #+#             */
/*   Updated: 2024/04/09 07:31:13 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_paths(char **patharray, char *command, char *cmd_with_path)
{
	int	i;

	i = 0;
	while (patharray[i] != 0)
	{
		if (access(cmd_with_path, X_OK) == 0)
		{
			ft_free(patharray);
			return (cmd_with_path);
		}
		cmd_with_path = ft_strjoin(ft_strjoin(patharray[i], "/"), command);
		if (!cmd_with_path)
			ft_error(ERR_MALLOC);
		if (access(cmd_with_path, X_OK) == 0)
		{
			ft_free(patharray);
			return (cmd_with_path);
		}
		free(cmd_with_path);
		i++;
	}
	return (NULL);
}

char	*check_access(char **patharray, char *command)
{
	char	*cmd_with_path;
	char	*cmd;

	if (access(command, X_OK) == 0)
		return (command);
	cmd_with_path = NULL;
	cmd = ft_strdup(command);
	cmd_with_path = check_paths(patharray, command, cmd_with_path);
	if (access(cmd_with_path, X_OK) == 0)
		return (cmd_with_path);
	free(cmd_with_path);
	ft_free(patharray);
	free(cmd);
	return (command);
}

char	**parse_path(char **envp)
{
	int		i;
	char	*pathline;
	char	**patharray;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 4) == 0)
		{
			pathline = &envp[i][5];
			patharray = ft_split(pathline, ':');
			if (!patharray)
				ft_error(ERR_MALLOC);
			return (patharray);
		}
		i++;
	}
	return (NULL);
}

static char	**split_command(char *cmd)
{
	char	**cmd_args;

	cmd_args = NULL;
	if (ft_strchr(cmd, '\'') != 0)
		cmd_args = ft_split_pipex(cmd, ' ');
	else
		cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
	{
		ft_error(ERR_MALLOC);
		exit (1);
	}
	return (cmd_args);
}

void	parse_command_paths(char *cmd, char **envp)
{
	char	**cmd_args;
	char	**paths;
	char	*cmd_path;
	int		dirfd;

	cmd_args = split_command(cmd);
	if (!cmd[0] || !cmd)
		ft_error(ERR_CMD);
	dirfd = open(cmd, O_DIRECTORY);
	if (dirfd == 1)
	{
		close(dirfd);
		ft_error_cmd(ERR_INFILE, cmd);
	}
	else if (ft_strchr(cmd_args[0], '/') != 0 && execute(cmd_args[0], \
	cmd_args, envp) == -1)
		ft_error_cmd(ERR_INFILE, cmd_args[0]);
	else
	{
		paths = parse_path(envp);
		cmd_path = check_access(paths, cmd_args[0]);
		if (execute(cmd_path, cmd_args, envp) == -1)
			ft_error_cmd(ERR_CMD, cmd_path);
		free(cmd_path);
	}
}
