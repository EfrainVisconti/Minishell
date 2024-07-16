/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:05:03 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/16 19:51:53 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include "../libs/libft/libft.h"

//linked list for enviroment variables
typedef struct s_env_lst
{
	char				*name;
	char				*content;
	struct s_env_lst	*next;
}					t_env_lst;

//main struct for the program
typedef struct s_minishell
{
	t_env_lst		*env_lst;
}					t_minishell;

#endif