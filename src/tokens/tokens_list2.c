/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:48:30 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/23 03:17:37 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(t_cmd *cmd, char **tokens, int *i)
{
	t_redirection	*redir;
	int				type;
	int				token_type;

	token_type = classify_token(tokens[*i]);
	if (!tokens[*i + 1])
		return (0);
	if (token_type == TOKEN_REDIRECTION_IN)
		type = 1;
	else if (token_type == TOKEN_REDIRECTION_OUT)
		type = 2;
	else if (token_type == TOKEN_APPEND)
		type = 3;
	else if (token_type == TOKEN_HEREDOC)
		type = 4;
	else
		type = 0;
	redir = create_redirection_node(type, ft_strdup(tokens[*i + 1]));
	if (!redir)
		return (0);
	add_redirection(cmd, redir);
	(*i)++;
	return (1);
}

t_cmd	*init_cmd_segment(t_cmd **cmd_list, char **tokens, int *i)
{
	t_cmd	*new;
	t_cmd	*tmp;

	if (classify_token(tokens[*i]) == TOKEN_PIPE)
		(*i)++;
	new = create_command_node();
	if (!new)
		return (NULL);
	if (!*cmd_list)
		*cmd_list = new;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

int	add_token_to_cmd(t_cmd *current, char **tokens, int *i)
{
	if (classify_token(tokens[*i]) == TOKEN_WORD)
	{
		if (!add_argument(current, ft_strdup(tokens[*i])))
			return (0);
	}
	else if (is_redirection(tokens[*i]))
	{
		if (!handle_redirection(current, tokens, i))
			return (0);
	}
	return (1);
}

t_cmd	*parse_tokens_to_list(char **tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current;
	int		i;

	cmd_list = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		if (!current || classify_token(tokens[i]) == TOKEN_PIPE)
		{
			current = init_cmd_segment(&cmd_list, tokens, &i);
			if (!current)
				return (free_cmd_list(cmd_list), NULL);
		}
		if (!add_token_to_cmd(current, tokens, &i))
			return (free_cmd_list(cmd_list), NULL);
		i++;
	}
	return (cmd_list);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		free_cmd_node(cmd_list);
		free(cmd_list);
		cmd_list = tmp;
	}
}
