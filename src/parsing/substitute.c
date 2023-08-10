/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/10 15:42:25 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_realloc(void	*ptr, size_t size)
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

static int	ft_setinput_index(char *input, int input_index)
{
	if (ft_strnstr(input + input_index, "$?",
			ft_strlen(input)) == input + input_index)
		input_index += 2;
	if (ft_strnstr(input + input_index, "${?}",
			ft_strlen(input)) == input + input_index)
		input_index += 4;
	return (input_index);
}

static int	check_if_exit_code_substitute(char *input,
	int code, t_substitute *s, int is_continue)
{
	if (input[s->input_index] == '\'')
	{
		if (!s->is_quote)
			s->is_quote = 1;
		else
			s->is_quote = 0;
	}
	if ((ft_strnstr(&input[s->input_index], "$?", ft_strlen(input))
			== &input[s->input_index] || ft_strnstr(&input[s->input_index],
				"${?}", ft_strlen(input))
			== &input[s->input_index]) && !s->is_quote)
	{
		s->number_str = ft_itoa(code);
		s->number_len = ft_strlen(s->number_str);
		s->new_output = ft_realloc(s->output, s->output_size + s->number_len);
		if (s->new_output == NULL)
			return (2);
		s->output = s->new_output;
		ft_memcpy(s->output + s->output_size, s->number_str, s->number_len);
		s->output_size += s->number_len;
		s->input_index = ft_setinput_index(input, s->input_index);
		free(s->number_str);
		is_continue = 1;
	}
	return (is_continue);
}

static int	check_parentesis_substitute2(t_substitute *s)
{
	s->env_len = ft_strlen(s->env_value);
	s->new_output = ft_realloc(s->output, s->output_size + s->env_len);
	if (s->new_output == NULL)
		return (0);
	s->new_output = ft_realloc(s->output, s->output_size + s->env_len);
	if (s->new_output == NULL)
		return (0);
	s->output = s->new_output;
	ft_memcpy(s->output + s->output_size, s->env_value, s->env_len);
	s->output_size += s->env_len;
	return (1);
}

static int	check_parentesis_substitute(char *input,
	t_substitute *s, t_list *is_head)
{
	char	*var_name;

	var_name = NULL;
	s->input_index++;
	s->var_start = input + s->input_index;
	while (input[s->input_index] != '}' && input[s->input_index])
		s->input_index++;
	if (input[s->input_index] == '}')
	{
		s->var_len = &input[s->input_index] - s->var_start;
		var_name = malloc((s->var_len + 1) * sizeof(char));
		ft_memcpy(var_name, s->var_start, s->var_len);
		var_name[s->var_len] = '\0';
		s->env_value = ft_getenv(is_head, var_name);
		if (s->env_value)
		{
			if (!check_parentesis_substitute2(s))
				return (0);
		}
		s->input_index++;
	}
	if (var_name)
		free (var_name);
	return (1);
}

static int	check_classic_substitute2(t_substitute *s, const char *env_value)
{
	s->env_len = ft_strlen(env_value);
	s->new_output = ft_realloc(s->output, s->output_size + s->env_len);
	if (s->new_output == NULL)
		return (0);
	s->output = s->new_output;
	ft_memcpy(s->output + s->output_size, env_value, s->env_len);
	s->output_size += s->env_len;
	return (1);
}

static int	check_classic_substitute(t_substitute *s,
	char *input, t_list *is_head)
{
	char		*var_name;
	const char	*env_value;

	s->var_start = input + s->input_index;
	while (ft_isalnum(input[s->input_index]) || input[s->input_index] == '_')
		s->input_index++;
	s->var_len = input + s->input_index - s->var_start;
	var_name = malloc((s->var_len + 1) * sizeof(char));
	if (!var_name)
		return (0);
	ft_memcpy(var_name, s->var_start, s->var_len);
	var_name[s->var_len] = '\0';
	env_value = ft_getenv(is_head, var_name);
	if (env_value)
	{
		if (!check_classic_substitute2(s, env_value))
			return (0);
	}
	if (var_name)
		free (var_name);
	return (1);
}

static int	is_substitute(t_substitute *s, char *input,
	t_list *is_head, int tmp)
{
	s->input_index++;
	if (input[s->input_index] == '{')
	{
		tmp = check_parentesis_substitute(input, s, is_head);
		if (tmp == 0)
			return (0);
	}
	else if (input[s->input_index])
	{
		tmp = check_classic_substitute(s, input, is_head);
		if (tmp == 0)
			return (0);
	}
	else
	{
		s->output = ft_realloc(s->output, s->output_size + 1);
		if (s->output == NULL)
			return (0);
		s->output[s->output_size++] = '$';
	}
	return (1);
}

static int	substitute_loop(char *input, int code,
	t_list *is_head, t_substitute *s)
{
	int	tmp;

	tmp = check_if_exit_code_substitute(input, code, s, 0);
	if (tmp == 1)
		return (1);
	else if (tmp == 2)
		return (0);
	if (input[s->input_index] == '$' && !s->is_quote)
	{
		tmp = is_substitute(s, input, is_head, 0);
		if (tmp == 0)
			return (0);
	}
	else
	{
		s->output = ft_realloc(s->output, s->output_size + 1);
		if (s->output == NULL)
			return (0);
		s->output[s->output_size++] = input[s->input_index++];
	}
	return (2);
}

char	*substitute_variables(char	*input, int code, t_list	*is_head)
{
	t_substitute	s;
	int				tmp;

	s.var_name = NULL;
	s.number_len = 0;
	s.number_str = NULL;
	s.output = NULL;
	s.new_output = NULL;
	s.output_size = 0;
	s.input_index = 0;
	s.is_quote = 0;
	while (input[s.input_index])
	{
		tmp = substitute_loop(input, code, is_head, &s);
		if (tmp == 1)
			continue ;
		else if (tmp == 0)
			return (NULL);
	}
	s.output = ft_realloc(s.output, s.output_size + 1);
	if (s.output == NULL)
		return (NULL);
	s.output[s.output_size] = '\0';
	return (s.output);
}
