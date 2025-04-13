# Libft - 42 Project

## Description
Libft is the first project at 42 school. The aim is to recreate various standard C library functions, as well as additional functions that will be useful throughout the cursus. This library will be used in most of the future 42 projects.

## Functions

### Libc Functions
`ft_isalpha` • `ft_isdigit` • `ft_isalnum` • `ft_isascii` • `ft_isprint` • `ft_strlen` • `ft_memset` • `ft_bzero` • `ft_memcpy` • `ft_memmove` • `ft_strlcpy` • `ft_strlcat` • `ft_toupper` • `ft_tolower` • `ft_strchr` • `ft_strrchr` • `ft_strncmp` • `ft_memchr` • `ft_memcmp` • `ft_strnstr` • `ft_atoi` • `ft_calloc` • `ft_strdup`

### Additional Functions
`ft_substr` • `ft_strjoin` • `ft_strtrim` • `ft_split` • `ft_itoa` • `ft_strmapi` • `ft_striteri` • `ft_putchar_fd` • `ft_putstr_fd` • `ft_putendl_fd` • `ft_putnbr_fd`

### Bonus Functions
`ft_lstnew` • `ft_lstadd_front` • `ft_lstsize` • `ft_lstlast` • `ft_lstadd_back` • `ft_lstdelone` • `ft_lstclear` • `ft_lstiter` • `ft_lstmap`

## Getting Started

### Prerequisites
- GCC compiler
- Make

### Usage
1. Include the header in your source file:
```c
#include "libft.h"
```

### Compilation
1. Compilation:
```bash
make
```

## Cleaning
- Remove object files:
```bash
make clean
```

- Remove object files and library:
```bash
make fclean
```

- Recompile everything:
```bash
make re
```

## Testing
This project doesn't come with unit tests, but you can use external testers:
- [libft-unit-test](https://github.com/alelievr/libft-unit-test)
- [libft-war-machine](https://github.com/ska42/libft-war-machine)
- [Tripouille/libfTester](https://github.com/Tripouille/libftTester)
