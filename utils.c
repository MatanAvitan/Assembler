#include "utils.h"

/**This file has general purpose, static functions that relevant for the entire project**/

void swap(char array[], int i, int j) {
    int temp = 0;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void reverse(char array[], int length) {
    int i = 0;
    for (i = 0; i < length / 2; ++i)
        swap(array, i, length - i - 1);
}

int non_negative_dec_to_binary(int n, int bits_count, char *out_buffer) {
    int i = 0;

    while (i < bits_count) {
        out_buffer[i] = n % 2;
        n /= 2;
        ++i;
    }
    if (n != 0)
        return FALSE;

    reverse(out_buffer, i);
    return TRUE;
}

int negate_bit(int i) {
    return (i == 0) ? 1 : 0;
}

void negate_bits_buffer(char buffer[], int length) {
    int i = 0;
    for (i = 0; i < length; ++i)
        buffer[i] = negate_bit(buffer[i]);
}

void increment_binary_buffer(char buffer[], int bits_count) {
    int i = 0;
    int carry = 1;
    int local_sum = 0;

    for (i = bits_count - 1; i >= 0; --i) {
        local_sum = buffer[i] + carry;
        buffer[i] = local_sum % 2;
        carry = local_sum / 2;
    }
}

int dec_to_binary(int n, int bits_count, char *out_buffer) {
    if (n >= 0)
        return non_negative_dec_to_binary(n, bits_count, out_buffer);
    else {
        n *= -1;
        if (non_negative_dec_to_binary(n, bits_count, out_buffer)) {
            negate_bits_buffer(out_buffer, bits_count);
            increment_binary_buffer(out_buffer, bits_count);
            return TRUE;
        } else
            return FALSE;
    }
}

int starts_with(const char *pre, const char *str) {
    size_t lenpre = strlen(pre), lenstr = strlen(str);
    return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

char *int_to_string(int num, char *num_as_string) {
    num_as_string[3] = (char) (num % 10) + '0';
    num /= 10;
    num_as_string[2] = (char) (num % 10) + '0';
    num /= 10;
    num_as_string[1] = (char) (num % 10) + '0';
    num /= 10;
    num_as_string[0] = (char) (num % 10) + '0';
    num_as_string[4] = '\t';
    num_as_string[5] = 0;
    return num_as_string;
}

int power(int x, unsigned int y) {
    if (y == 0)
        return 1;
    else if (y % 2 == 0)
        return power(x, y / 2) * power(x, y / 2);
    else
        return x * power(x, y / 2) * power(x, y / 2);
}

char *convert_bin_to_oct(char *bin_command, char *oct_command) {
    int i = 4, j = 0, oct = 0;

    int num = 0;
    for (; j < MAX_BITS; j++) {
        num += (int) ((bin_command[14 - j] - '0') * (power(10, (j % 3))));

        if (j % 3 == 2) {/**We passed three chars**/
            oct += (num % 10) * 1;
            num /= 10;
            oct += (num % 10) * 2;
            num /= 10;
            oct += (num % 10) * 4;
            oct_command[i] = (char) (oct + '0');
            i--;
            num = 0;
            oct = 0;
        }
    }
    oct_command[5] = 0;
    return oct_command;
}


