add_subdirectory(lib)

add_executable(runAllTests
        ParsingTest.cpp
        )

target_link_libraries(runAllTests
        gmock
        gtest
        gtest_main
        parser
        game
        )

add_test(NAME AllTests COMMAND runAllTests)