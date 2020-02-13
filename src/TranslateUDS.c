#include "Translate.h"

void	TranslateUDS(char **id)
{
	char	**trace;

	trace = ft_strsplit(id[1], ' ');
	if (trace)
	{
		switch (trace[0][0])
		{
		case 48:
			printf("  |  \e[93mSingle Frame\e[39m");
			TranslateSID(trace[1]);
			break;
		case 49:
			printf("  |  \e[94mFirst Frame\e[39m");
			TranslateSID(trace[2]);
			break;
		case 50:
			printf("  |  \e[92mConsecutive Frame\e[39m");
			printf("\n");
			break;
		case 51:
			printf("  |  \e[95mFlow Control\e[39m");
			printf("\n");
			break;
		default:
			printf("\n");
			break;
		}
	}
}

void	TranslateSID(char *byte)
{
	//printf("\t%s", byte);
	if (!strcmp(byte, "10"))
	{
		printf("  |  \e[34mRequest:  Diagnostic Session Control\e[39m\n");
	}
	else if (!strcmp(byte, "50"))
	{
		printf("  |  \e[32mResponse: Diagnostic Session Control\e[39m\n");
	}
	else if (!strcmp(byte, "11"))
	{
		printf("  |  \e[34mRequest:  ECU Reset \e[39m\n");
	}
	else if (!strcmp(byte, "52"))
	{
		printf("  |  \e[32mResponse: ECU Reset \e[39m\n");
	}
	else if (!strcmp(byte, "27"))
	{
		printf("  |  \e[34mRequest:  Security Access\e[39m\n");
	}
	else if (!strcmp(byte, "37"))
	{
		printf("  |  \e[32mResponse: Security Access\e[39m\n");
	}
	else if (!strcmp(byte, "28"))
	{
		printf("  |  \e[34mRequest:  Communication Control\e[39m\n");
	}
	else if (!strcmp(byte, "68"))
	{
		printf("  |  \e[32mResponse: Communication Control\e[39m\n");
	}
	else if (!strcmp(byte, "3E"))
	{
		printf("  |  \e[34mRequest:  Tester Present\e[39m\n");
	}
	else if (!strcmp(byte, "7E"))
	{
		printf("  |  \e[32mResponse: Tester Present\e[39m\n");
	}
	else if (!strcmp(byte, "83"))
	{
		printf("  |  \e[34mRequest:  Access Timing Parameters\e[39m\n");
	}
	else if (!strcmp(byte, "C3"))
	{
		printf("  |  \e[32mResponse: Access Timing Parameters\e[39m\n");
	}
	else if (!strcmp(byte, "84"))
	{
		printf("  |  \e[34mRequest:  Secured Data Transmission\e[39m\n");
	}
	else if (!strcmp(byte, "C4"))
	{
		printf("  |  \e[32mResponse: Secured Data Transmission\e[39m\n");
	}
	else if (!strcmp(byte, "85"))
	{
		printf("  |  \e[34mRequest:  Control DTC Settings\e[39m\n");
	}
	else if (!strcmp(byte, "C5"))
	{
		printf("  |  \e[32mResponse: Control DTC Settings \e[39m\n");
	}
	else if (!strcmp(byte, "86"))
	{
		printf("  |  \e[34mRequest:  Response On Event\e[39m\n");
	}
	else if (!strcmp(byte, "C6"))
	{
		printf("  |  \e[32mResponse: Response On Event\e[39m\n");
	}
	else if (!strcmp(byte, "87"))
	{
		printf("  |  \e[34mRequest:  Link Control\e[39m\n");
	}
	else if (!strcmp(byte, "C7"))
	{
		printf("  |  \e[32mResponse: Link Control\e[39m\n");
	}
	else if (!strcmp(byte, "22"))
	{
		printf("  |  \e[34mRequest:  Read Data By Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "62"))
	{
		printf("  |  \e[32mResponse: Read Data By Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "23"))
	{
		printf("  |  \e[34mRequest:  Read Memory By Address\e[39m\n");
	}
	else if (!strcmp(byte, "63"))
	{
		printf("  |  \e[32mResponse: Read Memory By Address\e[39m\n");
	}
	else if (!strcmp(byte, "24"))
	{
		printf("  |  \e[34mRequest:  Read Scaling Data By Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "64"))
	{
		printf("  |  \e[32mResponse: Read Scaling Data By Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "2A"))
	{
		printf("  |  \e[34mRequest:  Read Data By Identifier Periodic\e[39m\n");
	}
	else if (!strcmp(byte, "6A"))
	{
		printf("  |  \e[32mResponse: Read Data By Identifier Periodic\e[39m\n");
	}
	else if (!strcmp(byte, "2C"))
	{
		printf("  |  \e[34mRequest:  Dynamically Define Data Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "6C"))
	{
		printf("  |  \e[32mResponse: Dynamically Define Data Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "2E"))
	{
		printf("  |  \e[34mRequest:  Write Data By Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "6E"))
	{
		printf("  |  \e[32mResponse: Write Data By Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "3D"))
	{
		printf("  |  \e[34mRequest:  Write Memory By Address\e[39m\n");
	}
	else if (!strcmp(byte, "7D"))
	{
		printf("  |  \e[32mResponse: Write Memory By Address\e[39m\n");
	}
	else if (!strcmp(byte, "14"))
	{
		printf("  |  \e[34mRequest:  Clear Diagnostic Information\e[39m\n");
	}
	else if (!strcmp(byte, "54"))
	{
		printf("  |  \e[32mResponse: Clear Diagnostic Information\e[39m\n");
	}
	else if (!strcmp(byte, "19"))
	{
		printf("  |  \e[34mRequest:  Read DTC Information\e[39m\n");
	}
	else if (!strcmp(byte, "59"))
	{
		printf("  |  \e[32mResponse: Read DTC Information\e[39m\n");
	}
	else if (!strcmp(byte, "2F"))
	{
		printf("  |  \e[34mRequest:  Input Output Control By Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "6F"))
	{
		printf("  |  \e[32mResponse: Input Output Control By Identifier\e[39m\n");
	}
	else if (!strcmp(byte, "31"))
	{
		printf("  |  \e[34mRequest:  Routine Control\e[39m\n");
	}
	else if (!strcmp(byte, "71"))
	{
		printf("  |  \e[32mResponse: Routine Control\e[39m\n");
	}
	else if (!strcmp(byte, "34"))
	{
		printf("  |  \e[34mRequest:  Request Download\e[39m\n");
	}
	else if (!strcmp(byte, "74"))
	{
		printf("  |  \e[32mResponse: Request Download\e[39m\n");
	}
	else if (!strcmp(byte, "35"))
	{
		printf("  |  \e[34mRequest:  Request Upload\e[39m\n");
	}
	else if (!strcmp(byte, "75"))
	{
		printf("  |  \e[32mResponse: Request Upload\e[39m\n");
	}
	else if (!strcmp(byte, "36"))
	{
		printf("  |  \e[34mRequest:  Transfer Data\e[39m\n");
	}
	else if (!strcmp(byte, "76"))
	{
		printf("  |  \e[32mResponse: Transfer Data\e[39m\n");
	}
	else if (!strcmp(byte, "37"))
	{
		printf("  |  \e[34mRequest:  Request Transfer Exit\e[39m\n");
	}
	else if (!strcmp(byte, "77"))
	{
		printf("  |  \e[32mResponse: Request Transfer Exit\e[39m\n");
	}
	else if (!strcmp(byte, "38"))
	{
		printf("  |  \e[34mRequest:  Request File Transfer\e[39m\n");
	}
	else if (!strcmp(byte, "78"))
	{
		printf("  |  \e[32mResponse: Request File Transfer\e[39m\n");
	}
	else if (!strcmp(byte, "7F"))
	{
		printf("  |  \e[32m\e[32mResponse: Negative Response\e[39m\n");
	}
	else
		printf("\n");
}
