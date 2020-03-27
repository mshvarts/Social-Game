
add_library(json_processing
	src/Builder.cpp
	src/MessageParser.cpp)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_include_directories(json_processing
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)

target_link_libraries(json_processing
	PUBLIC
	user
	server_engine
	parser
	nlohmann_json::nlohmann_json)

set_target_properties(json_processing
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 17
	)


install(TARGETS json_processing
	ARCHIVE DESTINATION lib
	)
