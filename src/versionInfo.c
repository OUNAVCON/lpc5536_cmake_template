#include <stdint.h>
/*
* This entry must be in a C file, if this is in a header file it is not included by the compiler.
*/

#define VERSION_MAJOR 0x0a
#define VERSION_MINOR 0x0b
#define VERSION_BUILD 0x0c

/*
* DO NOT modify anything below this line.
*/
uint32_t __attribute__((section (".BLHeader"))) blHeader[] = {0xFEEDA5A5, 
                                                              0x00000000, 
                                                              0x00000000, 
                                                              0xCCCCCCCC, 
                                                              0xDDDDDDDD, 
                                                              (uint32_t)( ((VERSION_MAJOR & 0xFF) << 16) | ((VERSION_MINOR & 0xFF) << 8) | ((VERSION_BUILD & 0xFF)) )};