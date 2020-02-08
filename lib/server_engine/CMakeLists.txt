
add_library(server_engine
	src/ServerEngine.cpp
	)

target_include_directories(server_engine
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)

target_link_libraries(server_engine
	PUBLIC
	json_processing
	user
	networking
	room
	)

set_target_properties(server_engine
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 17
	)

install(TARGETS server_engine
	ARCHIVE DESTINATION lib
	)

