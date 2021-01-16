#include "pch.h"
#include "Bmps.h"

myBitmap::myBitmap() : pen(NULL), brush(NULL), clr(0), wid(1) {}

myBitmap::~myBitmap()
{
    DeleteObject(pen); DeleteObject(brush);
    DeleteDC(hdc); DeleteObject(bmp);
}

bool myBitmap::create(int w, int h)
{
    BITMAPINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biBitCount = sizeof(DWORD) * 8;
    bi.bmiHeader.biCompression = BI_RGB;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    HDC dc = GetDC(GetConsoleWindow());
    bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &pBits, NULL, 0);
    if (!bmp) return false;
    hdc = CreateCompatibleDC(dc);
    SelectObject(hdc, bmp);
    ReleaseDC(GetConsoleWindow(), dc);
    width = w; height = h;
    return true;
}

void myBitmap::clear(BYTE clr = 0)
{
    memset(pBits, clr, width * height * sizeof(DWORD));
}

void myBitmap::setBrushColor(DWORD bClr)
{
    if (brush) DeleteObject(brush);
    brush = CreateSolidBrush(bClr);
    SelectObject(hdc, brush);
}

void myBitmap::setPenColor(DWORD c)
{
    clr = c; createPen();
}

void myBitmap::setPenWidth(int w)
{
    wid = w; createPen();
}

void myBitmap::saveBitmap(std::string path)
{
    BITMAPFILEHEADER fileheader;
    BITMAPINFO       infoheader;
    BITMAP           bitmap;
    DWORD            wb;
    GetObject(bmp, sizeof(bitmap), &bitmap);
    DWORD* dwpBits = new DWORD[bitmap.bmWidth * bitmap.bmHeight];
    ZeroMemory(dwpBits, bitmap.bmWidth * bitmap.bmHeight * sizeof(DWORD));
    ZeroMemory(&infoheader, sizeof(BITMAPINFO));
    ZeroMemory(&fileheader, sizeof(BITMAPFILEHEADER));
    infoheader.bmiHeader.biBitCount = sizeof(DWORD) * 8;
    infoheader.bmiHeader.biCompression = BI_RGB;
    infoheader.bmiHeader.biPlanes = 1;
    infoheader.bmiHeader.biSize = sizeof(infoheader.bmiHeader);
    infoheader.bmiHeader.biHeight = bitmap.bmHeight;
    infoheader.bmiHeader.biWidth = bitmap.bmWidth;
    infoheader.bmiHeader.biSizeImage = bitmap.bmWidth * bitmap.bmHeight * sizeof(DWORD);
    fileheader.bfType = 0x4D42;
    fileheader.bfOffBits = sizeof(infoheader.bmiHeader) + sizeof(BITMAPFILEHEADER);
    fileheader.bfSize = fileheader.bfOffBits + infoheader.bmiHeader.biSizeImage;
    GetDIBits(hdc, bmp, 0, height, (LPVOID)dwpBits, &infoheader, DIB_RGB_COLORS);
    HANDLE file = CreateFile(s2ws(path).c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(file, &fileheader, sizeof(BITMAPFILEHEADER), &wb, NULL);
    WriteFile(file, &infoheader.bmiHeader, sizeof(infoheader.bmiHeader), &wb, NULL);
    WriteFile(file, dwpBits, bitmap.bmWidth * bitmap.bmHeight * 4, &wb, NULL);
    CloseHandle(file);
    delete[] dwpBits;
}

HDC myBitmap::getDC() const
{
    return hdc;
}

int myBitmap::getWidth() const
{
    return width;
}

int myBitmap::getHeight() const
{
    return height;
}

DWORD* myBitmap::bits() const
{
    return (DWORD*)pBits;
}

std::wstring myBitmap::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void myBitmap::createPen() {
    if (pen) DeleteObject(pen);
    pen = CreatePen(PS_SOLID, wid, clr);
    SelectObject(hdc, pen);
}

//======== JULIA CLASS ========

void julia::draw(fnptr fn, std::complex<long double> k, System::Windows::Forms::ProgressBar^ bar)
{
    bmp.create(BMP_SIZE, BMP_SIZE);
    DWORD* bits = bmp.bits();
    int res, pos;
    std::complex<long double> c, factor(FCT / BMP_SIZE, FCT / BMP_SIZE);

    for (int y = 0; y < BMP_SIZE; y++)
    {
        pos = y * BMP_SIZE;

        c.imag((factor.imag() * y) + -hFCT);

        for (int x = 0; x < BMP_SIZE; x++)
        {
            c.real(factor.real() * x + -hFCT);

            res = fn(c, k);
            
            if (res)
            {
                int n_res = res % 255;
                if (res < (ITERATIONS >> 1)) res = RGB(n_res << 2, n_res << 3, n_res << 4);
                else res = RGB(n_res << 4, n_res << 2, n_res << 5);
            }
            bits[pos++] = res;
        }
        bar->PerformStep();
    }
    bmp.saveBitmap("./julia.bmp");
}
