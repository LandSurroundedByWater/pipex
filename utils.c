/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:43 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/09 10:56:45 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (!arr[i])
		free(arr[i]);
	free(arr);
}

char	*check_access(char **patharray, char *command)
{
	int		i;
	char	*cmd_with_path;

	i = 0;
	while (patharray[i] != 0)
	{
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
	ft_free(patharray);
	ft_error(ERR_ACCESS);
	return (NULL);
}

char	**parse_path(char **envp)
{
	int		i;
	int		j;
	char	*pathline;
	char	**patharray;

	j = 0;
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
