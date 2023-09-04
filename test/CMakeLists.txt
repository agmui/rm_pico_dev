enable_testing()

# Tests need to be added as executables first
add_executable(testlib testlib.cpp)

# I'm using C++17 in the test
# target_compile_features(testlib PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(testlib modern_library GTest::gtest_main)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
# add_test(NAME testlibtest COMMAND testlib) # Command can be a target

include(GoogleTest)
gtest_discover_tests(testlib)