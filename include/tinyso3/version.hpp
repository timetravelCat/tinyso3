#pragma once

#define TINYSO3_VERSION "0.0.0"

#define TINYSO3_MAJOR_VERSION 0
#define TINYSO3_MINOR_VERSION 0
#define TINYSO3_PATCH_VERSION 0
#define TINYSO3_TWEAK_VERSION "539fcff"

#include "config.hpp"

#define TYPE float

#ifdef CONFIG_FLOATING_POINT_PRECISION_32
#define TYPE float
#elif CONFIG_FLOATING_POINT_PRECISION_64
#define TYPE double
#endif
