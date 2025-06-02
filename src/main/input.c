/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:15 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/02 23:56:18 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		printf("  Redirection - Type: %d, File: %s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void	print_cmd_list(t_cmd *cmd_list)
{
	int i;

	while (cmd_list)
	{
		printf("Command:\n");
		if (cmd_list->args)
		{
			i = 0;
			while (cmd_list->args[i])
			{
				printf("  Arg[%d]: %s\n", i, cmd_list->args[i]);
				i++;
			}
		}
		if (cmd_list->redir)
			print_redirections(cmd_list->redir);
		cmd_list = cmd_list->next;
	}
}

char	**parse_input(char *input, t_shell *shell)
{
	char	**tokens;
	int		i;

	tokens = tokenize_command(input, shell);
	if (!tokens)
	{
		printf(ERROR_TOKEN);
		shell->exit_status = 1;
		return (NULL);
	}
	if (validate_syntax(tokens))
	{
		i = 0;
		shell->exit_status = 2;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		return (NULL);
	}
	return (tokens);
}

void	process_input(char *input, t_shell *shell)
{
	char			**tokens;
	int				i;
	int				ret;
	t_cmd			*cmd_list;

	tokens = parse_input(input, shell);
	if (!tokens)
		return ;
	cmd_list = parse_tokens_to_list(tokens);
	print_cmd_list(cmd_list);
	if (cmd_list)
	{
		ret = execute_pipeline(cmd_list, shell);
		shell->exit_status = ret;
		free_cmd_list(cmd_list);
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
