/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:31:54 by tsaari            #+#    #+#             */
/*   Updated: 2024/04/06 14:19:01 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd_path, char **cmd_args, char **envp)
{
	if (execve(cmd_path, cmd_args, envp) == -1)
		ft_error_cmd(ERR_PER, cmd_path);
}

char	*check_paths(char **patharray, char *command, char *cmd_with_path)
{
	int	i;

	i = 0;
	while (patharray[i] != 0)
	{
		while (ft_strchr(command, '/') != 0)
			command = ft_strchr(command, '/') + 1;
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

	cmd_with_path = NULL;
	cmd = ft_strdup(command);
	cmd_with_path = check_paths(patharray, command, cmd_with_path);
	if (access(cmd_with_path, X_OK) == 0)
		return (cmd_with_path);
	else
	{
		ft_error_cmd(ERR_CMD, command);
		exit(127);
	}
	ft_free(patharray);
	if (ft_strchr(cmd, '/') != 0)
		ft_error_cmd(ERR_INFILE, cmd);
	free(cmd_with_path);
	free(cmd);
	return (NULL);
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

void	parse_command_paths(char *cmd, char **envp)
{
	char	**cmd_args;
	char	**paths;
	char	*cmd_path;

	if (!cmd[0] || !cmd)
		ft_error(ERR_CMD);
	if (ft_strchr(cmd, '\'') != 0)
		cmd_args = ft_split_pipex(cmd, ' ');
	else
		cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		ft_error(ERR_MALLOC);
	paths = parse_path(envp);
	cmd_path = check_access(paths, cmd_args[0]);
	if (cmd_path == NULL)
	{
		ft_free(cmd_args);
		free(cmd_path);
		ft_error_cmd(ERR_CMD, cmd);
	}
	else
		execute(cmd_path, cmd_args, envp);
	free(cmd_path);
	ft_free(cmd_args);
}
