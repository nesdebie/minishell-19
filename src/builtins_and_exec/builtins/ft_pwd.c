/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:03:21 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/19 12:27:26 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_shell *data)
{
	char	*str;
	t_list	**is_envp_list;

	is_envp_list = &data->envp_list;
	str = ft_getenv(*is_envp_list, "PWD");
	if (str)
	{
		write(STDOUT_FILENO, str, ft_strlen(str));
		write(STDOUT_FILENO, "\n", 1);
	}
	ft_print_error(data, NULL, 0);
}
