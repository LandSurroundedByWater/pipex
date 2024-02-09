/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:26:01 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/09 09:31:04 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include "libft/libft.h"

# define ERR_INFILE "pipex: input"
# define ERR_OUTFILE "Outfile: "
# define ERR_ARG "Invalid arguments: \n"
# define ERR_PIPE "Pipe:"
# define ERR_FORK "Fork:"
# define ERR_MALLOC "Malloc:"
# define ERR_EXECVE "Execve:"
# define ERR_ACCESS "Access:"
# define ERR_CMD "Command not found:\n"

char	**parse_path(char **envp);
void	ft_free(char **arr);
void	ft_error(char *error);
char	*check_access(char **patharray, char *command);

#endif
