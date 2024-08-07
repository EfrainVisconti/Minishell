/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:07:14 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/07 12:12:39 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// //linked list for enviroment variables
// typedef struct s_env
// {
// 	char			*name;
// 	char			*content;
// 	struct s_env	*next;
// }					t_env;

// //main struct for the program
// typedef struct s_minishell
// {
// 	t_env		*env;
// 	char		**bin_path;
// 	char		*input;
// 	char		**tokens;
// }					t_minishell;

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

//free program from main exit fuction
void	free_main(t_minishell *mini)
{
	free_array(mini->bin_path);
	free_env(mini->env);
}
