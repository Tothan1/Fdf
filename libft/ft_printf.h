/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:41:15 by tle-rhun          #+#    #+#             */
/*   Updated: 2025/11/29 13:01:48 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		ft_putstr(char *s);
int		ft_condition(char *s, int i);
int		ft_arg(char *s, int i, va_list ap);
int		ft_putadressmemory(void *pointeur);
int		ft_putbase(unsigned long long nbr, char *base);
int		ft_unsignedputnbr_fd(int n);
int		ft_putnbr(int n);
int		ft_putchar(char c);

#endif /* FT_PRINTF_H */
