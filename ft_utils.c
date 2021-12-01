#include "ft_pipex.h"

int		ft_str_ncmp(char *str1, char *str2, int n)
{
	while (--n > 0 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str2 - *str1);
}

int		ft_str_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (!str1[i] || !str2[i] || (str1[i] != str2[i]))
			return (0);
		i++;
	}
	return 1;
}

int		ft_pchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_str_ndup(char *str, unsigned int n)
{
	char				*duped;
	unsigned int		i;

	i = 0;
	duped = malloc(sizeof(char) * (n + 1));
	while (i < n)
		duped[i++] = *str++;
	duped[n] = 0;
	return (duped);
}

char	*path_join(char *path, char *bin)
{
	char	*fullPath;
	int		i;
	int		j;

	fullPath = malloc(sizeof(char) * (ft_pchr(path, 0)+ ft_pchr(bin, 0) + 2));
	i = 0;
	j = 0;
	while (path[j])
		fullPath[i++] = path[j++];
	fullPath[i++] = '/';
	j = 0;
	while (bin[j])
		fullPath[i++] = bin[j++];
	fullPath[i] = 0;
	return (fullPath);
}

char	**ft_str_split(char *str, char div)
{
	char	**matrix;
	int		count;
	int		i;
	int		j;

	count = 0;
	j = 0;
	while (str[j])
	{
		if (str[j++] == div)
			count++;
	}
	matrix = malloc(sizeof(char *) * (count + 2));
	matrix[count + 1] = NULL;
	i = 0;
	while (i < count + 1)
	{
		j = 0;
		while (str[j] && str[j] != div)
			j++;
		matrix[i++] = ft_str_ndup(str, j);
		str = str + j + 1;
	}
	return (matrix);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char*	ft_calloc(size_t size, size_t count)
{
	char	*new;
	size_t	i;

	new = malloc(size * (count + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
		new[i++] = '\0';
	new[i] = 0;
	return (new);
}

char*	ft_str_rall(char *buff, char ch)
{
	char	*new;
	int		len;
	int		i;

	if (buff == NULL)
	{
		buff = ft_calloc(sizeof(char), 1);
		buff[0] = ch;
		return buff;
	}
	len = ft_strlen(buff);
	new = ft_calloc(sizeof(char), len + 1);
	// new[len] = ch;
	i = 0;
	while (i < len)
	{
		new[i] = buff[i];
		i++;
	}
	new[i] = ch;
	free(buff);
	return (new);
}

/* Check if substr is contained in str */
int		ft_is_substr(char *str, char* substr)
{
	int	i;
	int	j;

	i = 0;
	while(str[i])
	{
		j = 0;
		while (substr[j] && str[i+j] == substr[j])
		{
				j++;
		}
		if (!substr[j])
			return (1);
		i++;
	}
	return (0);
}
