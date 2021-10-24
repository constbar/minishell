#include "../shell.h"

static void	export_w_helper(int k, int fa)
{
	char	*temp;

	temp = ft_substr(g_var.env[k], 0, fa + 1);
	ft_putstr("declare -x ");
	ft_putstr(temp);
	free(temp);
	ft_putstr("\"");
	temp = ft_substr(g_var.env[k], fa + 1, (ft_strlen(g_var.env[k]) - 1));
	ft_putstr(temp);
	ft_putstr("\"\n");
	free(temp);
}

static void	export_pr_else(int k)
{
	ft_putstr("declare -x ");
	ft_putstr(g_var.env[k]);
	ft_putstr("\n");
}

void	cmd_export_without(void)
{
	int	i;
	int	k;
	int	fa;

	i = 'A';
	while (i <= (int) 'z')
	{
		k = 0;
		while (g_var.env[k])
		{
			if (g_var.env[k][0] == (char)i)
			{
				fa = first_app(g_var.env[k]);
				if (fa > 0)
					export_w_helper(k, fa);
				else
					export_pr_else(k);
			}
			k++;
		}
		i++;
	}
}
