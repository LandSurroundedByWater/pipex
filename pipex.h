/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:26:01 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/08 12:41:24 by tsaari           ###   ########.fr       */
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


#define READ_END     0
#define WRITE_END    1

char	*parse_path(char *cmd, char **envp);
void	ft_free(char **arr);

char	*check_access(char **patharray, char *command);

#endif
