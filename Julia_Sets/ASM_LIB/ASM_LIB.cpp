// ASM_LIB.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "ASM_LIB.h"


// This is an example of an exported variable
ASMLIB_API int nASMLIB=0;

// This is an example of an exported function.
ASMLIB_API int fnASMLIB(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CASMLIB::CASMLIB()
{
    return;
}
