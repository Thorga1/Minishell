/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:27:31 by tordner           #+#    #+#             */
/*   Updated: 2025/04/19 14:48:32 by lfirmin          ###   ########.fr       */
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
	char	*file;

	if (redir->type == 1)
	{
		*file = open_file(av[1], O_RDONLY, 0);
		if (*file == -1)
			return (1);
	}
	else if (redir->type == 2)
	{
		*file = open_file(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*file == -1)
		{
			close(file);
			return (1);
		}
	}
	else if (redir->type == 3)
	{
		*file = open_file(av[4], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*file == -1)
			return (1);
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