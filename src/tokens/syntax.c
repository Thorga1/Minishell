/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:40:53 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/22 14:53:50 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	classify_token(char *token)
{
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
	// if (token[0] == '$' && ft_strlen(token) > 1)
	// 	return (TOKEN_ENV_VAR);
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