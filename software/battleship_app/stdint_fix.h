#ifndef _STDINT_FIX_H_
#define _STDINT_FIX_H_

#include <stdint.h>

#ifdef INT8_C
#undef INT8_C
#endif
#ifdef UINT8_C
#undef UINT8_C
#endif
#define INT8_C(n) ((int8_t)(n))
#define UINT8_C(n) ((uint8_t)(n))

#endif
