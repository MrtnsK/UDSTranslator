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
		if (ft_strlen(tab[i]) == 2)
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

char	**GetId(char *str)
{
	char	**id;
	char	*tmp;
	char	**tab;
	int		i;
	
	i = 0;
	tab = ft_strsplit(str, ' ');
	if (!(id = (char**)malloc(sizeof(char *) * 3)))
		return (NULL);
	while (tab[i])
	{
		tmp = ft_strtrim(tab[i]);
		if (!strcmp(tmp, "14DAF9FCx") || !strcmp(tmp, "14DAFCF9x"))
		{
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
	char	**id;
	char	*buf;

	if (ac != 2)
	{
		printf("Usage: ./TranslateUDS.exe [log file]\n");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY, S_IRUSR)) <= 0)
		printf ("Erreur open : fd=%d ", fd);
	else
	{
		while (get_next_line(fd, &buf) != 0)
		{
			id = GetId(buf);
			if (id)
			{
				printf("\e[95m%s: %-24s\e[39m", id[0], id[1]);
				TranslateUDS(id);
				ft_freetab(id);
			}
		}
	}
	return (0);
}
