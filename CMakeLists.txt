cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project("KR")

file(GLOB QUEST_SRC "quest/src/*")

add_executable(quest ${QUEST_SRC})

target_include_directories(quest PRIVATE "quest/include")