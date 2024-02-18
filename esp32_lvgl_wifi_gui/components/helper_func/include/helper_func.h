#ifndef __HELPER_FUNC_H__
#define __HELPER_FUNC_H__

char *u8cpy(uint8_t *dst, const uint8_t *src);
unsigned char *convertToUnsignedCharBuffer(const char *charArray, size_t size);
// const char *signedCharToString(signed char value);

const char *unsignedCharToString(unsigned char value);
const char *signedCharToString(signed char value);
const char *intToString(int value);
const char *unsignedShortToString(unsigned short value);
const char *charArrayToString(char *array, int size);

#endif
