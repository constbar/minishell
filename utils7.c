#include "shell.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	ft_memset(p, '\0', n);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (i < n - 1) && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

void	cpy_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_var.env = safe_malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		g_var.env[i] = ft_strdup(env[i]);
		i++;
	}
	g_var.env[i] = NULL;
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar(*s++);
}
