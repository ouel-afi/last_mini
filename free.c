/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:54:20 by taya              #+#    #+#             */
/*   Updated: 2025/07/25 14:44:47 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	free(lexer);
}

void	free_token(t_token *token)
{
	int i;

	if (!token)
		return ;
	if (token->cmds)
	{
		i = 0;
		while (token->cmds[i])
			free(token->cmds[i++]);
		free(token->cmds);
	}
	if (token->value)
		free(token->value);
	if (token->redir)
		free_token_list(token->redir);
	free(token);
}

void	free_token_list(t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < count)
		free(pipes[i++]);
	free(pipes);
}

void	free_pipeline_data(t_pipe_data *data)
{
	if (!data)
		return ;
	if (data->pipes)
		free_pipes(data->pipes, data->cmd_count - 1);
	if (data->pids)
		free(data->pids);
	free(data);
}
