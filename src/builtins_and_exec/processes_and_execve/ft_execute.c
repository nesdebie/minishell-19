/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:00:09 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/29 13:43:30 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_free_arr(char **arr, int flag)
{
	int	i;

	i = 0;
	if (flag > 0)
	{
		while (i < flag)
		{
			free(arr[i]);
			i++;
		}
	}
	else
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}

static char	**get_envp(t_list *lst)
{
	int		i;
	int		size;
	char	**mass;
	t_env	*env;

	size = ft_lstsize(lst) + 1;
	mass = malloc(size * sizeof(char *));
	if (!mass)
		return (0);
	i = 0;
	while (lst && i < size)
	{
		env = (t_env *)lst->content;
		mass[i++] = ft_join_env(env);
		if (!mass[i - 1])
		{
			ft_free_arr(mass, i - 1);
			return (0);
		}
		lst = lst->next;
	}
	mass[i] = NULL;
	return (mass);
}

char	**ft_get_path(t_shell *data)
{
	char	*tmp;
	char	**path;

	tmp = ft_getenv(data->envp_list, "PATH");
	if (!tmp)
		return (0);
	path = ft_split(tmp, ':');
	if (!path)
		return (0);
	return (path);
}

static int	cmd_with_path(t_shell *dt, char **path)
{
	int		i;

	i = -1;
	while (++i < dt->count_cmd)
	{
		if (!is_builtin(dt, i))
		{
			if (!ft_getenv(dt->envp_list, "PATH"))
			{
				if (!access(dt->cmd[i].cmd, X_OK))
					return (0);
				ft_no_file_dir(dt, -1, dt->cmd[i].cmd, 127);
				if (path)
					ft_free_arr(path, -1);
				return (1);
			}
			dt->cmd[i].cmd = join_path(dt->cmd[i].args[0], path, dt, -1);
		}
	}
	if (path)
		ft_free_arr(path, -1);
	return (0);
}

void	ft_executer(t_shell *data, char **path, char **envp, pid_t *id)
{
	if (!ft_strlen(data->cmd[0].cmd) && data->count_cmd == 1)
	{
		data->cmd[0].cmd = ft_free_str(data->cmd[0].cmd);
		ft_redir(data, &data->cmd[0], data->cmd->redir, 0);
	}
	else
	{
		ft_free_cmds(data);
		path = ft_get_path(data);
		if (cmd_with_path(data, path))
			return ;
		id = malloc(sizeof(pid_t) * data->count_cmd);
		if (!id)
			return ;
		envp = get_envp(data->envp_list);
		if (!envp)
		{
			free(id);
			return ;
		}
		ft_process_manager(id, data, envp, -1);
		free(id);
		ft_free_arr(envp, -1);
	}
	free_shell(data);
}
