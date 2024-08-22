cmake_minimum_required(VERSION 3.5)
project(rest-seervice_test CXX)

add_executable(${PROJECT_NAME} test_main.cc)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# target_link_libraries(${PROJECT_NAME}_test PRIVATE drogon)
#
# and comment out the following lines
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

# aux_source_directory(..libs LIBS_SRC)

target_sources(${PROJECT_NAME}
               PRIVATE
               ../${LIBS_SRC})

ParseAndAddDrogonTests(${PROJECT_NAME})
