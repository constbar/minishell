#include "shell.h"

void	export_all(char **cmd_arr)
{
	int	i;
	int	k;
	int	q;

	if (!cmd_arr[1])
		return ;
	i = 1;
	while (cmd_arr[i])
	{
		if (!(ft_isalpha(cmd_arr[i][0])))
		{
			ft_putstr("export: `");
			ft_putstr(cmd_arr[i]);
			ft_putstr("': not a valid identifier\n");
			g_var.status = 1;
			continue ;
		}
		cmd_export_with_arg(cmd_arr[i], i, k, q);
		i++;
	}
}

static int	len_of_env(void)
{
	int	len_env;

	len_env = 0;
	while (g_var.env[len_env])
		len_env++;
	return (len_env);
}

static void	export_a_helper(char *cmd_arr, int len_env, int k, int fa)
{
	int		i;
	int		j;
	char	**adv_env;

	fa = first_app(cmd_arr);
	if ((k == len_env) || (fa))
	{
		j = 0;
		len_env = len_of_env();
		adv_env = g_var.env;
		g_var.env = safe_malloc((len_env + 2) * sizeof(char *));
		ft_memset(g_var.env, 0, len_env + 2);
		g_var.env[len_env + 1] = NULL;
		i = 0;
		while (adv_env[i])
		{
			g_var.env[i] = adv_env[i];
			i++;
		}
		g_var.env[i] = ft_strdup(cmd_arr);
		g_var.env[i + 1] = NULL;
		if (adv_env)
			free(adv_env);
	}
}

static void	exp_if(int fa, char *cmd_arr, int k)
{
	char	*tmp;

	tmp = safe_malloc(fa + 1);
	ft_memset(tmp, '\0', fa + 1);
	ft_strlcpy(tmp, cmd_arr, fa + 1);
	cmd_unset(tmp, k);
	if (tmp)
		free(tmp);
}

void	cmd_export_with_arg(char *cmd_arr, int fa, int bp, int k)
{
	int		len_env;
	char	*tmp;

	len_env = len_of_env();
	k = 0;
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
		{
			if (fa)
				exp_if(fa, cmd_arr, k);
			break ;
		}
		k++;
	}
	export_a_helper(cmd_arr, len_env, k, fa);
}
