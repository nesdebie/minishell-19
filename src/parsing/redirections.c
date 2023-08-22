/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:11:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/22 18:56:36 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_heredoc(const char *end, int *fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!strncmp(line, end, ft_strlen(line) + 1) && *line)
			break ;
		rl_redisplay();
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

static void	heredoc(t_cmnd *cmd, const char *stop,
	struct termios *attr_out, struct termios *attr_in)
{
	int				fd[2];
	pid_t			id;

	attr_out = (struct termios *)malloc(sizeof(struct termios));
	if (!attr_out)
		return ;
	attr_in = (struct termios *)malloc(sizeof(struct termios));
	if (!attr_in)
		return (free_content(attr_out));
	pipe(fd);
	tcgetattr(STDOUT_FILENO, attr_out);
	tcgetattr(STDIN_FILENO, attr_in);
	id = fork();
	signal(SIGINT, SIG_IGN);
	if (!id)
		read_heredoc(stop, fd);
	close(fd[1]);
	waitpid(id, NULL, 0);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, attr_out);
	tcsetattr(STDIN_FILENO, TCSANOW, attr_in);
	free(attr_out);
	free(attr_in);
	dup2(fd[0], cmd->in_file);
	close(fd[0]);
}

static void	ft_check_fd(t_cmnd *cmd, t_redir **rd, t_list *lst)
{
	*rd = lst->content;
	if ((*rd)->mode == MODE_READ || (*rd)->mode == MODE_HEREDOC)
	{
		if (cmd->in_file)
			close(cmd->in_file);
	}
	else if ((*rd)->mode == MODE_APPEND || (*rd)->mode == MODE_WRITE)
	{
		if (cmd->out_file)
			close(cmd->out_file);
	}
}

static void	set_in_out(t_redir *rd, t_cmnd *cmd)
{
	char	*tmp;

	tmp = ft_strtrim(rd->name, "\"");
	if (!tmp)
		tmp = rd->name;
	remove_quotes(tmp);
	if (rd->mode == MODE_READ)
		cmd->in_file = open(tmp, O_RDONLY);
	else if (rd->mode == MODE_WRITE)
		cmd->out_file = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rd->mode == MODE_APPEND)
		cmd->out_file = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (rd->mode == MODE_HEREDOC)
		heredoc(cmd, tmp, NULL, NULL);
	if (tmp)
		free(tmp);
}

int	ft_redir(t_shell *data, t_cmnd *cmd, t_list *lst, int i)
{
	t_redir	*rd;

	while (lst)
	{
		if (data->count_cmd == 1)
			ft_check_fd(cmd, &rd, lst);
		else
			rd = lst->content;
		if (i == rd->idx)
		{
			set_in_out(rd, cmd);
			if (ft_no_file_dir(data, cmd->in_file, rd->name))
				return (1);
			else if (ft_no_file_dir(data, cmd->out_file, rd->name))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}
