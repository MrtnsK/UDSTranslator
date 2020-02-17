#include "Translate.h"

char	**Loadaddress(void)
{
	int		j;
	int		e;
	int		tmp;
	int		fd;
	char	*buf;
	char	**tab;
	char	**addr;

	if ((fd = open("id_ecu.csv", O_RDONLY, S_IRUSR)) <= 0)
	{
		printf ("\e[31mid_ecu.csv is missing\n");
		return (NULL);
	}
	if (!(addr = (char**)malloc(sizeof(char*) * 150)))
		return (NULL);
	if (!(g_ecu = (char**)malloc(sizeof(char*) * 150)))
		return (NULL);
	j = 0;
	e = 0;
	while (get_next_line(fd, &buf) != 0)
	{
		if (!ft_strncmp(buf, "EOF", 3))
		{
			ft_strdel(&buf);
			break;
		}
		tmp = count_word(buf, ';');
		tab = ft_strsplit(buf, ';');
		ft_strdel(&buf);
		if (tab && tmp == 2)
		{
			if (!ft_strncmp(tab[0], "0x", 2))
			{
				addr[j++] = ft_strjoin(tab[0] + 2, "x");
				g_ecu[e] = ft_strdup(tab[1]);
				g_ecu[e][ft_strlen(tab[1]) - 1] = '\0';
				e++;
			}
			ft_freetab(tab);
		}
	}
	close(fd);
	addr[j] = NULL;
	return (addr);
}

void	TranslateUDS(char **id, char **addr)
{
	char	**trace;
	int		i;

	i = 0;
	(void)i;
	(void)addr;
	trace = ft_strsplit(id[1], ' ');
	if (trace)
	{
		switch (trace[0][0])
		{
		case 48:
			printf("  |  \e[33mSingle Frame     \e[39m");
			TranslateSID(trace[1], trace, id[1]);
			while (strcmp(addr[i], id[0]))
				i++;
			printf("  |  \e[96m%-20s\e[39m\n", g_ecu[i]);
			break;
		case 49:
			printf("  |  \e[36mFirst Frame     \e[39m ");
			TranslateSID(trace[2], trace, id[1]);
			while (strcmp(addr[i], id[0]))
				i++;
			printf("  |  \e[96m%-20s\e[39m\n", g_ecu[i]);
			break;
		case 50:
			printf("  |  \e[90m%-75s\e[39m", "Consecutive Frame");
			while (strcmp(addr[i], id[0]))
				i++;
			printf("  |  \e[96m%-20s\e[39m\n", g_ecu[i]);
			break;
		case 51:
			printf("  |  \e[90m%-75s\e[39m", "Flow Control");
			while (strcmp(addr[i], id[0]))
				i++;
			printf("  |  \e[96m%-20s\e[39m\n", g_ecu[i]);
			break;
		default:
			printf("\n");
			break;
		}
		ft_freetab(trace);
	}
}

void	TranslateSID(char *byte, char **trace, char *id)
{
	if (!strcmp(byte, "10"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Diagnostic Session Control");
	}
	else if (!strcmp(byte, "50"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Diagnostic Session Control");
	}
	else if (!strcmp(byte, "11"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  ECU Reset");
	}
	else if (!strcmp(byte, "51"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: ECU Reset");
	}
	else if (!strcmp(byte, "27"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Security Access");
	}
	else if (!strcmp(byte, "67"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Security Access");
	}
	else if (!strcmp(byte, "28"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Communication Control");
	}
	else if (!strcmp(byte, "68"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Communication Control");
	}
	else if (!strcmp(byte, "3E"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Tester Present");
	}
	else if (!strcmp(byte, "7E"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Tester Present");
	}
	else if (!strcmp(byte, "83"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Access Timing Parameters");
	}
	else if (!strcmp(byte, "C3"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Access Timing Parameters");
	}
	else if (!strcmp(byte, "84"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Secured Data Transmission");
	}
	else if (!strcmp(byte, "C4"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Secured Data Transmission");
	}
	else if (!strcmp(byte, "85"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Control DTC Settings");
	}
	else if (!strcmp(byte, "C5"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Control DTC Settings");
	}
	else if (!strcmp(byte, "86"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Response On Event");
	}
	else if (!strcmp(byte, "C6"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Response On Event");
	}
	else if (!strcmp(byte, "87"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Link Control");
	}
	else if (!strcmp(byte, "C7"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Link Control");
	}
	else if (!strcmp(byte, "22"))
	{
		printf("  |  \e[34m%s \e[95m%s %-14s\e[39m", "Request:  Read Data By Identifier :", trace[2], trace[3]);
	}
	else if (!strcmp(byte, "62"))
	{
		printf("  |  \e[32m%s \e[95m%s %s\e[33m%s\e[39m", "Response: Read Data By Identifier :", trace[2], trace[3], strlen(id) > 12 ? id + 12 : NULL);
	}
	else if (!strcmp(byte, "23"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Read Memory By Address");
	}
	else if (!strcmp(byte, "63"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Read Memory By Address");
	}
	else if (!strcmp(byte, "24"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Read Scaling Data By Identifier");
	}
	else if (!strcmp(byte, "64"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Read Scaling Data By Identifier");
	}
	else if (!strcmp(byte, "2A"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Read Data By Identifier Periodic");
	}
	else if (!strcmp(byte, "6A"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Read Data By Identifier Periodic");
	}
	else if (!strcmp(byte, "2C"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Dynamically Define Data Identifier");
	}
	else if (!strcmp(byte, "6C"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Dynamically Define Data Identifier");
	}
	else if (!strcmp(byte, "2E"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Write Data By Identifier");
	}
	else if (!strcmp(byte, "6E"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Write Data By Identifier");
	}
	else if (!strcmp(byte, "3D"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Write Memory By Address");
	}
	else if (!strcmp(byte, "7D"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Write Memory By Address");
	}
	else if (!strcmp(byte, "14"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Clear Diagnostic Information");
	}
	else if (!strcmp(byte, "54"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Clear Diagnostic Information");
	}
	else if (!strcmp(byte, "19"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Read DTC Information");
	}
	else if (!strcmp(byte, "59"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Read DTC Information");
	}
	else if (!strcmp(byte, "2F"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Input Output Control By Identifier");
	}
	else if (!strcmp(byte, "6F"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Input Output Control By Identifier");
	}
	else if (!strcmp(byte, "31"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Routine Control");
	}
	else if (!strcmp(byte, "71"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Routine Control");
	}
	else if (!strcmp(byte, "34"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Request Download");
	}
	else if (!strcmp(byte, "74"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Request Download");
	}
	else if (!strcmp(byte, "35"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Request Upload");
	}
	else if (!strcmp(byte, "75"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Request Upload");
	}
	else if (!strcmp(byte, "36"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Transfer Data");
	}
	else if (!strcmp(byte, "76"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Transfer Data");
	}
	else if (!strcmp(byte, "37"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Request Transfer Exit");
	}
	else if (!strcmp(byte, "77"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Request Transfer Exit");
	}
	else if (!strcmp(byte, "38"))
	{
		printf("  |  \e[34m%-53s\e[39m", "Request:  Request File Transfer");
	}
	else if (!strcmp(byte, "78"))
	{
		printf("  |  \e[32m%-53s\e[39m", "Response: Request File Transfer");
	}
	else if (!strcmp(byte, "7F"))
	{
		printf("  |  \e[31m%-53s\e[39m", "Response: Negative Response");
	}
}

