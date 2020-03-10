#include "Translate.h"

char	*GetByte(char **tab)
{
	int		i;
	char	*trace;
	char	*tmp;

	i = 0;
	if (!(trace = (char*)malloc(sizeof(char) * 1)))
		return (NULL);
	trace[0] = '\0';
	while (tab[i])
	{
		if (tab[i + 1] == NULL)
			tab[i][2] = '\0';
		if (ft_strlen(tab[i]) == 2 && isxdigit(tab[i][0]) && isxdigit(tab[i][1]))
		{
			tmp = reallocstr(ft_strjoin(trace, " "));
			ft_strdel(&trace);
			trace = tmp;
			tmp = reallocstr(ft_strjoin(trace, tab[i]));
			ft_strdel(&trace);
			trace = tmp;
		}
		i++;
	}
	if (trace)
		return (trace);
	return (NULL);
}

int		Idvalid(char **id, char **addr)
{
	int		i;
	char	*tmp;

	i = 0;
	if (strlen((*id)) == 10 && (*id)[0] == '0' && (*id)[1] == 'x')
	{
		tmp = ft_strjoin((*id) + 2, "x\0");
		ft_strdel(&(*id));
		(*id) = reallocstr(tmp);
	}
	while (addr[i])
	{
		if (!strcmp((*id), addr[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**GetId(char *str, char **addr)
{
	char	**id;
	char	*tmp;
	char	**tab;
	int		i;
	
	i = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		tmp = ft_strtrim(tab[i]);
		if (Idvalid(&tmp, addr))
		{
			if (!(id = (char**)malloc(sizeof(char *) * 3)))
				return (NULL);
			id[0] = ft_strdup(tmp);
			id [1] = GetByte(tab);
			id [2] = NULL;
			ft_strdel(&tmp);
			ft_freetab(tab);
			return (id);
		}
		ft_strdel(&tmp);
		i++;
	}
	ft_freetab(tab);
	return (NULL);
}

int		main(int ac, char **av)
{
	int		fd;
	char	*file;
	char	**id;
	char	*buf;
	char	**addr;

	file = NULL;
	g_ecu = NULL;
	if (ac != 1 && ac != 2)
	{
		(void)av;
		printf("Usage: ./TranslateUDS.exe [log file]\nOR\n./TranslateUDS.exe\n$> Path to the file to translate? [log file]\n");
		return (1);
	}
	if (!av[1])
	{
		if (!(file = (char*)malloc(sizeof(char) * 150)))
			return (1);
		printf("Path to the file to translate ? (Not case sensitive)\n");
		scanf("%s", file);
	}
	if ((fd = open(file ? file : av[1], O_RDONLY)) <= 0)
		printf ("Erreur open : fd=%d\n", fd);
	else
	{
		if ((addr = Loadaddress()) == NULL)
			return (1);
		while (get_next_line(fd, &buf) != 0)
		{
			id = GetId(buf, addr);
			ft_strdel(&buf);
			if (id)
			{
				printf("%s%s: %-24s%s", LMAGENTA, id[0], id[1], DEFAULT);
				TranslateUDS(id, addr);
				ft_freetab(id);
			}
		}
		if (addr)
			ft_freetab(addr);
		if (g_ecu)
			ft_freetab(g_ecu);
		close(fd);
	}
	if (!av[1])
	{
		ft_strdel(&file);
		printf ("Press a Key then Enter (OR Ctrl C) to quit\n");
		scanf("%s", file);
	}
	return (0);
}
