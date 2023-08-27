/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/27 19:35:04 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_setin_i(char *input, int in_i)
{
	if (ft_strnstr(input + in_i, "$?",
			ft_strlen(input)) == input + in_i)
		in_i += 2;
	return (in_i);
}

static int	is_substitute(t_sub *s, char *input, t_list *is_head, int tmp)
{
	s->in_i++;
	if (input[s->in_i])
	{
		tmp = check_classic_substitute(s, input, is_head);
		if (tmp == 0)
			return (0);
	}
	else
	{
		s->output = ft_realloc(s->output, s->out_size + 1);
		if (s->output == NULL)
			return (0);
		s->output[s->out_size++] = '$';
	}
	return (1);
}

static int	check_if_exit_code_substitute(char *str,
	int code, t_sub *s, int is_continue)
{
	int	len;

	len = ft_strlen(str);
	get_quote_sub_value(str, s);
	if ((ft_strnstr(&str[s->in_i], "$?", len)
			== &str[s->in_i]) && s->is_quote != '\'')
	{
		s->nb_str = ft_itoa(code);
		s->nb_len = ft_strlen(s->nb_str);
		s->new_out = ft_realloc(s->output, s->out_size + s->nb_len);
		if (s->new_out == NULL)
			return (2);
		s->output = s->new_out;
		ft_memcpy(s->output + s->out_size, s->nb_str, s->nb_len);
		s->out_size += s->nb_len;
		s->in_i = ft_setin_i(str, s->in_i);
		free(s->nb_str);
		is_continue = 1;
	}
	return (is_continue);
}

static int	substitute_loop(char *input, int code, t_list *is_head, t_sub *s)
{
	int	tmp;

	tmp = check_if_exit_code_substitute(input, code, s, 0);
	if (tmp == 1)
		return (1);
	else if (tmp == 2)
		return (0);
	if (input[s->in_i] == '$' && s->is_quote != '\'')
	{
		tmp = is_substitute(s, input, is_head, 0);
		if (tmp == 0)
			return (0);
	}
	else
	{
		s->output = ft_realloc(s->output, s->out_size + 1);
		if (s->output == NULL)
			return (0);
		s->output[s->out_size++] = input[s->in_i++];
	}
	return (2);
}

char	*substitute_variables(char	*input, int code, t_list	*is_head)
{
	t_sub	s;
	int		tmp;

	s.var_name = NULL;
	s.nb_len = 0;
	s.nb_str = NULL;
	s.output = NULL;
	s.new_out = NULL;
	s.out_size = 0;
	s.in_i = 0;
	s.is_quote = 0;
	while (input[s.in_i])
	{
		tmp = substitute_loop(input, code, is_head, &s);
		if (tmp == 1)
			continue ;
		else if (tmp == 0)
			return (NULL);
	}
	s.output = ft_realloc(s.output, s.out_size + 1);
	if (s.output == NULL)
		return (NULL);
	s.output[s.out_size] = '\0';
	return (s.output);
}
