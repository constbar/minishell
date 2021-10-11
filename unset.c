#include "shell.h"

void	unsent_all(char **cmd_arr)
{
	int	i;

	if (!cmd_arr[1])
	{
		return ;
	}
	i = 1;
	while (cmd_arr[i])
	{
		if ((cmd_arr[i][ft_strlen(cmd_arr[i]) - 1] == '=')
		|| (!(ft_isalpha(cmd_arr[i][0]))))
		{
			ft_putstr("unset: `");
			ft_putstr(cmd_arr[i]);
			ft_putstr("': not a valid identifier\n");
			g_var.status = 1;
			i++;
			continue ;
		}
		cmd_unset(cmd_arr[i], i);
		i++;
	}
}

static void	unset_helper(int num_of_env, int k)
{
	int		j;
	int		i;
	char	**adv_env;

	j = 0;
	i = 0;
	if (k != num_of_env)
	{
		adv_env = g_var.env;
		g_var.env = safe_malloc(num_of_env * sizeof(char *));
		g_var.env[num_of_env - 1] = NULL;
		while (adv_env[j])
		{
			if (j != k)
			{
				g_var.env[i] = adv_env[j];
				i++;
			}
			j++;
		}
		if (adv_env[k])
			free(adv_env[k]);
		if (adv_env)
			free(adv_env);
	}
}

void	cmd_unset(char *cmd_arr, int k)
{
	int	fa;
	int	bp;
	int	num_of_env;

	fa = 0;
	k = 0;
	if (!cmd_arr)
		return ;
	num_of_env = 0;
	while (g_var.env[num_of_env])
		num_of_env++;
	while (g_var.env[k])
	{
		fa = first_app(g_var.env[k]);
		if (fa < 0)
			fa *= -1;
		if (fa)
			bp = fa;
		else
			bp = ft_strlen(cmd_arr);
		if (!(ft_strncmp(cmd_arr, g_var.env[k], bp)))
			break ;
		k++;
	}
	unset_helper(num_of_env, k);
}
