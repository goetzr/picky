#include "catch2/catch.hpp"
#include "picky/BinaryFileReader.h"
#include "picky/OpenFileError.h"
#include "picky/SeekFileError.h"
#include "picky/ReadFileError.h"

using namespace std;
using namespace picky;

auto GetFileSize(string const& file_path) {
	auto f = fopen(file_path.c_str(), "rb");
	fseek(f, 0, SEEK_END);
	auto file_size = ftell(f);
	fclose(f);
	return file_size;
}

TEST_CASE( "Constructor", "[BinaryFileReader]" ) {
	string const file_path = "test_files/test.bin";

	SECTION( "File does not exist" ) {
		REQUIRE_THROWS_AS( BinaryFileReader<ByteOrder::LITTLE>(file_path), OpenFileError );
	}

	SECTION( "Open file successfully" ) {
		auto const file_size = GetFileSize(file_path);

		BinaryFileReader<ByteOrder::LITTLE> reader(file_path);
		REQUIRE( reader.GetSize() == file_size );
		REQUIRE( reader.GetOffset() == 0 );
	}

}

TEST_CASE( "Seek", "[BinaryFileReader]" ) {
	string const file_path = "test_files/test.bin";
	auto const file_size = GetFileSize(file_path);

	BinaryFileReader<ByteOrder::LITTLE> reader{ file_path };

	SECTION( "Seeking past the end of the file" ) {
		REQUIRE_THROWS_AS( reader.Seek(file_size), SeekFileError );
	}

	SECTION( "Successful seek" ) {
		long const offset = 100;
		reader.Seek(offset);
		REQUIRE( reader.GetOffset() == offset );
	}
}

TEST_CASE( "Read using default endianness", "[BinaryFileReader]" ) {
	string const file_path = "test_files/test.bin";
	BinaryFileReader<ByteOrder::LITTLE> le_reader{ file_path };
	BinaryFileReader<ByteOrder::BIG> be_reader{ file_path };

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
	string const file_path = "test_files/test.bin";
	BinaryFileReader<ByteOrder::LITTLE> le_reader{ file_path };
	BinaryFileReader<ByteOrder::BIG> be_reader{ file_path };

	SECTION( "Read signed 16-bit integer" ) {
		int16_t data;

		le_reader.Seek(7);
		le_reader.Read(data, ByteOrder::BIG);
		REQUIRE( data == -30'567 );

		be_reader.Seek(7);
		be_reader.Read(data, ByteOrder::LITTLE);
		REQUIRE( data == -26'232 );
	}

	SECTION( "Read unsigned 16-bit integer" ) {
		uint16_t data;

		le_reader.Seek(7);
		le_reader.Read(data, ByteOrder::BIG);
		REQUIRE( data == 0x8899 );

		be_reader.Seek(7);
		be_reader.Read(data, ByteOrder::LITTLE);
		REQUIRE( data == 0x9988 );
	}

	SECTION( "Read signed 32-bit integer" ) {
		int32_t data;

		le_reader.Seek(7);
		le_reader.Read(data, ByteOrder::BIG);
		REQUIRE( data == -2'003'195'205 );

		be_reader.Seek(7);
		be_reader.Read(data, ByteOrder::LITTLE);
		REQUIRE( data == -1'146'447'480 );
	}

	SECTION( "Read unsigned 32-bit integer" ) {
		int32_t data;

		le_reader.Seek(7);
		le_reader.Read(data, ByteOrder::BIG);
		REQUIRE( data == 0x8899aabb );

		be_reader.Seek(7);
		be_reader.Read(data, ByteOrder::LITTLE);
		REQUIRE( data == 0xbbaa9988 );
	}

	SECTION( "Read signed 64-bit integer" ) {
		int64_t data;

		le_reader.Seek(7);
		le_reader.Read(data, ByteOrder::BIG);
		REQUIRE( data == -8'603'657'889'541'918'977 );

		be_reader.Seek(7);
		be_reader.Read(data, ByteOrder::LITTLE);
		REQUIRE( data == -4'822'678'189'205'112 );
	}

	SECTION( "Read unsigned 64-bit integer" ) {
		uint64_t data;

		le_reader.Seek(7);
		le_reader.Read(data, ByteOrder::BIG);
		REQUIRE( data == 0x8899aabbccddeeff );

		be_reader.Seek(7);
		be_reader.Read(data, ByteOrder::LITTLE);
		REQUIRE( data == 0xffeeddccbbaa9988 );
	}
}

TEST_CASE( "Read strings", "[BinaryFileReader]" ) {
	string const file_path = "test_files/test.bin";
	BinaryFileReader<ByteOrder::LITTLE> reader{ file_path };

	SECTION( "Read NULL-terminated string" ) {
		string data;
		reader.Seek(0xf);
		reader.Read(data);
		REQUIRE( data == "This is a test string." );
	}

	SECTION( "Read length-specified string" ) {
		string data;
		reader.Seek(0xf);
		reader.Read(data, 14);
		REQUIRE( data == "This is a test" );
	}
}