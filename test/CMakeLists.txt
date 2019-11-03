message("Message from test")
aux_source_directory(. DIR_TEST_SRCS)
add_executable(test ${DIR_TEST_SRCS})
target_link_libraries(test gtest tinyxml pthread)
