#include "picky_export.h"

namespace picky {
	
enum class PICKY_EXPORT Endian {
	LITTLE,
	BIG
};

constexpr auto HostEndianness() {
	short data = 0x1122;
	return (*(char*)(void*)&data) == 0x11 ? Endian::BIG : Endian::LITTLE;
}

}