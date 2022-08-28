#include <cstdio>

namespace dynLib
{
    __declspec(dllexport) void demo()
    {
        printf("dynLib   demo22");
    }

}