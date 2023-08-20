#include "main.h"

/* PRINT CHARACTER */

/**
 * print_char - Prints a charracter
 *
 * @types: List a of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of chars printed
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/* PRINT A STRING */

/**
 * print_string - Prints a string
 *
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, n;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (n = width - length; n > 0; n--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (n = width - length; n > 0; n--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/* PRINT PERCENT SIGN */

/**
 * print_percent - Prints a percent sign.
 *
 * @types: Lista of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of chars printed.
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* PRINT INT */

/**
 * print_int - Print int.
 *
 * @types: Lista of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of chars printed.
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int s = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[s--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[s--] = (num % 10) + '0';
		num /= 10;
	}

	s++;

	return (write_number(is_negative, s, buffer, flags, width, precision, size));
}

/* PRINT BINARY */

/**
 * print_binary - Prints an unsigned number.
 *
 * @types: Lista of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Numbers of char printed.
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int W, m, S, sum;
	unsigned int b[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	W = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	b[0] = W / m;
	for (S = 1; S < 32; S++)
	{
		m /= 2;
		b[S] = (W / m) % 2;
	}
	for (S = 0, sum = 0, count = 0; S < 32; S++)
	{
		sum += b[S];
		if (sum || S == 31)
		{
			char z = '0' + b[S];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
