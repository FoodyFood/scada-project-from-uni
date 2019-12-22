//This section written by D O'Connor

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// #define WIN32_LEAN_AND_MEAN			// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// Additional Headers
#include <commctrl.h>					// Common Controls header
#include <math.h>						// For round function

// Library Searches						// Adding library-search records to the object file
#pragma comment(lib, "comctl32.lib")	// Common Controls library