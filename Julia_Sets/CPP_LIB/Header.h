#pragma once

#ifdef CPPLIB_EXPORTS
#define CPPLIB_API __declspec(dllexport)
#else
#define CPPLIB_API __declspec(dllimport)
#endif
#include <complex>

extern "C" CPPLIB_API int inSet(std::complex<long double> z, std::complex<long double> c);
