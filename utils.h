#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <type_traits>
#include <stdint.h>

#define IS_INTEGRAL(T) typename std::enable_if< std::is_integral<T>::value >::type* = 0

namespace Utils{

    enum Endianness { Little = 1, Big = 2 };
    enum BinaryClass { b32 = 1, b64 = 2 };

    template<class T>
    std::bitset<sizeof(T) * 8> IntegerToBitset(T integer, IS_INTEGRAL(T))
    {
        return std::bitset<sizeof(T) * 8>(integer);
    }

    uint16_t readInt16(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness);

    uint32_t readInt32(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness);

    uint64_t readInt64(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness);

    uint64_t readPointer(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness, BinaryClass binaryClass);

}

#endif // UTILS_H
