#include "shell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	l;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	l = ft_strlen(s1);
	while (l && ft_strchr(set, s1[l]))
		l--;
	return (ft_substr((char *)s1, 0, l + 1));
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (i < n && s1[i])
	{
		k = 0;
		while (i + k < n && s2[k] && s1[i + k] == s2[k])
			k++;
		if (s2[k] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}

int	first_app(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i * -1);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}
