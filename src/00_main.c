/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/16 20:49:57 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

t_env_lst *new_env_node(char *name, char *content)
{
    t_env_lst *new_node;

    new_node = (t_env_lst *)malloc(sizeof(t_env_lst));
    if (!new_node)
        return (NULL);
    new_node->name = ft_strdup(name);
    new_node->content = ft_strdup(content);
    new_node->next = NULL;
    return (new_node);
}

void    set_env(char **env, t_minishell *mini)
{
    char        **split_env;
    t_env_lst   *current;
    t_env_lst   *new_node;

    mini->env_lst = NULL;
    while (*env != NULL)
    {
        split_env = ft_split(*env, '=');
        if (!split_env[0] || !split_env[1])
			break;
        new_node = new_env_node(split_env[0], split_env[1]);
        if (!mini->env_lst)
            mini->env_lst = new_node;
        else
        {
            current = mini->env_lst;
            while (current->next)
                current = current->next;
            current->next = new_node;
        }
        free(split_env[0]);
        free(split_env[1]);
        free(split_env);
        env++;
    }
}

int main(int argc, char **argv, char **env)
{
	t_minishell *mini;

    if (argc > 1)
		return (1);
    (void)argv;
	mini = (t_minishell *)malloc(sizeof(t_minishell));
    if (!mini)
        return (1);
    set_env(env, mini);
	while (mini->env_lst != NULL)
	{
		ft_printf("%s %s\n", mini->env_lst->name, mini->env_lst->content);
		mini->env_lst = mini->env_lst->next;
	}
    return (0);
}
