#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <bitset>
#include <type_traits>

#define IS_INTEGRAL(T) typename std::enable_if< std::is_integral<T>::value >::type* = 0

namespace Utils{

    template<class T>
    std::bitset<sizeof(T) * 8> IntegerToBitset(T integer, IS_INTEGRAL(T))
    {
        return std::bitset<sizeof(T) * 8>(integer);
    }

}

#endif // UTILS_H
