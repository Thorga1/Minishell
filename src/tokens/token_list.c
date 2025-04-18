/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:11:25 by tordner           #+#    #+#             */
/*   Updated: 2025/04/18 14:02:48 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd			*cmd;
	t_redirection	*redir;
	t_redirection	*next_redir;
	int				i;

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		redir = cmd->redir;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->file);
			free(redir);
			redir = next_redir;
		}
		cmd = cmd->next;
		free(cmd_list);
		cmd_list = cmd;
	}
}

t_cmd	*create_command_node(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->redir = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_redirection	*create_redirection_node(int type, char *file)
{
	t_redirection *node;

	node = malloc(sizeof(t_redirection));
	if (!node)
		return NULL;
	node->type = type;
	node->file = file;
	node->next = NULL;
	return (node);
}

static int	add_argument(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_args;
	int		i;

	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	new_args = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (0);
	i = -1;
	while (++i < count)
		new_args[i] = cmd->args[i];
	new_args[count] = arg;
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}


void	add_redirection(t_cmd *cmd, t_redirection *redir)
{
	t_redirection	*last;

	if (!cmd || !redir)
		return ;
	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		last = cmd->redir;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}


static int	handle_redirection(t_cmd *cmd, char **tokens, int *i)
{
	t_redirection	*redir;
	int				type;

	type = classify_token(tokens[*i]);
	if (!tokens[*i + 1])
		return (0);
	redir = create_redirection_node(type, ft_strdup(tokens[*i + 1]));
	if (!redir)
		return (0);
	add_redirection(cmd, redir);
	(*i)++;
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
			if (classify_token(tokens[i]) == TOKEN_PIPE)
				i++;
			current = create_command_node();
			if (!current)
				return (free_cmd_list(cmd_list), NULL);
			if (!cmd_list)
				cmd_list = current;
			else
				current->next = current;
		}
		if (classify_token(tokens[i]) == TOKEN_WORD)
		{
			if (!add_argument(current, ft_strdup(tokens[i])))
				return (free_cmd_list(cmd_list), NULL);
		}
		else if (is_redirection(tokens[i]))
		{
			if (!handle_redirection(current, tokens, &i))
				return (free_cmd_list(cmd_list), NULL);
		}
		i++;
	}
	return (cmd_list);
}
