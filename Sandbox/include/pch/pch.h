#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include <math.h>
#include <algorithm>
#include <functional>
#include <array>

#include <iostream>

#define ENABLE_ASSERTS
#ifdef ENABLE_ASSERTS
#define ASSERT(x) {if(x) __debugbreak();}
#else
#define ASSERT(x, ...)
#endif