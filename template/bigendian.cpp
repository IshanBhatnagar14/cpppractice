#include <boost/predef/other/endian.h>
#include <stdlib.h>
#include <iostream>

int main()
{
#if BOOST_ENDIAN_BIG_BYTE
    std::cout << "Big endian." << std::endl;
#elif BOOST_ENDIAN_LITTLE_BYTE
    std::cout << "Little endian." << std::endl;
#else
    std::cout << "Unknown endian." << std::endl;
#endif
    exit(EXIT_SUCCESS);
}