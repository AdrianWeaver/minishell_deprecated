/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:10:20 by jcervoni          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/11 13:51:34 by jcervoni         ###   ########.fr       */
=======
/*   Updated: 2022/05/10 18:24:47 by jcervoni         ###   ########.fr       */
>>>>>>> UPDATE STRUCT.H / PARSING.H / MAIN.C :
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_arg
{
	int				token;
	char			*content;
	struct s_arg	*next;
}	t_arg;

typedef struct s_mlc
{
	void			*ptr;
	struct s_mlc	*next;
}	t_mlc;

typedef struct s_env
{
	char			*name;
<<<<<<< HEAD
	char			**content;
	struct s_env	*next;
}	t_env;	

#endif
=======
	char			*content;
	struct t_env	*next;
}	t_env;

#endif
>>>>>>> UPDATE STRUCT.H / PARSING.H / MAIN.C :
