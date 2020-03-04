
add_library(room
	src/Room.cpp
	)

target_include_directories(room 
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)

target_link_libraries(room 
	PUBLIC
	user
	)

set_target_properties(room
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 17
	)

install(TARGETS room
	ARCHIVE DESTINATION lib
	)


# Now link against gtest or gtest_main as needed. Eg
add_executable(roomTest test/RoomTest.cpp)

target_include_directories(roomTest
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)

target_link_libraries(roomTest
	PUBLIC
	user
	gtest_main
	room
	)

add_test(NAME room_test COMMAND roomTest)