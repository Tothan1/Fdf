/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 10:53:38 by tle-rhun          #+#    #+#             */
/*   Updated: 2025/11/29 12:50:56 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putbase(unsigned long long nbr, char *base)
{
	unsigned long long	lenbase;
	int					len;
	char				mod;

	len = 0;
	lenbase = 16;
	if (nbr >= lenbase)
		len += ft_putbase(nbr / lenbase, base);
	mod = base[nbr % lenbase];
	write(1, &mod, 1);
	len++;
	return (len);
}

int	ft_putadressmemory(void *pointeur)
{
	char				*base;
	unsigned long long	addr;
	int					len;

	base = "0123456789abcdef";
	addr = (unsigned long long) pointeur;
	ft_putstr("0x");
	len = 2 + ft_putbase(addr, base);
	return (len);
}

int	ft_unsignedputnbr_fd(int n)
{
	unsigned int	nb;
	int				len;
	char			mod;

	len = 0;
	nb = (unsigned int)n;
	if (nb > 9)
		len += ft_putnbr(nb / 10);
	mod = (nb % 10) + '0';
	write(1, &mod, 1);
	len++;
	return (len);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
