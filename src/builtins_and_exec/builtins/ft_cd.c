/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/28 12:19:21 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_check_tilde(t_list **head, char *str)
{
	if (!ft_strlen(str) || *str != '~' || !ft_getenv(*head, "HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(ft_getenv(*head, "HOME"), str));
}

static int	check_no_home(t_shell *d, int num_cmd)
{
	if (ft_getenv(d->envp_list, "HOME") && ft_getenv(d->envp_list, "OLDPWD"))
		ft_putenv(&d->envp_list, "OLDPWD", ft_getenv(d->envp_list, "PWD"), 1);
	else if (!ft_getenv(d->envp_list, "HOME"))
	{
		if (!d->cmd[num_cmd].args[1])
			return (1);
		if (!ft_strncmp(d->cmd[num_cmd].args[1], "~", 1))
			return (1);
	}
	return (0);
}

int	check_old_pwd(char *oldpwd, t_shell *d)
{
	char	*home;

	if (!oldpwd)
	{
		home = ft_getenv(d->envp_list, "HOME");
		if (!home)
		{
			no_home_err(d);
			return (0);
		}
		if (chdir(home) == -1)
		{
			perror(home);
			return (0);
		}
		free(oldpwd);
		free(home);
	}
	else
		ft_putenv(&d->envp_list, "OLDPWD", oldpwd, 1);
	return (1);
}

static int	ft_cd2(int num_cmd, t_shell *d, char *new_pwd, int *err)
{
	if (!d->cmd[num_cmd].args[1])
	{
		if (check_no_home(d, num_cmd))
			return (no_home_err(d));
		*err = chdir(ft_getenv(d->envp_list, "HOME"));
	}
	else
	{
		new_pwd = ft_check_tilde(&d->envp_list, d->cmd[num_cmd].args[1]);
		*err = chdir(new_pwd);
		if (new_pwd)
			free(new_pwd);
	}
	return (-2);
}

int	ft_cd(t_shell *d, int num_cmd, char *new_pwd)
{
	int		err;
	char	*oldpwd;
	int		ret;

	oldpwd = getcwd(NULL, 0);
	if (!check_old_pwd(oldpwd, d))
		return (1);
	if (!d || !d->envp_list || !d->cmd[num_cmd].args[0])
		return (1);
	ret = ft_cd2(num_cmd, d, new_pwd, &err);
	if (ret != -2)
		return (ret);
	if (err)
		ft_print_perror(d, d->cmd[num_cmd].args[1], 1);
	else
	{
		err = ft_update_dir(d);
		d->exit_code = 0;
	}
	return (err);
}
