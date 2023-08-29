/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:36:09 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/29 09:24:30 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	suppress_output(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}

void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		exit(1);
	}
}

static void	handle_sigint(int sig)
{
	(void)sig;
	exit (1);
}

void	signals_init(void)
{
	suppress_output();
	signal(SIGINT, handle_sigint);
}
