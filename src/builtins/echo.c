/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/18 14:03:08 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value(char *var_name, t_shell *shell)
{
	int	i;
	int	var_len;

	if (!var_name || !shell || !shell->env)
		return (NULL);
	if (var_name[0] == '$')
		var_name++;
	var_len = strlen(var_name);
	i = 0;
	while (shell->env[i])
	{
		if (strncmp(shell->env[i], var_name, var_len) == 0
			&& shell->env[i][var_len] == '=')
			return (shell->env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

static int	is_env_var(char *str)
{
	return (str && str[0] == '$' && str[1] != '\0');
}

// static int	handle_output_redirection(t_cmd *cmd)
// {
// 	int	original_stdout;
// 	int	fd;

// 	if (cmd->outfile == NULL)
// 		return (0);
// 	original_stdout = dup(STDOUT_FILENO);
// 	if (original_stdout == -1)
// 	{
// 		perror("Erreur lors de la duplication de STDOUT");
// 		return (1);
// 	}
// 	if (cmd->append)
// 		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Erreur lors de l'ouverture du fichier de sortie");
// 		close(original_stdout);
// 		return (1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("Erreur lors de la redirection");
// 		close(fd);
// 		close(original_stdout);
// 		return (1);
// 	}
// 	close(fd);
// 	return (original_stdout);
// }

// static void	restore_stdout(int original_stdout)
// {
// 	if (original_stdout > 0)
// 	{
// 		dup2(original_stdout, STDOUT_FILENO);
// 		close(original_stdout);
// 	}
// }

int	ft_echo(t_cmd *cmd, t_shell *shell)
{
	int		print_newline;
	int		i;
	char	**args;
	// int		original_stdout;
	int		ret;
	char	*env_value;

	i = 1;
	print_newline = 1;
	args = cmd->args;
	// original_stdout = 0;
	ret = 0;
	// if (cmd->outfile != NULL)
	// {
	// 	original_stdout = handle_output_redirection(cmd);
	// 	if (original_stdout <= 0)
	// 		return (1);
	// }
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		print_newline = 0;
		i++;
	}
	int first = 1;
	while (args[i])
	{
		if (!first)
			printf(" ");

		if (is_env_var(args[i]))
		{
			env_value = get_env_value(args[i], shell);
			if (env_value)
				printf("%s", env_value);
		}
		else
		{
			printf("%s", args[i]);
		}
		first = 0;
		i++;
	}
	if (print_newline)
		printf("\n");

	// if (cmd->outfile != NULL)
	// {
	// 	restore_stdout(original_stdout);
	// }
	return (ret);
}
