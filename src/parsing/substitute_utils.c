/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:56:10 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/20 15:07:42 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		free(ptr);
		return (malloc(size));
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

static int	check_parentesis_substitute2(t_sub *s)
{
	s->env_len = ft_strlen(s->env_val);
	s->new_out = ft_realloc(s->output, s->out_size + s->env_len);
	if (s->new_out == NULL)
		return (0);
	s->new_out = ft_realloc(s->output, s->out_size + s->env_len);
	if (s->new_out == NULL)
		return (0);
	s->output = s->new_out;
	ft_memcpy(s->output + s->out_size, s->env_val, s->env_len);
	s->out_size += s->env_len;
	return (1);
}

int	check_parentesis_substitute(char *input, t_sub *s, t_list *is_head)
{
	char	*var_name;

	var_name = NULL;
	s->input_i++;
	s->var_start = input + s->input_i;
	while (input[s->input_i] != '}' && input[s->input_i])
		s->input_i++;
	if (input[s->input_i] == '}')
	{
		s->var_len = &input[s->input_i] - s->var_start;
		var_name = malloc((s->var_len + 1) * sizeof(char));
		ft_memcpy(var_name, s->var_start, s->var_len);
		var_name[s->var_len] = '\0';
		s->env_val = ft_getenv(is_head, var_name);
		if (s->env_val)
		{
			if (!check_parentesis_substitute2(s))
				return (0);
		}
		s->input_i++;
	}
	if (var_name)
		free (var_name);
	return (1);
}

static int	check_classic_substitute2(t_sub *s, const char *env_val)
{
	s->env_len = ft_strlen(env_val);
	s->new_out = ft_realloc(s->output, s->out_size + s->env_len);
	if (s->new_out == NULL)
		return (0);
	s->output = s->new_out;
	ft_memcpy(s->output + s->out_size, env_val, s->env_len);
	s->out_size += s->env_len;
	return (1);
}

int	check_classic_substitute(t_sub *s, char *input, t_list *is_head)
{
	char		*var_name;
	const char	*env_val;

	s->var_start = input + s->input_i;
	while (ft_isalnum(input[s->input_i]) || input[s->input_i] == '_')
		s->input_i++;
	s->var_len = input + s->input_i - s->var_start;
	var_name = malloc((s->var_len + 1) * sizeof(char));
	if (!var_name)
		return (0);
	ft_memcpy(var_name, s->var_start, s->var_len);
	var_name[s->var_len] = '\0';
	env_val = ft_getenv(is_head, var_name);
	if (env_val)
	{
		if (!check_classic_substitute2(s, env_val))
			return (0);
	}
	if (var_name)
		free (var_name);
	return (1);
}
