#pragma once

#include <cstdint>
#include <bitset>

using ComponentType = std::uint8_t;
// Used to define the size of arrays later on
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;
