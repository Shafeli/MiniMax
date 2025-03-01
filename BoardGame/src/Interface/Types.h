// Types.h
#pragma once

#include <bitset>

constexpr size_t kHashBitsetSize = 128;
using GameStateHashType = std::bitset<kHashBitsetSize>;
