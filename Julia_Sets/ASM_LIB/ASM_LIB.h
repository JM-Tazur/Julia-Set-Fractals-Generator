// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the ASMLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// ASMLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ASMLIB_EXPORTS
#define ASMLIB_API __declspec(dllexport)
#else
#define ASMLIB_API __declspec(dllimport)
#endif

// This class is exported from the dll
class ASMLIB_API CASMLIB {
public:
	CASMLIB(void);
	// TODO: add your methods here.
};

extern ASMLIB_API int nASMLIB;

ASMLIB_API int fnASMLIB(void);
