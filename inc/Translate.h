
#ifndef TRANSLATE_H
# define TRANSLATE_H
# define BUFF_SIZE 32
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <ctype.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>

# ifdef _WIN32
# define YELLOW ""
# define LCYAN ""
# define CYAN ""
# define GRAY ""
# define BLUE ""
# define GREEN ""
# define RED ""
# define LMAGENTA ""
# define DEFAULT ""
# endif
# ifdef linux
# define YELLOW "\e[33m"
# define LCYAN "\e[96m"
# define CYAN "\e[36m"
# define GRAY "\e[90m"
# define BLUE "\e[34m"
# define GREEN "\e[32m"
# define RED "\e[31m"
# define LMAGENTA "\e[95m"
# define DEFAULT "\e[39m"
# endif

typedef struct		s_file
{
	int				fd;
	char			*buf;
	struct s_file	*next;
}					t_file;

char			**g_ecu;

void			ft_strdel(char **as);
char			*ft_strnew(size_t size);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *str);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *str);
void			ft_bzero(void *s, size_t n);
t_file			*ft_newfile(int fd);
t_file			*ft_findfd(t_file *file, int fd);
int				ft_clearfile(t_file **file, int fd, int ret);
int				ft_treat(char **buf, char **line);
int				get_next_line(const int fd, char **line);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_strsplit(const char *str, char c);
int				count_word(const char *s, char c);
char			*ft_strtrim(char const *s);
void			ft_freetab(char **tab);
char			*reallocstr(char *str);
void			ft_memdel(void **ap);
void			TranslateUDS(char **id, char **addr);
void			TranslateSID(char *byte, char **trace, char *id);
int				Idvalid(char *id, char **addr);
char			**Loadaddress(void);
void			ft_strclr(char *s);

#endif
