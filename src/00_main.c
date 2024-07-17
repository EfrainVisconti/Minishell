/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/17 15:37:35 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*find_env_var(t_env **env_var, char *name)
{
	t_env	*current;

	current = *env_var;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	set_bin_path(t_minishell *mini)
{
	t_env	*bin_path;

	bin_path = find_env_var(&(mini->env), "PATH");
	if (bin_path)
		mini->bin_path = ft_split(bin_path->content, ':');
	else
		mini->bin_path = NULL;
}

t_env	*new_env_node(char *name, char *content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}

void	set_env(char **env, t_minishell *mini)
{
	char	**split_env;
	t_env	*current;
	t_env	*new_node;

	while (*env != NULL)
	{
		split_env = ft_split(*env, '=');
		if (!split_env[0] || !split_env[1])
		{
			free_array(split_env);
			break ;
		}
		new_node = new_env_node(split_env[0], split_env[1]);
		if (!mini->env)
			mini->env = new_node;
		else
		{
			current = mini->env;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
		free_array(split_env);
		env++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*mini;
	char		*input;

	if (argc > 1)
		return (1);
	(void)argv;
	mini = (t_minishell *)malloc(sizeof(t_minishell));
	if (!mini)
		return (1);
	mini->input = (char *)malloc(sizeof(char *));
	if (!mini->input)
		return (1);
	mini->env = NULL;
	set_env(env, mini);
	set_bin_path(mini);
	while (1)
	{
		input = readline("minishell:");
		if (input == NULL)
			break ;
		mini->input = ft_strcpy(mini->input, input);
		add_history(input);
		if (!ft_strcmp(input, "exit"))
		{
			ft_printf("exit\n");
			break ;
		}
	}
	//testeo init
	//testeo end
	free(input);
	free_program(mini);
	return (0);
}
