/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:17:12 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/23 01:17:17 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_heredoc(char *delim)
{
	int pipefd[2];
	char *line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}