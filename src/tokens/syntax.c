/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:40:53 by thorgal           #+#    #+#             */
/*   Updated: 2025/03/03 13:24:14 by thorgal          ###   ########.fr       */
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
		return (TOKEN_REDIRECTION_APPEND);
	if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIRECTION_IN);
	if (ft_strcmp(token, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (token[0] == '$' && ft_strlen(token) > 1)
		return (TOKEN_ENV_VAR);
	if ((token[0] == '"' && token[ft_strlen(token) - 1] == '"') ||
		(token[0] == '\'' && token[ft_strlen(token) - 1] == '\''))
		return (TOKEN_QUOTED_STRING);
	return (TOKEN_ARGUMENT);
}

int	validate_syntax(char **tokens)
{
	
}