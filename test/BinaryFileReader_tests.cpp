#include "catch2/catch.hpp"
#include "picky/BinaryFileReader.h"
#include "picky/SeekError.h"
#include "picky/ReadError.h"

using namespace std;
using namespace picky;

TEST_CASE( "Seek", "[BinaryFileReader]" ) {
	auto file_size = 256L;
	auto file = fopen("test_files/test.bin", "rb");
	REQUIRE( file != nullptr );

	REQUIRE( fseek(file, 0, SEEK_END) == 0 );
	REQUIRE( ftell(file) == file_size );
	REQUIRE( fseek(file, 0, SEEK_SET) == 0 );

	BinaryFileReader<Endian::LITTLE> reader{ file };

	SECTION( "Seeking past the end of the file" ) {
		REQUIRE_THROWS_AS( reader.Seek(file_size), SeekError );
	}

	SECTION( "Successful seek" ) {
		long const offset = 100;
		reader.Seek(offset);
		REQUIRE( ftell(file) == offset );
	}
}

TEST_CASE( "Read using default endianness", "[BinaryFileReader]" ) {
	auto le_file = fopen("test_files/test.bin", "rb");
	REQUIRE( le_file != nullptr );
	BinaryFileReader<Endian::LITTLE> le_reader{ le_file };

	auto be_file = fopen("test_files/test.bin", "rb");
	REQUIRE( be_file != nullptr );
	BinaryFileReader<Endian::BIG> be_reader{ be_file };

	SECTION( "Read signed 8-bit integer" ) {
		int8_t data;

		le_reader.Seek(7);
		le_reader.Read(data);
		REQUIRE( data == -120 );

		be_reader.Seek(7);
		be_reader.Read(data);
		REQUIRE( data == -120 );
	}

	SECTION( "Read unsigned 8-bit integer" ) {
		uint8_t data;

		le_reader.Seek(7);
		le_reader.Read(data);
		REQUIRE( data == 0x88 );

		be_reader.Seek(7);
		be_reader.Read(data);
		REQUIRE( data == 0x88 );
	}

	SECTION( "Read signed 16-bit integer" ) {
		int16_t data;

		le_reader.Seek(7);
		le_reader.Read(data);
		REQUIRE( data == -26'232 );

		be_reader.Seek(7);
		be_reader.Read(data);
		REQUIRE( data == -30'567 );
	}

	SECTION( "Read unsigned 16-bit integer" ) {
		uint16_t data;

		le_reader.Seek(7);
		le_reader.Read(data);
		REQUIRE( data == 0x9988 );

		be_reader.Seek(7);
		be_reader.Read(data);
		REQUIRE( data == 0x8899 );
	}

	SECTION( "Read signed 32-bit integer" ) {
		int32_t data;

		le_reader.Seek(7);
		le_reader.Read(data);
		REQUIRE( data == -1'146'447'480 );

		be_reader.Seek(7);
		be_reader.Read(data);
		REQUIRE( data == -2'003'195'205 );
	}

	SECTION( "Read unsigned 32-bit integer" ) {
		int32_t data;

		le_reader.Seek(7);
		le_reader.Read(data);
		REQUIRE( data == 0xbbaa9988 );

		be_reader.Seek(7);
		be_reader.Read(data);
		REQUIRE( data == 0x8899aabb );
	}

	SECTION( "Read signed 64-bit integer" ) {
		int64_t data;

		le_reader.Seek(7);
		le_reader.Read(data);
		REQUIRE( data == -4'822'678'189'205'112 );

		be_reader.Seek(7);
		be_reader.Read(data);
		REQUIRE( data == -8'603'657'889'541'918'977 );
	}

	SECTION( "Read unsigned 64-bit integer" ) {
		uint64_t data;

		le_reader.Seek(7);
		le_reader.Read(data);
		REQUIRE( data == 0xffeeddccbbaa9988 );

		be_reader.Seek(7);
		be_reader.Read(data);
		REQUIRE( data == 0x8899aabbccddeeff );
	}
}

TEST_CASE( "Read using non-default endianness", "[BinaryFileReader]" ) {
	auto le_file = fopen("test_files/test.bin", "rb");
	REQUIRE( le_file != nullptr );
	BinaryFileReader<Endian::LITTLE> le_reader{ le_file };

	auto be_file = fopen("test_files/test.bin", "rb");
	REQUIRE( be_file != nullptr );
	BinaryFileReader<Endian::BIG> be_reader{ be_file };

	SECTION( "Read signed 16-bit integer" ) {
		int16_t data;

		le_reader.Seek(7);
		le_reader.Read(data, Endian::BIG);
		REQUIRE( data == -30'567 );

		be_reader.Seek(7);
		be_reader.Read(data, Endian::LITTLE);
		REQUIRE( data == -26'232 );
	}

	SECTION( "Read unsigned 16-bit integer" ) {
		uint16_t data;

		le_reader.Seek(7);
		le_reader.Read(data, Endian::BIG);
		REQUIRE( data == 0x8899 );

		be_reader.Seek(7);
		be_reader.Read(data, Endian::LITTLE);
		REQUIRE( data == 0x9988 );
	}

	SECTION( "Read signed 32-bit integer" ) {
		int32_t data;

		le_reader.Seek(7);
		le_reader.Read(data, Endian::BIG);
		REQUIRE( data == -2'003'195'205 );

		be_reader.Seek(7);
		be_reader.Read(data, Endian::LITTLE);
		REQUIRE( data == -1'146'447'480 );
	}

	SECTION( "Read unsigned 32-bit integer" ) {
		int32_t data;

		le_reader.Seek(7);
		le_reader.Read(data, Endian::BIG);
		REQUIRE( data == 0x8899aabb );

		be_reader.Seek(7);
		be_reader.Read(data, Endian::LITTLE);
		REQUIRE( data == 0xbbaa9988 );
	}

	SECTION( "Read signed 64-bit integer" ) {
		int64_t data;

		le_reader.Seek(7);
		le_reader.Read(data, Endian::BIG);
		REQUIRE( data == -8'603'657'889'541'918'977 );

		be_reader.Seek(7);
		be_reader.Read(data, Endian::LITTLE);
		REQUIRE( data == -4'822'678'189'205'112 );
	}

	SECTION( "Read unsigned 64-bit integer" ) {
		uint64_t data;

		le_reader.Seek(7);
		le_reader.Read(data, Endian::BIG);
		REQUIRE( data == 0x8899aabbccddeeff );

		be_reader.Seek(7);
		be_reader.Read(data, Endian::LITTLE);
		REQUIRE( data == 0xffeeddccbbaa9988 );
	}
}

TEST_CASE( "Read strings", "[BinaryFileReader]" ) {
	auto le_file = fopen("test_files/test.bin", "rb");
	REQUIRE( le_file != nullptr );
	BinaryFileReader<Endian::LITTLE> le_reader{ le_file };

	auto be_file = fopen("test_files/test.bin", "rb");
	REQUIRE( be_file != nullptr );
	BinaryFileReader<Endian::BIG> be_reader{ be_file };

	SECTION( "Read NULL-terminated string" ) {
		string le_data;
		le_reader.Seek(0xf);
		le_reader.Read(le_data);
		REQUIRE( le_data == "This is a test string." );

		string be_data;
		be_reader.Seek(0xf);
		be_reader.Read(be_data);
		REQUIRE( be_data == "This is a test string." );
	}

	SECTION( "Read length-specified string" ) {
		string le_data;
		le_reader.Seek(0xf);
		le_reader.Read(le_data, 14);
		REQUIRE( le_data == "This is a test" );

		string be_data;
		be_reader.Seek(0xf);
		be_reader.Read(be_data, 14);
		REQUIRE( be_data == "This is a test" );
	}
}