/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 10:53:38 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/28 17:18:12 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long	nb;
	int		len;
	char	mod;

	len = 0;
	nb = n;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		nb = nb * -1;
		write(1, "-", 1);
		len++;
	}
	if (nb > 9)
		len += ft_putnbr(nb / 10);
	mod = (nb % 10) + '0';
	write(1, &mod, 1);
	len++;
	return (len);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_arg(char *s, int i, va_list ap)
{
	void			*ptr;

	if (s[i + 1] == 'c')
		return (ft_putchar((char) va_arg(ap, int)));
	else if (s[i + 1] == 's')
		return (ft_putstr(((char *) va_arg(ap, char *))));
	else if (s[i + 1] == 'p')
	{
		ptr = va_arg(ap, void *);
		if (ptr == NULL)
			return (write(1, "(nil)", 5));
		return (ft_putadressmemory(ptr));
	}
	else if (s[i + 1] == 'd' || s[i + 1] == 'i')
		return (ft_putnbr(((int) va_arg(ap, int))));
	else if (s[i + 1] == 'u')
		return (ft_unsignedputnbr_fd((int) va_arg(ap, int)));
	else if (s[i + 1] == 'x')
		return (ft_putbase((unsigned int) va_arg(ap, int), "0123456789abcdef"));
	else if (s[i + 1] == 'X')
		return (ft_putbase((unsigned int) va_arg(ap, int), "0123456789ABCDEF"));
	else
		return (ft_putchar('%'));
}

int	ft_condition(char *s, int i)
{
	if (s[i] == '%')
	{
		if (s[i + 1] == 'c'
			|| s[i + 1] == 's' || s[i + 1] == 'p'
			|| s[i + 1] == 'd' || s[i + 1] == 'i'
			|| s[i + 1] == 'u' || s[i + 1] == 'x'
			|| s[i + 1] == 'X' || s[i + 1] == '%'
		)
			return (0);
		return (1);
	}
	else
		return (1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	ap;
	char	*s;

	va_start(ap, str);
	s = (char *) str;
	i = 0;
	len = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (!ft_condition(s, i))
			len += ft_arg((char *)str, i, ap);
		if (!ft_condition(s, i))
			i++;
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (len);
}

/* #include <stdio.h>
int main (void)
{
	const char * str ="oui";
	// char *nb ="tout le monde";
	// // char nb ='b';
	long long	nb = -88888888839878787;
	long long *ptr = &nb;

	// printf("taille fonction originale:%d\n", ft_printf(" dd ", str));
	// printf("taille fonction originale:%d\n", printf(" dd", str));
	printf("taille fonction originale:%d\n", printf(" %%%%%%s %%%s ", str));
	printf("taille fonction Tynaël:%d\n", ft_printf(" %%%%%%s %%%s ", str));
	printf("taille fonction originale:%d\n", printf(" %%%%%% %% "));
	printf("taille fonction Tynaël:%d\n", ft_printf(" %%%%%% %% "));
	printf("taille fonction originale:%d\n", printf("%p", ptr));
	printf("taille fonction Tynaël:%d\n", ft_printf("%p", ptr));

	ft_printf(0);
	// return (1);
// 
} */