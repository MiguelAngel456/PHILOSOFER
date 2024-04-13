#VARIABLES
NAME = philo
CC = gcc -g -Wall -Werror -Wextra 
AR = ar rcs
RM = rm -f
GREEN = `tput setaf 2`
RESET = `tput sgr0`
BLUE = `tput setaf 4`

#ARCHIVOS
FILES = archive_dinner.c\
		archive_think.c\
		archive_times.c\
		clean.c\
		error.c\
		philo_utils.c\
		philosofer.c\
		archive_handle.c\
		set-get.c\


#CREA LOS ARCHIVOS OBJETO
OBJS = $(FILES:.c=.o)

#COMPILA LOS ARCHIVOS
#SE ENCARGA DE QUE AGREGAR A LA LIBRERIA .A LOS OBJETOS
all:	$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) -I ./philosofer.h -c $< -o $@

	@-echo "${GREEN}-----------✅PHILOSOFER COMPILED✅------------${RESET}"

#ENCARGADO DE HACER LA PARTE DE LIMPIEZA TANTO EN ESTA CARPETA COMO EN FT_PRINTF

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "${BLUE}------✅ALL CLEAN✅-------${RESET}"
	

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "${BLUE}------✅ALL CLEAN✅-------${RESET}"

re: fclean all

.PHONY: all clean fclean re