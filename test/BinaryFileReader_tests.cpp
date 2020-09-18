#include "catch2/catch.hpp"
#include "picky/BinaryFileReader.h"

TEST_CASE( "Constructor", "[BinaryFileReader]" ) {
	auto file = fopen("test.bin", "rb");
	picky::BinaryFileReader<picky::Endian::LITTLE> reader{ file };
}