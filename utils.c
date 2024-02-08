/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:43 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/08 15:19:24 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	ft_free(char **arr)
{
	int i;

	i = 0;
	while(!arr[i])
		free(arr[i]);
	free(arr);
}


char *check_access(char **patharray, char *command)
{
	int i;
	char *cmd_with_path;

	i = 0;
	while (patharray[i] != 0)
	{
		cmd_with_path = ft_strjoin(ft_strjoin(patharray[i], "/"), command);
		if (access(cmd_with_path, X_OK) == 0)
		{
			ft_free(patharray);
			return (cmd_with_path);
		}
		free(cmd_with_path);
		i++;
	}
	ft_free(patharray);
	return (NULL);
}

char	*parse_path(char *cmd, char **envp)
{
	int i;
	int j;
	char *pathline;
	char **patharray;

	j = 0;
	i = 0;
	while (envp[i] != 0)
	{
		if(ft_strncmp(envp[i], "PATH=", 4) == 0)
		{
			pathline = &envp[i][5];
			printf("%s", pathline);
			patharray = ft_split(pathline, ':');
			if (!patharray)
			{
				perror("split");
				ft_free(patharray);
				exit(EXIT_FAILURE);
			}
			return(check_access(patharray, cmd));
		}
		i++;
	}
	return (NULL);
}
