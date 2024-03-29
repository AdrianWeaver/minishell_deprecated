/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:02:09 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/23 12:30:44 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_char(t_env *env)
{
	char	**tab;
	int		env_size;
	int		i;

	i = 0;
	env_size = ft_env_size(env);
	tab = malloc(sizeof(*tab) * env_size + 1);
	tab[env_size] = 0;
	while (*env)
	{
		tab[i] = ft_strjoin(env->name, "=");
		tab[i] = ft_strjoin(tab[i], "=");
		i++;
	}
	return (tab);
}
