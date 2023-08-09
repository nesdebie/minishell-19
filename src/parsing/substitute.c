/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/09 11:31:11 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void* ft_realloc(void* ptr, size_t size)
{
	void* new_ptr;

    if (size == 0)
	{
        free(ptr);
        return NULL;
    }
    if (ptr == NULL)
	{
        free(ptr);
        return malloc(size);
    }
    new_ptr = malloc(size);
    if (new_ptr == NULL)
	{
        free(ptr);
        return NULL;
    }
    ft_memcpy(new_ptr, ptr, size);
    free(ptr);
    return new_ptr;
}

static int ft_setinput_index(char *input, int input_index)
{
    if (ft_strnstr(input + input_index, "$?", ft_strlen(input)) == input + input_index)
		input_index += 2;
	if (ft_strnstr(input + input_index, "${?}", ft_strlen(input)) == input + input_index)
		input_index += 4;    
    return (input_index);
}

char* substitute_variables(char* input, int code, t_list *is_head)
{
    char *output;
    char *new_output;
    int output_size;
    int input_index;
	int is_quote;
	char *var_start;
	int var_len;
    char *number_str;
    int number_len;
    const char* env_value;
    int env_len;
    char *var_name;

    var_name = NULL;
    number_len = 0;
    number_str = NULL;
    output = NULL;
    new_output = NULL;
    output_size = 0;
    input_index = 0;
    is_quote = 0;
    while (input[input_index])
    {
		if (input[input_index] == '\'')
		{
			if (!is_quote)
				is_quote = 1;
			else
				is_quote = 0;
		}
		if ((ft_strnstr(&input[input_index], "$?", ft_strlen(input)) == &input[input_index] || ft_strnstr(&input[input_index], "${?}", ft_strlen(input)) == &input[input_index]) && !is_quote)
		{
			number_str = ft_itoa(code);
			number_len = ft_strlen(number_str);
			new_output = ft_realloc(output, output_size + number_len);
			if (new_output == NULL)
				return NULL;
			output = new_output;
			ft_memcpy(output + output_size, number_str, number_len);
			output_size += number_len;
			input_index = ft_setinput_index(input, input_index);
			free(number_str);
			continue;
		}
        if (input[input_index] == '$' && !is_quote)
        {
            input_index++;
            if (input[input_index] == '{')
            {
                input_index++;
                var_start = input + input_index;
                while (input[input_index] != '}' && input[input_index])
                    input_index++;
                if (input[input_index] == '}')
                {
                    var_len = &input[input_index] - var_start;
                    char var_name[var_len + 1];
                    ft_memcpy(var_name, var_start, var_len);
                    var_name[var_len] = '\0';
                    env_value = ft_getenv(is_head, var_name);
                    if (env_value)
                    {
                        env_len = ft_strlen(env_value);
                        new_output = ft_realloc(output, output_size + env_len);
                        if (new_output == NULL)
                            return NULL;
                        output = new_output;
                        ft_memcpy(output + output_size, env_value, env_len);
                        output_size += env_len;
                    }
					input_index++;
                }
            }
            else if (input[input_index])
            {
                var_start = input + input_index;
                while (ft_isalnum(input[input_index]) || input[input_index] == '_')
                    input_index++;
                var_len = input + input_index - var_start;
                char var_name[var_len + 1];
                ft_memcpy(var_name, var_start, var_len);
                var_name[var_len] = '\0';
                const char* env_value = ft_getenv(is_head, var_name);
                if (env_value)
                {
                    env_len = ft_strlen(env_value);
                    new_output = ft_realloc(output, output_size + env_len);
                    if (new_output == NULL)
                        return NULL;
                    output = new_output;
                    ft_memcpy(output + output_size, env_value, env_len);
                    output_size += env_len;
                }
            }
            else
            {
                output = ft_realloc(output, output_size + 1);
                if (output == NULL)
                    return NULL;
                output[output_size++] = '$';
            }
        }
        else
        {
            output = ft_realloc(output, output_size + 1);
            if (output == NULL)
                return NULL;
            output[output_size++] = input[input_index++];
        }
	}
    output = ft_realloc(output, output_size + 1);
    if (output == NULL)
        return (NULL);
    output[output_size] = '\0';
    return output;
}