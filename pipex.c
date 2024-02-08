/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:33:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/08 13:01:54 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"



void child_process(int *end, char **argv, char **envp)
{
	printf("moi");
	char **cmd_args;
	char *cmd_path;
	int ft_ch;

	ft_ch =  open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (end[1] < 0)
		exit (1);
	dup2(end[1], STDOUT_FILENO);
	dup2(ft_ch, STDIN_FILENO);
	close(end[0]);
	close(ft_ch);
	cmd_args = ft_split(argv[3], ' ');
	cmd_path = parse_path(cmd_args[0], envp);
	
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		printf("error");
		exit(0);
	}

	ft_free(cmd_args);

}

void parent_process(int *end, char **argv, char **envp)
{
	char **cmd_args;
	char *cmd_path;
	int ft_pr;

	ft_pr = open(argv[1], O_RDONLY);
	if (end[0] < 0)
		exit (1);
	dup2(end[1], STDIN_FILENO);
	dup2(ft_pr, STDOUT_FILENO);
	close(end[0]);
	close(ft_pr);
	cmd_args = ft_split(argv[2], ' ');
	cmd_path = parse_path(cmd_args[0], envp);
	printf("------>   %s\n\n", cmd_path);
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
        perror("execve");
        exit(EXIT_FAILURE);
    }

	ft_free(cmd_args);
}

int main(int argc, char **argv, char **envp)
{

	int end[2];
	pid_t pid1;


	if (argc == 5)
	{
		if (pipe(end) == -1)
			exit(-1);
		pid1 = fork();
		if (pid1 == -1)
		{
			printf("Error: %s\n", strerror(errno));
			exit(1);
		}
		if (pid1 == 0)
			child_process(end, argv, envp);
		else
		{
			waitpid(pid1, NULL, 0);
			parent_process(end, argv, envp);
		}

	}
	else
	{
		printf("Give four arguments");
		exit(1);
	}
    return (0);
}
