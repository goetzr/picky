add_executable(test_picky main.cpp
	BinaryFileReader_tests.cpp
)

target_link_libraries(test_picky picky Catch2::Catch2)

add_test(NAME test_picky COMMAND test_picky)