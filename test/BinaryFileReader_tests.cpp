#include "catch2/catch.hpp"
#include "picky/BinaryFileReader.h"

TEST_CASE( "Constructor", "[BinaryFileReader]" ) {
	BinaryFileReader reader("test.bin");
}