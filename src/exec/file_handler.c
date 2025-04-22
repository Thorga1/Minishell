/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:27:31 by tordner           #+#    #+#             */
/*   Updated: 2025/04/22 14:28:54 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
	{
		write(1, "Error opening file\n", 20);
		return (-1);
	}
	return (fd);
}

int	setup_files(t_redirection *redir)
{
	int	fd;

	if (redir->type == 1) // Redirection d'entrée (<)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == 2) // Redirection de sortie (>)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == 3) // Redirection en mode append (>>)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	loop_open_files(t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redir;
	while (redir)
	{
		setup_files(redir);
		redir = redir->next;
	}
	return (0);
}