/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:41:50 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/02 11:13:09 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_minishell(t_shell *data)
{
	if (data->envp_list)
		ft_free_env(&data->envp_list);
	if (data->cmd && data->count_cmd > 0)
		free_shell(data);
	exit(data->exit_code);
}

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	set_input_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	signal_handler2(int signo)
{
	if (signo == SIGINT)
		ft_putendl_fd("", 1);
}

/*
Boucle infinie qui affiche le prompt et attend l'input de l'utilisateur
*/
static void	ft_prompt(int ac, t_shell *shell)
{
	char	*str;

	str = NULL;
	while (ac > 0)
	{
		set_input_signals();
		str = readline("prompt> ");
		str = ft_strtrim(str, " ");
		signal(SIGINT, &signal_handler2);
		if (!str)
		{
			ft_putendl_fd("exit", 1);
			free(str);
			ft_exit_minishell(shell);
		}
		if (ft_strlen(str))
		{
			if (!parser(str, shell))
			{
				ft_executer(shell);
				free_shell(shell);
			}
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)av;
	shell.exit_code = 0;
	if (ac > 1)
	{
		ft_putendl_fd("No arguments allowed", 1);
		exit (127);
	}
	shell.envp_list = ft_init_env(&shell, envp);
	if (!shell.envp_list)
		return (0);
	shell.exit_code = 0;
	ft_prompt(ac, &shell);
	return (0);
}
