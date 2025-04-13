/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:11:25 by tordner           #+#    #+#             */
/*   Updated: 2025/03/10 17:57:06 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_smd	*create_new_node(void)
{
	t_smd	*new_node;

	new_node = malloc(sizeof(t_smd));
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->append = 0;
	new_node->next = NULL;
	return (new_node);
}

t_smd	*parse_tokens_to_list(char **tokens)
{
	t_smd	*cmd_list;
	t_smd	*current;
	t_smd	*new_node;
	char	**new_args;
	int		arg_count;
	int		i;
	int		j;

	cmd_list = NULL;
	current = NULL;
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (!current)
		{
			current = create_new_node();
			if (!current)
				return (NULL);
			cmd_list = current;
		}
		if (classify_token(tokens[i]) == TOKEN_WORD)
		{
			arg_count = 0;
			while (current->args && current->args[arg_count])
				arg_count++;
			new_args = malloc(sizeof(char *) * (arg_count + 2));
			if (!new_args)
				return (NULL);
			j = 0;
			while (j < arg_count)
			{
				new_args[j] = current->args[j]; // Copy old args
				j++;
			}
			new_args[arg_count] = ft_strdup(tokens[i]);
			new_args[arg_count + 1] = NULL;
			free(current->args); // Free old args array
			current->args = new_args;
		}
		else if (classify_token(tokens[i]) == TOKEN_REDIRECTION_IN
			&& i > 0 && tokens[i - 1])
			current->infile = ft_strdup(tokens[i - 1]);
		else if (classify_token(tokens[i]) == TOKEN_REDIRECTION_OUT
			&& tokens[i + 1])
			current->outfile = ft_strdup(tokens[++i]);
		else if (classify_token(tokens[i]) == TOKEN_APPEND && tokens[i + 1])
		{
			current->outfile = ft_strdup(tokens[++i]);
			current->append = 1;
		}
		else if (classify_token(tokens[i]) == TOKEN_HEREDOC && tokens[i + 1])
			current->infile = ft_strdup(tokens[i + 1]);
		else if (classify_token(tokens[i]) == TOKEN_PIPE)
		{
			new_node = create_new_node();
			if (!new_node)
				return (NULL);
			current->next = new_node;
			current = new_node;
		}
		i++;
	}
	return (cmd_list);
}