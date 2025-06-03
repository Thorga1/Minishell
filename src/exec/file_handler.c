/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:27:31 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 03:51:22 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_open_files(t_cmd *cmd)
{
	t_redirection	*redir;
	int				result;

	if (!cmd || !cmd->redir)
		return (0);
	redir = cmd->redir;
	while (redir)
	{
		result = setup_files(redir);
		if (result != 0)
			return (result);
		redir = redir->next;
	}
	return (0);
}

int	setup_input_redirections(t_redirection *redir)
{
	int				fd;
	t_redirection	*current;

	current = redir;
	while (current)
	{
		if (current->type == 1)
		{
			fd = open(current->file, O_RDONLY);
			if (fd == -1)
			{
				perror(current->file);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (current->type == 4)
		{
			if (handle_heredoc(current->file) != 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	has_input_redirection(t_redirection *redir)
{
	t_redirection	*current;

	current = redir;
	while (current)
	{
		if (current->type == 1 || current->type == 4)
			return (1);
		current = current->next;
	}
	return (0);
}
