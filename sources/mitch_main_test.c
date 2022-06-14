/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mitch_main_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/14 07:43:32 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_test(t_arg *arg, t_env *env)
{
	int		*dq;
	char	*flags;
	char	**pieces;

	dq = ft_count_quotes(arg);
	if (!dq)
		return (-1);
	flags = ft_get_var_pos(arg->content, env);
	ft_flag_char(arg->content, flags);
	printf("flags = %s\n", flags);
	if (dq[0] != 0)
		ft_set_final_q_index(arg, flags, dq, env);
	pieces = ft_lock_expand(ft_count_expand(arg, flags, env));
	if (!pieces)
		return (-1);
	// printf("ici\n");
	ft_final_string(arg, pieces, flags, env);
	if (flags)
		free(flags);
	ft_remove_quotes(arg, dq);
	if (dq)
		free(dq);
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	char	*test;
	t_arg	*verif;
	t_arg	*temp;
	t_env	*env_list;
	
	(void)env;
	(void)ac;
	(void)av;
	env_list = ft_env_to_list(env);
	while (1)
	{
		test = readline("Test readline :");
		if (ft_strcmp(test, "test") == 0)
		{
			free(test);
			exit (1);
		}
		
		verif = ft_get_args(test);
		temp = verif;
		if (verif != NULL)
		{
			ft_set_token(verif);
			while (verif != NULL)
			{
				verif = ft_get_infile(verif);
				verif = ft_get_heredoc(verif);
				verif = ft_get_outfile(verif);
				verif = ft_get_appendout(verif);
				if (verif->token == TOKEN_CMD)
				{
					if (ft_test(verif, env_list) == -1)
					{
						printf("Missing or extra dquote\n");
						exit(1);
					}
				}
				// printf("final content = %s,  token = %d\n", verif->content, verif->token);
				verif = verif->next;
			}
			verif = temp;
			while (verif)
			{
				ft_builtin_parser(verif);
				verif = verif->next;
			}
			verif = temp;
			while (verif)
			{
				printf("final content = %s,  token = %d\n", verif->content, verif->token);
				verif = verif->next;
			}
			// if (temp != NULL)
			// 	ft_cleararg(temp);
		}
	}
	return (0);
}
