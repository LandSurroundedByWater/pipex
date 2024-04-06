/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:37:48 by tsaari            #+#    #+#             */
/*   Updated: 2024/04/06 14:22:40 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_cmd(char *str)
{
	int	i;
	int	x;

	x = -1;
	i = -0;
	while (str[++i] != 0)
	{
		if (str[i] != ' ')
			x = 1;
	}
	if (ft_strlen(str) == 0)
	{
		ft_error_cmd(ERR_PER, "");
		exit(126);
	}
	else if (x == -1)
	{
		ft_error_cmd(ERR_CMD, "");
		exit(127);
	}
}

void	free_array(char **s)
{
	size_t	i;

	i = 0;
	while (s[i] != NULL)
	{
		free (s[i]);
		i++;
	}
	free(s);
	exit(1);
}
