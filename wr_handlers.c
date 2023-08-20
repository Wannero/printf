#include "main.h"

/**
 * handle_write_char - function that prints a string.
 *
 * @c: char types.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier.
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int n = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pad = '0';

	buffer[n++] = c;
	buffer[n] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (n = 0; n < width - 1; n++)
			buffer[BUFF_SIZE - n - 2] = pad;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - n - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - n - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - function that prints a string.
 *
 * @is_negative: Lista of arguments.
 * @ind: char types.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of chars printed.
 */

int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int leng = BUFF_SIZE - ind - 1;
	char pad = ' ', extra_ = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		extra_ = '-';
	else if (flags & F_PLUS)
		extra_ = '+';
	else if (flags & F_SPACE)
		extra_ = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		leng, pad, extra_));
}

/**
 * write_num - function that write a number using a bufffer.
 *
 * @ind: Index at which the number starts on the buffer.
 * @buffer: Buffer.
 * @flags: Flags.
 * @width: width.
 * @prec: Precision specifier.
 * @length: Number length.
 * @padd: Pading char.
 * @extra_c: Extra char.
 *
 * Return: Number of printed chars.
 */

int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int n, padd_st = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (n = 1; n < width - length + 1; n++)
			buffer[n] = padd;
		buffer[n] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], n - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], n - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_st] = extra_c;
			return (write(1, &buffer[padd_st], n - padd_sta) +
				write(1, &buffer[ind], length - (1 - padd_st)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - function that writes an unsigned number.
 *
 * @is_negative: Number indicating if the num is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Array of chars.
 * @flags: Flags specifiers.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of written chars.
 */

int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{

	int leng = BUFF_SIZE - ind - 1, i = 0;
	char pad = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < leng)
		pad = ' ';

	while (precision > leng)
	{
		buffer[--ind] = '0';
		leng++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > leng)
	{
		for (i = 0; i < width - leng; i++)
			buffer[i] = pad;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], leng) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], leng));
		}
	}

	return (write(1, &buffer[ind], leng));
}

/**
 * write_pointer -  function that Write a memory address
 *
 * @buffer: Arrays of chars.
 * @ind: Index at which the number starts in the buffer.
 * @length: Length of number.
 * @width: Width specifier.
 * @flags: Flags specifier.
 * @padd: Char representing the padding.
 * @extra_c: Char representing extra char.
 * @padd_start: Index at which padding should start.
 *
 * Return: Number of written chars.
 */

int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int n;

	if (width > length)
	{
		for (n = 3; n < width - length + 3; n++)
			buffer[n] = padd;
		buffer[n] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], n - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], n - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], n - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
