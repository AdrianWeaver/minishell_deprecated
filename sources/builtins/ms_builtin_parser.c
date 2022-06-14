/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:27:19 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/14 07:48:39 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_builtin_parser(t_arg *arg)
{
	if (arg && ft_strcmp(arg->content, "echo") == 0)
	{
		ft_echo(arg->next);
		ft_clear_echo_args(arg);
	}
}
