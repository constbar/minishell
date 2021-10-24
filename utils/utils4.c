#include "../shell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (size > 0)
	{
		while (*(src + i) && --size)
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_copy(char *dst, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += ('a' - 'A');
	return (c);
}

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(12);
	return (ptr);
}

char	*ft_itoa(int nbr)
{
	int		n;
	int		size;
	char	*str;

	n = nbr / 10;
	size = 1;
	while (n)
	{
		size++;
		n /= 10;
	}
	str = safe_malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	while (size)
	{
		size--;
		str[size] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
