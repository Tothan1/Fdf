/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:00:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/28 17:18:42 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9
# endif 

# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/* character / classification */
int		ft_isalpha(int character);
int		ft_isdigit(int number);
int		ft_isalnum(int character);
int		ft_isascii(int nb);
int		ft_isprint(int character);
int		ft_toupper(int number);
int		ft_tolower(int number);

/* memory */
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *pointer, int value, size_t count);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_memcmp(const void *str1, const void *str2, size_t n);

/* conversion / misc */
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/* fd output */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);

/* strings */
int		ft_strncmp(const char *s1, const char *s2, int n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*ft_super_strjoin(int size, char **strs, char *sep);
char	*ft_strtrim(char const *s1, const char *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_free_tab(char **tab);
/* bonus-libft*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);

/* printf*/
int		ft_printf(const char *str, ...);
int		ft_putstr(char *s);
int		ft_condition(char *s, int i);
int		ft_arg(char *s, int i, va_list ap);
int		ft_putadressmemory(void *pointeur);
int		ft_putbase(unsigned long nbr, char *base);
int		ft_unsignedputnbr_fd(int n);
int		ft_putnbr(int n);

/* get next line*/
char	*get_next_line(int fd);
char	*ft_strjoin_limits(char *s1, char *s2, int limits);
char	*ft_secondtab_limits(int i, char *newstr, char *s2, int limits);

#endif /* LIBFT_H */
