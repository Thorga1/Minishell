/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:17:12 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/03 03:37:59 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	return (0);
}

static void	process_heredoc_input(int pipefd[2], char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd(\
				"minishell: warning: here-document delimited "
				"by end-of-file\n", 2);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char *delim)
{
	int	pipefd[2];

	if (!delim)
		return (1);
	if (create_heredoc_pipe(pipefd))
		return (1);
	process_heredoc_input(pipefd, delim);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		return (1);
	}
	close(pipefd[0]);
	return (0);
}
