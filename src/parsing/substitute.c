/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/08 16:41:53 by mebourge         ###   ########.fr       */
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
        return malloc(size);
    }
    new_ptr = malloc(size);
    if (new_ptr == NULL)
	{
        return NULL;
    }
    ft_memcpy(new_ptr, ptr, size);
    free(ptr);
    return new_ptr;
}

char* substitute_variables(char* input, int code, t_list *is_head)
{
    char* output = NULL;
    int output_size = 0;
    int input_index = 0;
	int is_quote = 0;
	char* var_start;
	int var_len;

    while (input[input_index] != '\0')
    {
		if (input[input_index] == '\'')
		{
			if (is_quote == 0)
				is_quote = 1;
			else
				is_quote = 0;
		}
		if ((ft_strnstr(input + input_index, "$?", ft_strlen(input)) == input + input_index || ft_strnstr(input + input_index, "${?}", ft_strlen(input)) == input + input_index) && is_quote == 0)
		{
			char *number_str;
			number_str = ft_itoa(code);
			int number_len = ft_strlen(number_str);
			char* new_output = ft_realloc(output, output_size + number_len);
			if (new_output == NULL)
			{
				free(output);
				return NULL;
			}
			output = new_output;
			ft_memcpy(output + output_size, number_str, number_len);
			output_size += number_len;
			if (ft_strnstr(input + input_index, "$?", ft_strlen(input)) == input + input_index)
			{
				input_index += 2;
			}
			if (ft_strnstr(input + input_index, "${?}", ft_strlen(input)) == input + input_index)
			{
				input_index += 4;
			}
			free(number_str);
			continue;
		}
        if (input[input_index] == '$' && is_quote == 0)
        {
            input_index++;
            if (input[input_index] == '{')
            {
                input_index++;
                var_start = input + input_index;
                while (input[input_index] != '}' && input[input_index] != '\0')
                {
                    input_index++;
                }
                if (input[input_index] == '}')
                {
                    var_len = input + input_index - var_start;
                    char var_name[var_len + 1];
                    ft_memcpy(var_name, var_start, var_len);
                    var_name[var_len] = '\0';
                    const char* env_value = ft_getenv(is_head, var_name);
                    if (env_value != NULL)
                    {
                        int env_len = ft_strlen(env_value);
                        char* new_output = ft_realloc(output, output_size + env_len);
                        if (new_output == NULL)
                        {
                            free(output);
                            return NULL;
                        }
                        output = new_output;
                        ft_memcpy(output + output_size, env_value, env_len);
                        output_size += env_len;
                    }
					input_index++;
                }
            }
            else if (input[input_index] != '\0')
            {
                char* var_start = input + input_index;
                while ((input[input_index] >= 'a' && input[input_index] <= 'z') ||
                       (input[input_index] >= 'A' && input[input_index] <= 'Z') ||
                       (input[input_index] >= '0' && input[input_index] <= '9') ||
                       input[input_index] == '_')
                {
                    input_index++;
                }
                int var_len = input + input_index - var_start;
                char var_name[var_len + 1];
                ft_memcpy(var_name, var_start, var_len);
                var_name[var_len] = '\0';
                const char* env_value = ft_getenv(is_head, var_name);
                if (env_value != NULL)
                {
                    int env_len = ft_strlen(env_value);
                    char* new_output = ft_realloc(output, output_size + env_len);
                    if (new_output == NULL)
                    {
                        free(output);
                        return NULL;
                    }
                    output = new_output;
                    ft_memcpy(output + output_size, env_value, env_len);
                    output_size += env_len;
                }
            }
            else
            {
                output = ft_realloc(output, output_size + 1);
                if (output == NULL)
                {
                    free(output);
                    return NULL;
                }
                output[output_size++] = '$';
            }
        }
        else
        {
            output = ft_realloc(output, output_size + 1);
            if (output == NULL)
            {
                free(output);
                return NULL;
            }
            output[output_size++] = input[input_index];
            input_index++;
        }
	}
    output = ft_realloc(output, output_size + 1);
    if (output == NULL)
    {
        free(output);
        return NULL;
    }
    output[output_size] = '\0';
    return output;
}