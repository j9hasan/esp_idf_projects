#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper_func.h"

/*copies ssid and pass to wifi_config*/
char *u8cpy(uint8_t *dst, const uint8_t *src)
{
    return (char *)strcpy((char *)dst, (const char *)src);
}

/*no use*/
const char *unsignedCharToString(unsigned char value)
{
    static char buffer[5]; // Adjust the size based on your requirement
    sprintf(buffer, "%u", value);
    return buffer;
}
const char *signedCharToString(signed char value)
{
    static char buffer[5]; // Adjust the size based on your requirement
    sprintf(buffer, "%d", value);
    return buffer;
}
const char *intToString(int value)
{
    static char buffer[12]; // Adjust the size based on your requirement
    sprintf(buffer, "%d", value);
    return buffer;
}
const char *unsignedShortToString(unsigned short value)
{
    static char buffer[12]; // Adjust the size based on your requirement
    sprintf(buffer, "%hu", value);
    return buffer;
}
const char *charArrayToString(char *array, int size)
{
    static char result[5]; // Adjust the size based on your requirement
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (i == 1)
        {
            result[index++] = '.'; // Insert a decimal point after the first digit
        }
        index += snprintf(result + index, sizeof(result) - index, "%d", array[i]);
        // Serial.printf("%02X", array[i]);
    }
    return result;
}

uint32_t toLittleEndian(uint32_t value)
{
    return ((value & 0xFF000000) >> 24) | ((value & 0x00FF0000) >> 8) |
           ((value & 0x0000FF00) << 8) | ((value & 0x000000FF) << 24);
}
int charArrayToInt(const char array[])
{
    int result = 0;
    int i = 0;

    // Assuming the array represents a null-terminated string
    while (array[i] != '\0')
    {
        // Convert character to integer and update the result
        result = result * 10 + (array[i] - '0');
        i++;
    }

    return result;
}
