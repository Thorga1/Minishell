/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:40:53 by thorgal           #+#    #+#             */
/*   Updated: 2025/05/30 15:16:30 by lfirmin          ###   ########.fr       */
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
	return (TOKEN_WORD);
}

int	validate_syntax(char **tokens)
{
	if (validate_pipes(tokens))
	{
		write(STDERR_FILENO, "Syntax error: unexpected pipe\n", 30);
		return (1);
	}
	if (validate_redirections(tokens))
		return (2);
	return (0);
}
