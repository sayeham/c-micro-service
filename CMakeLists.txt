cmake_minimum_required(VERSION 3.20)
project(cpp_microservice_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/controllers/HealthController.cpp
    src/controllers/UserController.cpp
    src/services/UserService.cpp
    src/repositories/UserRepository.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
