#pragma once
#include <Windows.h>
#include <string>
#include <complex>
#include <omp.h>

const int BMP_SIZE = 600, ITERATIONS = 512;     //rozmiar bitmapy, ilosc iteracji
const long double FCT = 2.85, hFCT = FCT / 2.0; //stale rozmiarowe

typedef int (*fnptr)(std::complex <long double> z, std::complex <long double> c);

class myBitmap
{
private:
    void createPen();
    HBITMAP bmp;
    HDC hdc;
    HPEN pen;
    HBRUSH brush;
    void* pBits;
    int width, height, wid;
    DWORD clr;

public:
    myBitmap();
    ~myBitmap();
    bool create(int w, int h);
    void clear(BYTE clr);
    void setBrushColor(DWORD bClr);
    void setPenColor(DWORD c);
    void setPenWidth(int w);
    void saveBitmap(std::string path);
    HDC getDC() const;
    int getWidth() const;
    int getHeight() const;
    DWORD* bits() const;
    std::wstring s2ws(const std::string& s);
};


class julia
{
private:
    myBitmap bmp;

public:
    void draw(fnptr fn, std::complex<long double> k, System::Windows::Forms::ProgressBar ^bar, int num_threads);
};
