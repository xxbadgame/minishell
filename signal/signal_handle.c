/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:47:31 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/01 14:47:31 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sig_output(int *flag_stop, int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			*flag_stop = 1;
	}
}

static void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	g_sigint = 1;
	write(1, "\n", 1);
}

void	setup_signals(struct sigaction *sa_new, struct sigaction *sa_old)
{
	g_sigint = 0;
	sa_new->sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa_new->sa_mask);
	sa_new->sa_flags = 0;
	sigaction(SIGINT, sa_new, sa_old);
}
