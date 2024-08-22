/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:11:52 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/22 17:35:41 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_node *node, int fd)
{
	int	i;
	int	len;

	len = ft_arraylen(node->full_cmd);
	i = 1;
	if (!ft_strcmp(node->full_cmd[i], "-n"))
	{
		i++;
		while (node->full_cmd[i])
		{
			ft_putstr_fd(node->full_cmd[i], fd);
			if (i++ < len - 1)
				ft_putstr_fd(" ", fd);
		}
	}
	else
	{
		while (node->full_cmd[i])
		{
			ft_putstr_fd(node->full_cmd[i], fd);
			if (i++ < len - 1)
				ft_putstr_fd(" ", fd);
		}
		ft_putstr_fd("\n", fd);
	}
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_exit(t_minishell *mini, t_node *node)
{
	int	len;
	int	exit_status;

	exit_status = 2;
	len = ft_arraylen(node->full_cmd);
	if (len > 2 && is_numeric(node->full_cmd[1]))
	{
		print_error(16, NULL);
		return (1);
	}
	else if (len >= 2 && !is_numeric(node->full_cmd[1]))
		print_error(17, node->full_cmd[1]);
	else if (len == 1)
		exit_status = g_status;
	else if (len == 2 && is_numeric(node->full_cmd[1]))
	{
		exit_status = ft_atoi(node->full_cmd[1]) % 256;
	}
	free_main(mini);
	free(mini->input);
	if (mini->tokens && mini->tokens[0])
		free_array(mini->tokens);
	if (mini->nodes)
		free_nodes(mini->nodes);
	return (ft_putstr_fd("exit\n", 2), exit(exit_status), exit_status);
}

int	ft_env(t_minishell *mini, t_node *node, int len, int fd)
{
	t_env	*current;

	current = mini->env;
	len = ft_arraylen(node->full_cmd);
	if (len == 1)
	{
		while (current)
		{
			if (current->is_env)
			{
				ft_putstr_fd(current->name, fd);
				ft_putstr_fd("=", fd);
				ft_putstr_fd(current->content, fd);
				ft_putstr_fd("\n", fd);
				current = current->next;
			}
		}
		return (0);
	}
	else
	{
		print_error(18, node->full_cmd[1]);
		return (127);
	}
}

void	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd, fd);
		free(pwd);
	}
	ft_putstr_fd("\n", fd);
}

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

int	ft_cd(t_minishell *mini, t_node *node)
{
	char	*cwd;
	int		len;
	char	*dir;
	t_env	*old;
	t_env	*pwd;

	len = ft_arraylen(node->full_cmd);
	cwd = getcwd(NULL, 0);
	old = find_env_var(&(mini->env), "OLDPWD");
	pwd = find_env_var(&(mini->env), "PWD");
	if (len == 2 && (!ft_strcmp(node->full_cmd[1], ".") || !ft_strcmp(node->full_cmd[1], "")))
		return (free(cwd), 0);
	else if ((len == 1) || (len == 2 && !ft_strcmp(node->full_cmd[1], "~")))
	{
		dir = find_env_var(&(mini->env), "HOME")->content;
		free(old->content);
		old->content = ft_strdup(cwd, 1);
		free(pwd->content);
		pwd->content = ft_strdup(dir, 0);
	}
	else if (len == 2 && ft_strcmp(node->full_cmd[1], "."))
	{
		dir = node->full_cmd[1];
		free(old->content);
		old->content = ft_strdup(cwd, 1);
	}
	else
		return (print_error(19, NULL), free(cwd), 1);
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

void	simple_export_aux(t_env *cur, t_env **env, t_env *name, int *size, int fd)
{
	cur = *env;
	name = cur;
	while (name->is_printed == TRUE && name->next)
		name = name->next;
	while (cur)
	{
		if (ft_strcmp(name->name, cur->name) > 0 && cur->is_printed == FALSE)
			name = cur;
		cur = cur->next;
	}
	name->is_printed = TRUE;
	if (!name->is_exp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(name->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(name->content, fd);
	}
	else
	{
		ft_putstr_fd(name->name, fd);
	}
	ft_putstr_fd("\n", fd);
	(*size)--;
}

void	simple_export(t_env **env, int fd)
{
	t_env	*current;
	t_env	*name;
	int		size;

	size = 0;
	name = NULL;
	current = *env;
	while (current)
	{
		size++;
		current = current->next;
	}
	while (size > 1)
		simple_export_aux(current, env, name, &size, fd);
	current = *env;
	while (current)
	{
		current->is_printed = FALSE;
		current = current->next;
	}
}

int	ft_export(t_minishell *mini, t_node *node, int fd)
{
	int		len;

	len = ft_arraylen(node->full_cmd);
	if (len == 1)
	{
		simple_export(&(mini->env), fd);
	}
	else
		return (1);
	return (0);
}

void	execute_builtin(char *s, t_minishell *mini, int i)
{
	g_status = 0;
	if (!ft_strcmp(s, "echo") && mini->nbr_nodes != 1)
		ft_echo(mini->nodes[i], 1);
	else if (!ft_strcmp(s, "echo") && mini->nbr_nodes == 1)
		ft_echo(mini->nodes[i], mini->nodes[i]->outfile);
	else if (!ft_strcmp(s, "cd"))
	  	g_status = ft_cd(mini, mini->nodes[i]);
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
