/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:00:09 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/12 15:40:52 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
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
			ft_free_arr(mass);
			return (0);
		}
		lst = lst->next;
	}
	mass[i] = NULL;
	return (mass);
}

static char	**ft_get_path(t_shell *data)
{
	char	*tmp;
	char	**path;

	tmp = ft_getenv(data->envp_list, "PATH");
	path = ft_split(tmp, ':');
	return (path);
}

static int	cmd_with_path(t_shell *dt, char **path)
{
	int		i;

	i = 0;
	while (i < dt->count_cmd)
	{
		if (!is_builtin(dt, i))
		{
			if (!ft_getenv(dt->envp_list, "PATH"))
			{
				if (access(dt->cmd[i].cmd, X_OK) == 0)
					return (0);
				ft_no_file_dir(dt, -1, dt->cmd[i].cmd);
				dt->exit_code = 127;
				return (-1);
			}
			dt->cmd[i].cmd = join_path(dt->cmd[i].args[0], path, dt);
		}
		i++;
	}
	return (0);
}

int	ft_executer(t_shell *data)
{
	pid_t	*id;
	char	**path;
	char	**envp;

	if (!data->cmd[0].cmd)
	{
		if (ft_redir(data, &data->cmd[0], data->cmd->redir, 0))
			return (0);
	}
	else
	{
		envp = get_envp(data->envp_list);
		path = ft_get_path(data);
		cmd_with_path(data, path);
		id = malloc(sizeof(pid_t) * data->count_cmd);
		if (!id)
			return (-1);
		ft_process_manager(id, data, envp, -1);
		free(id);
		if (path)
			ft_free_arr(path);
		ft_free_arr(envp);
	}
	return (0);
}
