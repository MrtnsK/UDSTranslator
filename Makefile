# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Makefile   UDSTranslate	                                               #
#                                                                              #
#                                                                              #
#    By: kmartin                                                               #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = UDSTranslate

#INC
INCDIR	= ./inc/

#SRC
SRCDIR	= ./src/
SRC =	utils.c\
		TranslateUDS.c\
		mainParsing.c
SRCWDW =./src/utils.c\
		./src/TranslateUDS.c\
		./src/mainParsing.c

#OBJ
OBJDIR	= ./obj/
OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

FLAGS = -Wall -Werror -Wextra

all : obj $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	gcc $(FLAGS) -I $(INCDIR) -g3 -o $@ -c $<

$(NAME): $(OBJ)
	gcc $(OBJ) -lm -o $(NAME)
	@echo "Everything done."

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f UDSTranslate.exe

wdw:
	gcc $(SRCWDW) -I$(INCDIR) -o UDSTranslate.exe

re: fclean all
