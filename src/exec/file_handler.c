/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:27:31 by tordner           #+#    #+#             */
/*   Updated: 2025/05/16 03:29:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *file, int flags, int mode)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, flags, mode);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	return (fd);
}

int	setup_files(t_redirection *redir)
{
	int	fd;

	if (!redir || !redir->file)
		return (1);
	if (redir->type == 1) // Redirection d'entrée (<)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			perror(redir->file);
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
			perror(redir->file);
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
			perror(redir->file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == 4) // Heredoc (<<)
	{
		if (handle_heredoc(redir->file) != 0)
			return (1);
	}
	return (0);
}

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