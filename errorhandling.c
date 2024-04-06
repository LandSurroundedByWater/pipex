/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 07:24:34 by tsaari            #+#    #+#             */
/*   Updated: 2024/04/06 14:17:41 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_cmd(char *error, char *cmd)
{
	write(2, error, ft_strlen(error));
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

void	ft_error(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	ft_infile_error(char *error, char *arg)
{
	write(2, error, ft_strlen(error));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

void	ft_file_error(char *error, char *arg)
{
	write(2, error, ft_strlen(error));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
