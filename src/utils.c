#include "Translate.h"

void	ft_strclr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		s[i++] = '\0';
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]
	&& s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}

char	*ft_strnew(size_t size)
{
	char		*str;

	if (!(str = (char *)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	ft_bzero(str, size);
	str[size] = '\0';
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)(str + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dest;

	if (!(dest = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	if (!s)
		return (NULL);
	if (!(str = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	if (!(res = ft_strnew(len1 + len2 + 1)))
		return (NULL);
	i = -1;
	while (i++ < len1)
		res[i] = s1[i];
	i = -1;
	while (i++ < len2)
		res[len1 + i] = s2[i];
	res[len1 + i] = '\0';
	return (res);
}

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = 0;
}

t_file			*ft_newfile(int fd)
{
	t_file		*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	file->next = NULL;
	file->fd = fd;
	file->buf = NULL;
	return (file);
}

t_file			*ft_findfd(t_file *file, int fd)
{
	if (file)
	{
		if (file->fd == fd)
			return (file);
		else if (file->next)
			return (ft_findfd(file->next, fd));
		file->next = ft_newfile(fd);
		return (file->next);
	}
	if (!(file = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	file = ft_newfile(fd);
	return (file);
}

int				ft_clearfile(t_file **file, int fd, int ret)
{
	t_file		*last;
	t_file		*tofree;

	last = *file;
	while (last->fd != fd && last->next && last->next->fd != fd)
		last = last->next;
	tofree = last->fd == fd ? last : last->next;
	if (last->fd == fd)
		*file = tofree->next;
	else
		last->next = tofree->next;
	ft_strdel(&(tofree->buf));
	free(tofree);
	free(*file);
	return (ret);
}

int				ft_treat(char **buf, char **line)
{
	char	*tmp;
	int		l_line;

	l_line = 0;
	while ((*buf)[l_line] && (*buf)[l_line] != '\n')
		l_line++;
	if (((*buf)[l_line]) == '\n')
	{
		*line = ft_strsub(*buf, 0, l_line);
		tmp = *buf;
		*buf = ft_strdup(&(*buf)[l_line + 1]);
		free(tmp);
		!(*buf)[0] ? ft_strdel(buf) : 0;
	}
	else if (!((*buf)[l_line]))
	{
		*line = ft_strdup(*buf);
		ft_strdel(buf);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*file = NULL;
	t_file			*current;
	char			*tmp;
	char			*buffer;
	int				r;

	if (fd < 0 || !line || (!file && !(file = ft_newfile(fd))))
		return (-1);
	current = ft_findfd(file, fd);
	if ((!(current->buf) && !(current->buf = ft_strnew(0)))
		|| !(buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (!(r = 0) && !ft_strchr(current->buf, 10) && !ft_strchr(buffer, 10)
		&& (r = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[r] = 0;
		tmp = current->buf;
		current->buf = ft_strjoin(current->buf, buffer);
		free(tmp);
	}
	free(buffer);
	if (r < 0 || (r == 0 && (!(current->buf) || !(current->buf)[0])))
		return (ft_clearfile(&file, fd, r < 0 ? -1 : 0));
	return (ft_treat(&(current->buf), line));
}

void	ft_memdel(void **ap)
{
	if (!(*ap))
		return ;
	free(*ap);
	*ap = NULL;
}

char	*reallocstr(char *str)
{
	char	*new;
	int		i;

	if (!(new = (char *)malloc(sizeof(char) * ft_strlen(str) + 2)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	ft_memdel((void**)&str);
	return (new);
}

void	ft_freetab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
		ft_strdel(&tab[i++]);
	free(*tab);
	tab = NULL;
}

char	*ft_strtrim(char const *s)
{
	int start;
	int len;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == '\n' || s[start] == '\t' || s[start] == ' ')
		start++;
	len = ft_strlen(s) - 1;
	while (s[len] == '\n' || s[len] == '\t' || s[len] == ' ')
		len--;
	len = len - start + 1;
	len = (len < 0) ? 0 : len;
	return (ft_strsub(s, start, len));
}

int	count_word(const char *s, char c)
{
	int		cmpt;
	int		i;

	cmpt = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			cmpt++;
		while (s[i] != c && s[i])
			i++;
	}
	return (cmpt);
}

static char	**ft_split(char **tab, char c, size_t l, const char *str)
{
	size_t	save;
	size_t	i;
	size_t	n;

	save = 0;
	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		save = i;
		while (str[i] != c && str[i])
		{
			i++;
			l++;
		}
		tab[n] = ft_strsub(str, save, l);
		n++;
		l = 0;
	}
	tab[n] = NULL;
	return (tab);
}

char		**ft_strsplit(const char *str, char c)
{
	int		m;
	size_t	l;
	char	**tab;

	if (str == NULL)
		return (NULL);
	l = 0;
	m = count_word(str, c);
	if (!(tab = malloc(sizeof(char *) * (m + 1))))
		return (NULL);
	return (ft_split(tab, c, l, str));
}
