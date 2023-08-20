/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:31:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/20 15:13:37 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_print_env(t_list **is_envp_list)
{
	t_env	**env_lst;
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	env_lst = ft_sortenv(is_envp_list);
	while (env_lst && env_lst[i])
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, env_lst[i]->name, ft_strlen(env_lst[i]->name));
		s = ft_getenv(*is_envp_list, env_lst[i]->name);
		if (s && s[0])
		{
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, s, ft_strlen(s));
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	free(env_lst);
}

int	ft_isnum(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

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

char	*ft_strjoin_export(char const *s1, char const *s2)
{
	char				*str;
	unsigned int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (s1[0] == '\'' && s1[ft_strlen(s1) == '\''])
		s1 = ft_strtrim(s1, "\'");
	else if (s1[0] == '\"' && s2[ft_strlen(s2) == '\"'])
		s2 = ft_strtrim(s2, "\"");
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	return (str);
}
