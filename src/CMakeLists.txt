add_library(picky
            ${picky_SOURCE_DIR}/include/picky/ByteOrder.h
            BinaryFileReader.cpp ${picky_SOURCE_DIR}/include/picky/BinaryFileReader.h
            OpenFileError.cpp ${picky_SOURCE_DIR}/include/picky/OpenFileError.h
            ReadFileError.cpp ${picky_SOURCE_DIR}/include/picky/ReadFileError.h
            SeekFileError.cpp ${picky_SOURCE_DIR}/include/picky/SeekFileError.h)
add_library(picky::picky ALIAS picky)

target_include_directories(picky
  INTERFACE ${picky_SOURCE_DIR}/include
  PRIVATE ${picky_SOURCE_DIR}/include/picky
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}          # Necessary to find generated header files
)

target_link_libraries(picky PRIVATE fmt::fmt)

include(TestBigEndian)
TEST_BIG_ENDIAN(is_host_big_endian)
configure_file(HostByteOrder.h.in HostByteOrder.h)

include(GenerateExportHeader)
generate_export_header(picky)
if (NOT BUILD_SHARED_LIBS)
  # When building as a static library a special preprocessor definition is necessary to prevent
  # the symbol export/import keywords from being added.
  target_compile_definitions(picky PRIVATE
    PICKY_STATIC_DEFINE
  )
endif()