#include "../shell.h"

void	*ft_memset(void *str, int c, size_t n)
{
	while (n--)
		*(unsigned char *)(str + n) = c;
	return (str);
}

int	ft_putchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (0);
	return (c);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if (*(str + i) == (char)c)
		return ((char *)(str + i));
	return (NULL);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					f;
	unsigned long int	r;

	i = 0;
	r = 0;
	f = 1;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			f = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		i++;
		if (r > 2147483647 && f == 1)
			return (-1);
		if (r > 2147483648 && f == -1)
			return (0);
	}
	return (r * f);
}

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}
