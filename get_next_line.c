#include "monty.h"

/**
 * ft_substr - gets a part of a string
 * @s: the string in hand
 * @start: where to start cutting
 * @len: the length of the wanted string
 * Return: the new cut string
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

/**
 * read_to_stash - reads to stash
 * @fd: the file descriptor
 * @stash: the stash
 * Return: returns the string read from fd
*/

char	*read_to_stash(int fd, char *stash)
{
	int		r;
	char	*buffer;

	r = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			break;
		buffer[r] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	free(buffer);
	return (stash);
}

/**
 * get_line_from_stash - gets a line from the stash
 * @stash: the stash
 * Return: returns the line
*/

char	*get_line_from_stash(char *stash)
{
	int		i;
	char	*line;

	if (!stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_substr(stash, 0, i + 1);
	return (line);
}

/**
 * get_new_stash - gets the new stash
 * @stash: the original stash
 * Return: returns the new stash
*/

char	*get_new_stash(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i + 1);
	free(stash);
	return (new_stash);
}

/**
 * get_next_line - gets a line by line from the fd
 * @fd: the file descriptor
 * Return: the line read from fd
*/

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line_from_stash(stash);
	stash = get_new_stash(stash);
	return (line);
}
