/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:08:49 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/28 14:58:10 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**set_args(int count_args)
{
	char	**args;

	args = NULL;
	args = malloc(sizeof(char *) * (count_args + 1));
	if (!args)
		return (0);
	ft_memset(args, '\0', (sizeof(char *)) * (count_args + 1));
	args[count_args] = NULL;
	return (args);
}

static char	**init_cmd_args(t_list **lst, t_shell *data, int idx, int j)
{
	char	**args;
	char	*token;

	args = set_args(args_counter(*lst));
	while (args && args_counter(*lst) > 0)
	{
		token = (*lst)->content;
		if (*token == '<' || *token == '>')
		{
			ft_init_file(*lst, data->cmd, data, idx);
			(*lst) = (*lst)->next->next;
		}
		else
		{
			(*lst)->content = parse_line((*lst)->content, data); 
			if (!(*lst)->content)
				return (ft_free_arr_content(args, j, (*lst)->content));
			args[j] = ft_strdup((*lst)->content);
			if (!args[j])
				return (ft_free_arr_content(args, j - 1, (*lst)->content));
			j++;
			(*lst) = (*lst)->next;
		}
	}
	return (args);
}

static int	is_builtin_ll(char *token)
{
	if (token == NULL)
		return (0);
	if (!ft_strncmp(token, "cd", 3))
		return (1);
	else if (!ft_strncmp(token, "pwd", 4))
		return (1);
	else if (!ft_strncmp(token, "PWD", 4))
		return (1);
	else if (!ft_strncmp(token, "echo", 5))
		return (1);
	else if (!ft_strncmp(token, "env", 4))
		return (1);
	else if (!ft_strncmp(token, "ENV", 4))
		return (1);
	else if (!ft_strncmp(token, "exit", 5))
		return (1);
	else if (!ft_strncmp(token, "unset", 6))
		return (1);
	else if (!ft_strncmp(token, "export", 7))
		return (1);
	return (0);
}

static char	*find_cmd(t_list *lst, t_shell *data)
{
	char	*token;

	while (lst != NULL)
	{
		token = lst->content;
		if (is_builtin_ll(token))
			return (token);
		else if (is_non_builtin(token, data, NULL, -1))
			return (token);
		lst = lst->next;
	}
	return (0);
}

void	init_each_command(t_list **lst, t_shell *data, int i)
{
	char	*cmd;

	cmd = find_cmd(*lst, data);
	if (!ft_strncmp((*lst)->content, ">", 1)
		|| !ft_strncmp((*lst)->content, "<", 1))
	{
		if (!cmd)
			data->cmd[i].cmd = ft_calloc(1, 1);
		else
			data->cmd[i].cmd = ft_strdup(cmd);
		data->cmd[i].cmd = parse_line(data->cmd[i].cmd, data);
	}
	else
	{
		data->cmd[i].cmd = ft_strdup((*lst)->content);
		data->cmd[i].cmd = parse_line(data->cmd[i].cmd, data);
		while ((*lst)->next && data->cmd[i].cmd && data->cmd[i].cmd[0] == 0)
		{
			(*lst) = (*lst)->next;
			free(data->cmd[i].cmd);
			data->cmd[i].cmd = ft_strdup((*lst)->content);
			data->cmd[i].cmd = parse_line(data->cmd[i].cmd, data);
		}
	}
	data->cmd[i].args = init_cmd_args(lst, data, i, 0);
}
