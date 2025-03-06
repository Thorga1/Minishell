/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:11:25 by tordner           #+#    #+#             */
/*   Updated: 2025/03/06 18:19:52 by tordner          ###   ########.fr       */
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

void	add_node_to_list(t_smd **head, t_smd *new_node)
{
	t_smd	*temp;

	if (!head || !new_node)
		return;
	if (*head == NULL)
	{
		*head = new_node;
			return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_smd	parse_tokens_to_list(char **tokens)
{
	t_smd	*cmd_list;
	t_smd	*new_node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		new_node = create_new_node();
	}
}