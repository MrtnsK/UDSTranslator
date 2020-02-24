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

	if ((fd = open("id_ecu.csv", O_RDONLY)) <= 0)
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
			printf("  |  %sSingle Frame     %s", YELLOW, DEFAULT);
			TranslateSID(trace[1], trace, id[1]);
			while (strcmp(addr[i], id[0]))
				i++;
			printf("  |  %s%-20s%s\n", LCYAN, g_ecu[i], DEFAULT);
			break;
		case 49:
			printf("  |  %sFirst Frame     %s ", CYAN, DEFAULT);
			TranslateSID(trace[2], trace, id[1]);
			while (strcmp(addr[i], id[0]))
				i++;
			printf("  |  %s%-20s%s\n", LCYAN, g_ecu[i], DEFAULT);
			break;
		case 50:
			printf("  |  %s%-75s%s", GRAY, "Consecutive Frame", DEFAULT);
			while (strcmp(addr[i], id[0]))
				i++;
			printf("  |  %s%-20s%s\n", LCYAN, g_ecu[i], DEFAULT);
			break;
		case 51:
			printf("  |  %s%-75s%s", GRAY, "Flow Control", DEFAULT);
			while (strcmp(addr[i], id[0]))
				i++;
			printf("  |  %s%-20s%s\n", LCYAN, g_ecu[i], DEFAULT);
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
		printf("  |  %s%-53s%s", BLUE, "Request:  Diagnostic Session Control", DEFAULT);
	}
	else if (!strcmp(byte, "50"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Diagnostic Session Control", DEFAULT);
	}
	else if (!strcmp(byte, "11"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  ECU Reset", DEFAULT);
	}
	else if (!strcmp(byte, "51"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: ECU Reset", DEFAULT);
	}
	else if (!strcmp(byte, "27"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Security Access", DEFAULT);
	}
	else if (!strcmp(byte, "67"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Security Access", DEFAULT);
	}
	else if (!strcmp(byte, "28"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Communication Control", DEFAULT);
	}
	else if (!strcmp(byte, "68"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Communication Control", DEFAULT);
	}
	else if (!strcmp(byte, "3E"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Tester Present", DEFAULT);
	}
	else if (!strcmp(byte, "7E"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Tester Present", DEFAULT);
	}
	else if (!strcmp(byte, "83"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Access Timing Parameters", DEFAULT);
	}
	else if (!strcmp(byte, "C3"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Access Timing Parameters", DEFAULT);
	}
	else if (!strcmp(byte, "84"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Secured Data Transmission", DEFAULT);
	}
	else if (!strcmp(byte, "C4"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Secured Data Transmission", DEFAULT);
	}
	else if (!strcmp(byte, "85"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Control DTC Settings", DEFAULT);
	}
	else if (!strcmp(byte, "C5"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Control DTC Settings", DEFAULT);
	}
	else if (!strcmp(byte, "86"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Response On Event", DEFAULT);
	}
	else if (!strcmp(byte, "C6"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Response On Event", DEFAULT);
	}
	else if (!strcmp(byte, "87"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Link Control", DEFAULT);
	}
	else if (!strcmp(byte, "C7"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Link Control", DEFAULT);
	}
	else if (!strcmp(byte, "22"))
	{
		printf("  |  %s%s %s%s %-14s%s", BLUE, "Request:  Read Data By Identifier :", LMAGENTA, trace[2], trace[3], DEFAULT);
	}
	else if (!strcmp(byte, "62"))
	{
		printf("  |  %s%s %s%s %s%s%s%s", GREEN, "Response: Read Data By Identifier :", LMAGENTA, trace[2], trace[3], YELLOW, strlen(id) > 12 ? id + 12 : NULL, DEFAULT);
	}
	else if (!strcmp(byte, "23"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Read Memory By Address", DEFAULT);
	}
	else if (!strcmp(byte, "63"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Read Memory By Address", DEFAULT);
	}
	else if (!strcmp(byte, "24"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Read Scaling Data By Identifier", DEFAULT);
	}
	else if (!strcmp(byte, "64"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Read Scaling Data By Identifier", DEFAULT);
	}
	else if (!strcmp(byte, "2A"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Read Data By Identifier Periodic", DEFAULT);
	}
	else if (!strcmp(byte, "6A"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Read Data By Identifier Periodic", DEFAULT);
	}
	else if (!strcmp(byte, "2C"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Dynamically Define Data Identifier", DEFAULT);
	}
	else if (!strcmp(byte, "6C"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Dynamically Define Data Identifier", DEFAULT);
	}
	else if (!strcmp(byte, "2E"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Write Data By Identifier", DEFAULT);
	}
	else if (!strcmp(byte, "6E"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Write Data By Identifier", DEFAULT);
	}
	else if (!strcmp(byte, "3D"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Write Memory By Address", DEFAULT);
	}
	else if (!strcmp(byte, "7D"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Write Memory By Address", DEFAULT);
	}
	else if (!strcmp(byte, "14"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Clear Diagnostic Information", DEFAULT);
	}
	else if (!strcmp(byte, "54"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Clear Diagnostic Information", DEFAULT);
	}
	else if (!strcmp(byte, "19"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Read DTC Information", DEFAULT);
	}
	else if (!strcmp(byte, "59"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Read DTC Information", DEFAULT);
	}
	else if (!strcmp(byte, "2F"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Input Output Control By Identifier", DEFAULT);
	}
	else if (!strcmp(byte, "6F"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Input Output Control By Identifier", DEFAULT);
	}
	else if (!strcmp(byte, "31"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Routine Control", DEFAULT);
	}
	else if (!strcmp(byte, "71"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Routine Control", DEFAULT);
	}
	else if (!strcmp(byte, "34"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Request Download", DEFAULT);
	}
	else if (!strcmp(byte, "74"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Request Download", DEFAULT);
	}
	else if (!strcmp(byte, "35"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Request Upload", DEFAULT);
	}
	else if (!strcmp(byte, "75"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Request Upload", DEFAULT);
	}
	else if (!strcmp(byte, "36"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Transfer Data", DEFAULT);
	}
	else if (!strcmp(byte, "76"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Transfer Data", DEFAULT);
	}
	else if (!strcmp(byte, "37"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Request Transfer Exit", DEFAULT);
	}
	else if (!strcmp(byte, "77"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Request Transfer Exit", DEFAULT);
	}
	else if (!strcmp(byte, "38"))
	{
		printf("  |  %s%-53s%s", BLUE, "Request:  Request File Transfer", DEFAULT);
	}
	else if (!strcmp(byte, "78"))
	{
		printf("  |  %s%-53s%s", GREEN, "Response: Request File Transfer", DEFAULT);
	}
	else if (!strcmp(byte, "7F"))
	{
		printf("  |  %s%-53s%s", RED, "Response: Negative Response", DEFAULT);
	}
}

