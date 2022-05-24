/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:51:25 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/24 14:30:27 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_n_opt(t_arg *arg)
{
	int	n_opt;

	n_opt = 0;
	if (arg && ft_strcmp(arg->content, "-n") == 0)
		n_opt = 1;
	return (n_opt);
}

int	ft_echo_nbr_cmd(t_arg *arg)
{
	int	nbr_cmd;

	nbr_cmd = 0;
	while(arg && arg->token != TOKEN_PIPE)
	{
		if (arg->token == TOKEN_CMD)
			nbr_cmd++;
		arg = arg->next;
	}
	return (nbr_cmd);
}

void	ft_clear_echo_args(t_arg *arg)
{
	t_arg	*temp;

	temp = arg->next;
	while (temp && temp->token != TOKEN_PIPE)
	{
		temp = temp->next;
		free(arg->next->content);
		free(arg->next);
		arg->next = temp;
	}
}

int	ft_echo(t_arg *arg)
{
	char	*to_print;
	int		nbr_cmd;
	int		n_opt;
	
	n_opt = ft_echo_n_opt(arg);
	if (n_opt == 1)
		arg = arg->next;
	nbr_cmd = ft_echo_nbr_cmd(arg);
	to_print = ft_calloc(1, 1);
	while (arg && arg->token != TOKEN_PIPE)
	{
		if (arg->token == TOKEN_APPENDOUT || arg->token == TOKEN_OUTFILE
			|| arg->token == TOKEN_INFILE || arg->token == TOKEN_HEREDOC)
			ft_redirection(arg);
		else
		{
			to_print = ft_strjoin_free(to_print, arg->content);
			nbr_cmd--;
			if(nbr_cmd > 0)
				to_print = ft_strjoin_free(to_print, " ");
		}
		arg = arg->next;
	}
	if (n_opt == 0)
		to_print = ft_strjoin_free(to_print, "\n");
	printf("%s", to_print);
	free(to_print);
	return (0);
}
