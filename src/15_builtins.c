/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:11:52 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/25 19:44:47 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_unset(t_minishell *mini, t_node *node, int len)
{
	t_env	*var;
	t_env	*prev;

	len = ft_arraylen(node->full_cmd);
	if (len > 1)
	{
		prev = NULL;
		var = mini->env;
		while (var)
		{
			if (!ft_strcmp(var->name, node->full_cmd[1]))
			{
				if (prev == NULL)
					mini->env = var->next;
				else
					prev->next = var->next;
				free(var->content);
				free(var->name);
				free(var);
				break ;
			}
			prev = var;
			var = var->next;
		}
	}
}

void	cd_to_home(t_minishell *mini, char **dir, t_env *old, t_env *pwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	*dir = find_env_var(&(mini->env), "HOME")->content;
	free(old->content);
	old->content = ft_strdup(cwd, 1);
	free(pwd->content);
	pwd->content = ft_strdup(*dir, 0);
}

void	cd_to_dir(t_node *node, char **dir, t_env *old)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	*dir = node->full_cmd[1];
	free(old->content);
	old->content = ft_strdup(cwd, 1);
}

int	ft_cd(t_minishell *mini, t_node *node, char *cwd, char *dir)
{
	int		len;
	t_env	*old;
	t_env	*pwd;

	len = ft_arraylen(node->full_cmd);
	old = find_env_var(&(mini->env), "OLDPWD");
	pwd = find_env_var(&(mini->env), "PWD");
	if (len == 2 && (!ft_strcmp(node->full_cmd[1], ".")
			|| !ft_strcmp(node->full_cmd[1], "")))
		return (0);
	else if ((len == 1) || (len == 2 && !ft_strcmp(node->full_cmd[1], "~")))
		cd_to_home(mini, &dir, old, pwd);
	else if (len == 2 && ft_strcmp(node->full_cmd[1], "."))
		cd_to_dir(node, &dir, old);
	else
		return (print_error(19, NULL), 1);
	if (dir && chdir(dir))
		return (print_error(20, dir), 1);
	else
	{
		free(pwd->content);
		cwd = getcwd(NULL, 0);
		pwd->content = ft_strdup(cwd, 1);
		return (0);
	}
}

void	execute_builtin(char *s, t_minishell *mini, int i)
{
	g_status = 0;
	if (!ft_strcmp(s, "echo") && mini->nbr_nodes != 1)
		ft_echo(mini->nodes[i], 1);
	else if (!ft_strcmp(s, "echo") && mini->nbr_nodes == 1)
		ft_echo(mini->nodes[i], mini->nodes[i]->outfile);
	else if (!ft_strcmp(s, "cd"))
		g_status = ft_cd(mini, mini->nodes[i], NULL, NULL);
	else if (!ft_strcmp(s, "pwd") && mini->nbr_nodes != 1)
		ft_pwd(1);
	else if (!ft_strcmp(s, "pwd") && mini->nbr_nodes == 1)
		ft_pwd(mini->nodes[i]->outfile);
	else if (!ft_strcmp(s, "export") && mini->nbr_nodes != 1)
		g_status = ft_export(mini, mini->nodes[i], 1);
	else if (!ft_strcmp(s, "export") && mini->nbr_nodes == 1)
		g_status = ft_export(mini, mini->nodes[i], mini->nodes[i]->outfile);
	else if (!ft_strcmp(s, "unset"))
		ft_unset(mini, mini->nodes[i], 1);
	else if (!ft_strcmp(s, "env") && mini->nbr_nodes != 1)
		g_status = ft_env(mini, mini->nodes[i], 1, 1);
	else if (!ft_strcmp(s, "env") && mini->nbr_nodes == 1)
		g_status = ft_env(mini, mini->nodes[i], 1, mini->nodes[i]->outfile);
	else if (!ft_strcmp(s, "exit"))
		g_status = ft_exit(mini, mini->nodes[i]);
}
