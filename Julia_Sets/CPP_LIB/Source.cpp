#include "pch.h"
#include "Header.h"


int inSet(std::complex<long double> z, std::complex<long double> c)
{
    long double dist;
    for (int ec = 0; ec < 512; ec++)
    {
        z = z * z; 
        z = z + c;
        dist = (z.imag() * z.imag()) + (z.real() * z.real());
        if (dist > 3) return(ec);
    }
    return 0;
}