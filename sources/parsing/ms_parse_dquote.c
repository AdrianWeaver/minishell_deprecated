/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_dquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:09:57 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/24 11:28:41 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : check string and copy each char except opening and                  */
/*		closing double quotes                                                 */
/*	ARG : t_arg pointer *arg, int *tab dq_nbr which contains quote's          */
/*		indexes                                                               */
/*	RET : 0 if OK, -1 in case of error                                        */
/* ************************************************************************** */

int	ft_remove_quotes(t_arg *arg, int *dq_nbr)
{
	char	*temp;
	int		i;
	int		j;
	int		t;

	i = 0;
	j = 1;
	t = -1;
	temp = malloc(sizeof(char) * (ft_strlen(arg->content) + 1));
	if (!temp)
		return (-1);
	while (arg->content[i] != '\0')
	{
		if (j <= dq_nbr[0] && i == dq_nbr[j])
			j++;
		else
			temp[++t] = arg->content[i];
		i++;
	}
	temp[++t] = '\0';
	free(arg->content);
	arg->content = ft_strdup(temp);
	free(temp);
	return (0);
}

/* ************************************************************************** */
/*	ACT : check string and fill a int *tab with number et indexes of closing  */
/*		and opening double quotes                                             */
/*	ARG : t_arg pointer *arg,                                                 */
/*	RET : a pointer to malloc'd int *tab dq_nbr, NULL in case of error        */
/* ************************************************************************** */

int	*ft_count_quotes(t_arg *arg)
{
	int		i;
	int		dq;
	int		*dq_nbr;
	char	delim;

	i = -1;
	dq = 0;
	delim = 'n';
	while (arg->content[++i] != '\0')
	{
		if (arg->content[i] == '\'' || arg->content[i] == '"')
		{
			delim = arg->content[i];
			dq++;
		}
		if (delim != 'n')
		{
			while (arg->content[++i] && arg->content[i] != delim)
				;
			if (arg->content[i] && arg->content[i] == delim)
				dq++;
		}
	}
	dq_nbr = ft_lock_quote_pos(arg, dq);
	return (dq_nbr);
}

int	*ft_lock_quote_pos(t_arg *arg, int dq)
{
	int	*dq_nbr;

	if (dq != 0 && dq % 2 != 0)
		return (NULL);
	dq_nbr = calloc(sizeof(int), dq + 1);
	if (!dq_nbr)
		return (NULL);
	dq_nbr[0] = dq;
	ft_fill_q_tab(arg->content, dq_nbr);
	return (dq_nbr);
}
/* ************************************************************************** */
/*	ACT : check string for $VAR and calculate future position of dquote after */
/*		expanding or removing wrong $VAR name in string                       */
/*	ARG : t_arg pointer *arg, int *dq_nbr with initial position of dquotes,   */
/*		t_env pointer *env for checking if $NAME exists                       */
/*	RET : nothing                                                             */
/* ************************************************************************** */

void	ft_set_final_q_index(t_arg *arg, char *flags, int *dq_nbr, t_env *env)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 1;
	ret = 0;
	while (arg->content[i] != '\0')
	{
		if (j <= dq_nbr[0] && i == dq_nbr[j])
		{
			dq_nbr[j] = dq_nbr[j] + ret;
			j++;
		}
		if (flags[i] != '0' && arg->content[i] == '$' && arg->content[i + 1]
			&& ft_set_q_jump(&arg->content[i + 1]) > 0)
		{
			if (ft_check_var(&arg->content[i], env) > 0)
				ret += ft_expand_size(&arg->content[i + 1], env) - 1;
			else
				ret -= ft_set_q_jump(&arg->content[i + 1]) + 1;
		}
		i++;
	}
}

void	ft_fill_q_tab(char *str, int *dq_nbr)
{
	int		i;
	int		j;
	char	delim;

	i = -1;
	j = 0;
	delim = 'n';
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			delim = str[i];
			dq_nbr[++j] = i;
		}
		if (delim != 'n')
		{
			while (str[++i] && str[i] != delim)
				;
			if (str[i] && str[i] == delim)
				dq_nbr[++j] = i;
		}
	}
}
