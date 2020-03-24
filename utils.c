#include "utils.h"
#include <stdlib.h>


void swap(char array[], int i, int j)
{
	int temp = 0;
	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void reverse(char array[], int length)
{
	int i = 0;
	for (i = 0; i < length / 2; ++i)
		swap(array, i, length - i - 1);
}

int non_negative_dec_to_binary(int n, int bits_count, char *out_buffer)
{
	int i = 0;

	while (i < bits_count)
	{
		out_buffer[i] = n % 2;
		n /= 2;
		++i;
	}
	if (n != 0)
		return FALSE;

	reverse(out_buffer, i);
	return TRUE;
}

int negate_bit(int i)
{
	return (i == 0) ? 1 : 0;
}

void negate_bits_buffer(char buffer[], int length)
{
	int i = 0;
	for (i = 0; i < length; ++i)
		buffer[i] = negate_bit(buffer[i]);
}

void increment_binary_buffer(char buffer[], int bits_count)
{
	int i = 0;
	int carry = 1;
	int local_sum = 0;

	for (i = bits_count - 1; i >= 0; --i)
	{
		local_sum = buffer[i] + carry;
		buffer[i] = local_sum % 2;
		carry = local_sum / 2;
	}
}

int dec_to_binary(int n, int bits_count, char *out_buffer)
{
	if (n >= 0)
		return non_negative_dec_to_binary(n, bits_count, out_buffer);
	else
	{
		n *= -1;
		if (non_negative_dec_to_binary(n, bits_count, out_buffer))
		{
			negate_bits_buffer(out_buffer, bits_count);
			increment_binary_buffer(out_buffer, bits_count);
			return TRUE;
		}		
		else
			return FALSE;
	}
}


