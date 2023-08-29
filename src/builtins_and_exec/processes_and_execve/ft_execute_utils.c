/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:00:49 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/29 13:43:19 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_free_str(char *str)
{
	if (str)
	{
		free (str);
		str = NULL;
	}
	return (str);
}

void	ft_free_cmds(t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->count_cmd)
	{
		if (!is_builtin(data, i) && ft_getenv(data->envp_list, "PATH"))
			free (data->cmd[i].cmd);
		i++;
	}
}

static char	*error_path(t_shell *dt, char *command, char *to_free)
{
	if (to_free)
		free(to_free);
	dt->exit_code = 127;
	ft_putstr_fd("W3LC0M3-1N-sH3LL: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	return (0);
}

static char	*check_accessed_file(t_shell *dt, char *cmd, int fd, char *to_free)
{
	if (to_free)
		free(to_free);
	if (access(cmd, F_OK))
	{
		ft_no_file_dir(dt, -1, cmd, 127);
		return (0);
	}
	fd = open(cmd, O_WRONLY, -1);
	if (fd == -1 && errno == EISDIR && ft_isinset('/', cmd))
	{
		close(fd);
		ft_putstr_fd("W3LC0M3-1N-sH3LL: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		dt->exit_code = 126;
		return (0);
	}
	close (fd);
	if (access(cmd, F_OK) || (!access(cmd, F_OK) && !ft_isinset('/', cmd)))
		return (error_path(dt, cmd, 0));
	else if (access(cmd, X_OK))
		return (permission_error(cmd, dt));
	return (cmd);
}

char	*join_path(char *cmd, char **path, t_shell *dt, int i)
{
	char	*join;
	char	*command;

	command = ft_strjoin("/", cmd);
	if (!command)
		return (0);
	while (path[++i])
	{
		join = ft_strjoin(path[i], command);
		if (!join)
			return (ft_free_str(command));
		if (!access(join, F_OK) && !access(join, X_OK))
			break ;
		free (join);
	}
	if (path[i] && ft_strncmp(cmd, "./", 2))
	{
		free (command);
		return (join);
	}
	if (access(cmd, F_OK) && !ft_isinset('/', cmd))
		return (error_path(dt, cmd, command));
	else if (!check_accessed_file(dt, cmd, command, 0))
		return (0);
	return (ft_strdup(cmd));
}
