/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:26:01 by tsaari            #+#    #+#             */
/*   Updated: 2024/04/06 13:48:42 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define ERR_INFILE "no such file or directory: "
# define ERR_OUTFILE "no such file or directory: "
# define ERR_ARG "Invalid  amount of arguments"
# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_MALLOC "Malloc error"
# define ERR_EXECVE "Execve error"
# define ERR_ACCESS "Access error"
# define ERR_CMD "command not found: "
# define ERR_PER "permission denied: "

char	**parse_path(char **envp);
void	ft_free(char **arr);
void	ft_error(char *error);
void	ft_error_cmd(char *error, char *cmd);
char	**ft_split_pipex(const char *so, char c);
char	*check_access(char **patharray, char *command);
void	execute(char *cmd_path, char **cmd_args, char **envp);
void	ft_file_error(char *error, char *arg);
void	ft_infile_error(char *error, char *arg);
void	ft_error_arg(int code);
void	parse_command_paths(char *cmd, char **envp);
void	check_cmd(char *str);
void	free_array(char **s);

#endif
