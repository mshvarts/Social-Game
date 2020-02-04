
add_library(user
  src/User.cpp
)

target_include_directories(user
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(user
	PUBLIC
	networking
	)

set_target_properties(user
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS user
  ARCHIVE DESTINATION lib
)

