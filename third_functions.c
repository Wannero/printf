#include "main.h"

/* PRINT POINTER */

/**
 * print_pointer - Prints the value of a pointed variable
 *
 * @types: List a of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of chars printed.
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;

	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/* PRINT NON PRINTABLE */

/**
 * print_non_printable - Prints ascii codes in hexa of non printable character.
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

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int n = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[n] != '\0')
	{
		if (is_printable(str[n]))
			buffer[n + offset] = str[n];
		else
			offset += append_hexa_code(str[n], buffer, n + offset);

		n++;
	}

	buffer[n + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/* PRINT REVERSE */

/**
 * print_reverse - Prints reverse string.
 *
 * @types: Lista of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Numbers of chars printed.
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *st;
	int n, cou = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	st = va_arg(types, char *);

	if (st == NULL)
	{
		UNUSED(precision);

		st = ")Null(";
	}
	for (n = 0; str[n]; n++)
		;

	for (n = n - 1; n >= 0; n--)
	{
		char z = st[n];

		write(1, &z, 1);
		cou++;
	}
	return (cou);
}
/* PRINT A STRING IN ROT13 */

/**
 * print_rot13string - Print a string in rot13.
 *
 * @types: Lista of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Numbers of chars printed.
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char v;
	char *str;
	unsigned int n, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (n = 0; str[n]; n++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[n])
			{
				v = out[j];
				write(1, &v, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			v = str[n];
			write(1, &v, 1);
			count++;
		}
	}
	return (count);
}
