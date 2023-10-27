NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c ft_strdup.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_striteri.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_split.c \
	getnextline_exit.c getnextline_utils_exit.c \

BSRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c \

OBJS = $(SRC:.c=.o)

BOBJS = $(BSRC:.c=.o)

AR = ar rcs
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

ifdef ADD_BONUS
ALLFILES = $(OBJS) $(BOBJS)
else
ALLFILES = $(OBJS)
endif

all: $(NAME)

$(NAME): $(ALLFILES)
	$(AR) $(NAME) $(ALLFILES)

bonus:
	@$(MAKE) ADD_BONUS=1

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all