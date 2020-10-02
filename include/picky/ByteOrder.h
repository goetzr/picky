#pragma once

#include "picky_export.h"

#include <cstdint>

namespace picky {
	
enum class PICKY_EXPORT ByteOrder {
	LITTLE,
	BIG
};

inline std::int16_t SwapByteOrder(std::int16_t data) {
	#ifdef __GNUC__	// GCC
		return static_cast<std::int16_t>(__builtin_bswap16(static_cast<std::uint16_t>(data)));
	#elif _MSC_VER	// MSVC
		return static_cast<std::int16_t>(_byteswap_ushort(static_cast<std::uint16_t>(data)));
	#else
		static_assert("Unsupported compiler.");
	#endif
}

inline std::int32_t SwapByteOrder(std::int32_t data) {
	#ifdef __GNUC__	// GCC
		return static_cast<std::int32_t>(__builtin_bswap32(static_cast<std::uint32_t>(data)));
	#elif _MSC_VER	// MSVC
		return static_cast<std::int32_t>(_byteswap_ulong(static_cast<std::uint32_t>(data)));
	#else
		static_assert("Unsupported compiler.");
	#endif
}

inline std::int64_t SwapByteOrder(std::int64_t data) {
	#ifdef __GNUC__	// GCC
		return static_cast<std::int64_t>(__builtin_bswap64(static_cast<std::uint64_t>(data)));
	#elif _MSC_VER	// MSVC
		return static_cast<std::int64_t>(_byteswap_uint64(static_cast<std::uint64_t>(data)));
	#else
		static_assert("Unsupported compiler.");
	#endif
}

inline std::uint16_t SwapByteOrder(std::uint16_t data) {
	#ifdef __GNUC__	// GCC
		return __builtin_bswap16(data);
	#elif _MSC_VER	// MSVC
		return _byteswap_ushort(data);
	#else
		static_assert("Unsupported compiler.");
	#endif
}

inline std::uint32_t SwapByteOrder(std::uint32_t data) {
	#ifdef __GNUC__	// GCC
		return __builtin_bswap32(data);
	#elif _MSC_VER	// MSVC
		return _byteswap_ulong(data);
	#else
		static_assert("Unsupported compiler.");
	#endif
}

inline std::uint64_t SwapByteOrder(std::uint64_t data) {
	#ifdef __GNUC__	// GCC
		return __builtin_bswap64(data);
	#elif _MSC_VER	// MSVC
		return _byteswap_uint64(data);
	#else
		static_assert("Unsupported compiler.");
	#endif
}

}