#pragma once

#include <stdint.h>

extern "C" uint32_t _ntohl(uint32_t _Val);

#define ntohl _ntohl