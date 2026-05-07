file(GLOB SOURCES "src/*.cpp")
add_executable(CelesteGame ${SOURCES})
target_include_directories(CelesteGame PRIVATE "src")