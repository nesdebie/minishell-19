/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:31:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/21 17:37:23 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_name_env(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
		i++;
	if (s[i - 1] == '+')
		i--;
	temp = ft_substr(s, 0, i);
	return (temp);
}

char	*get_value_env(char *s)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	if (!s)
	{
		temp = (char *)ft_calloc(1, sizeof(char));
		return (temp);
	}
	while (s[i] != '=' && s[i])
		i++;
	if (s[i] == '=')
		temp = ft_substr(s, i + 1, ft_strlen(s) - i);
	return (temp);
}