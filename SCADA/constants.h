//This section written by D O'Connor

//file access constants
#define ReadPerComponent	7		// 6 integers & 1 component type ID
#define CharPerValue		20		// number of characters per integer/ID in file
#define IntToSTR			21		// buffer size for read in characters incl. terminator

//toolbar & statusbar constants
#define HeightOfToolbar		28		// the height of the top toolbar onscreen

//animation constants
#define AnimationSpeed		700		// measured in milliseconds, speed of WM_PAINT messages
#define	DataUpdateSpeed		500		// time between getting updates from the com port