#include "get_next_line.h"
#include <fcntl.h>

char	*reader(int fd, char *str, char *buf)
{
	char	*s;
	int		i;

	i = 1;
	while ((!ft_strchr(str, '\n')) && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		if (i == 0)
		{
			free(buf);
			return (str);
		}
		buf[i] = '\0';
		s = str;
		str = ft_strjoin(str, buf);
		free(s);
	}
	free(buf);
	return (str);
}

char	*current(char *str)
{
	char	*s;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	s[i] = '\0';
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i] = '\n';
	return (s);
}

char	*next(char *str)
{
	char	*s;
	size_t	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
	{
		i++;
	}
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	s = ft_strdup(str + i);
	if (!s)
		return (NULL);
	free(str);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*s;
	char		*buf;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	str = reader(fd, str, buf);
	if (!str)
		return (NULL);
	s = current(str);
	str = next(str);
	return (s);
}
