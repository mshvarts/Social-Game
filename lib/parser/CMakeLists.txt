
add_library(parser
	src/GameParser.cpp
)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_include_directories(parser
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(parser nlohmann_json::nlohmann_json game)

set_target_properties(parser
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)


install(TARGETS parser
  ARCHIVE DESTINATION lib
)

