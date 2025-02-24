#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_putstr(const char *s, int *count)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		write(1, s++, 1);
		(*count)++;
	}
}

static void	ft_putnbr(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		(*count)++;
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10, count);
	c = (n % 10) + '0';
	write(1, &c, 1);
	(*count)++;
}

static void	ft_puthex(unsigned int n, int *count)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		ft_puthex(n / 16, count);
	write(1, &hex[n % 16], 1);
	(*count)++;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(args, char *), &count);
			else if (*format == 'd')
				ft_putnbr(va_arg(args, int), &count);
			else if (*format == 'x')
				ft_puthex(va_arg(args, int), &count);
			else
			{
				write(1, format, 1);
				count++;
			}
		}
		else
		{
			write(1, format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	int ori_ret;
	int ftp_ret;

	printf("sta\n");
	ori_ret = printf("ori: hellow world\n");
	ftp_ret = ft_printf("ftp: hellow world\n");
	printf("ori: %d, ftp: %d\n\n", ori_ret, ftp_ret);

	printf("str\n");
	ori_ret = printf("ori: %s\n", "test text");
	ftp_ret = ft_printf("ftp: %s\n", "test text");
	printf("ori: %d, ftp: %d\n\n", ori_ret, ftp_ret);

	printf("null\n");
	char *null_ptr = NULL;
	ori_ret = printf("ori: %s\n", null_ptr);
	ftp_ret = ft_printf("ftp: %s\n", null_ptr);
	printf("ori: %d, ftp: %d\n\n", ori_ret, ftp_ret);

	printf("nbr\n");
	ori_ret = printf("ori: %d\n", 12345);
	ftp_ret = ft_printf("ftp: %d\n", 12345);
	printf("ori: %d, ftp: %d\n\n", ori_ret, ftp_ret);

	printf("n_nbr\n");
	ori_ret = printf("ori: %d\n", -42);
	ftp_ret = ft_printf("ftp: %d\n", -42);
	printf("ori: %d, ftp: %d\n\n", ori_ret, ftp_ret);

	printf("INT_MAX\n");
	ori_ret = printf("ori: %ld\n", -2147483648);
	ftp_ret = ft_printf("ftp: %d\n", -2147483648);
	printf("ori: %d, ftp: %d\n\n", ori_ret, ftp_ret);

	printf("hex\n");
	ori_ret = printf("ori: %x\n", 255);
	ftp_ret = ft_printf("ftp: %x\n", 255);
	printf("ori: %d, ftp: %d\n\n", ori_ret, ftp_ret);

	return (0);
}