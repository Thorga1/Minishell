/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:19:08 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/19 11:56:03 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct v
{
	char	**array;
	int		i;
	int		j;
	int		start;
	int		end;
}	t_split_struct;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_atoi(const char *str);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_lstsize(t_list *lst);
int				ft_strcmp(char *s1, char *s2);
long long		ft_atoll(const char *str);

size_t			ft_strlen(const char *s);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t dsts);

void			*ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memmove(void *s1, const void *s2, size_t len);
void			*ft_memset(void *str, int c, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));

char			*ft_strchr(char const *str, int c);
char			*ft_strdup(const char *src);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strnstr(const char *hay, const char *need, size_t len);
char			*ft_strrchr(const char *str, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_itoa(int n);
char			*ft_straddchar(char *str, char c);
char			*ft_strcpy(char *dest, char *src);

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
				void (*del)(void *));

#endif