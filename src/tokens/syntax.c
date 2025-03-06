/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:40:53 by thorgal           #+#    #+#             */
/*   Updated: 2025/03/06 17:36:44 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_token_type	classify_token(char *token)
{
	if (!token || *token == '\0')
		return (TOKEN_UNKNOWN);
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(token, ">") == 0)
		return (TOKEN_REDIRECTION_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (TOKEN_APPEND);
	if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIRECTION_IN);
	if (ft_strcmp(token, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (token[0] == '$' && ft_strlen(token) > 1)
		return (TOKEN_ENV_VAR);
	return (TOKEN_WORD);
}

int	validate_syntax(char **tokens)
{
	if (validate_pipes(tokens))
	{
		printf("Syntax error: unexpected pipe\n");
		return (1);
	}
	if (validate_redirections(tokens))
		return (1);
	return (0);
}