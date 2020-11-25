// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>
#include <string>
#include <vector>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef wchar_t wchar;

typedef std::string String;
typedef std::wstring WString;

#define TEXT(...) L##__VA_ARGS__

template<class Type, class Alloc = std::allocator<Type>>
using Vector = std::vector<Type, Alloc>;
