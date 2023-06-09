cmake_minimum_required(VERSION 3.20)
project(hashtable  VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -ggdb3 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -no-pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/src/asm")

set(SRC_FILES
    src/hashfunc.cpp
    src/hashtable.cpp
    src/list.cpp
    src/textutils.cpp
    src/asm/rolhash_asm.o
)

set(INCLUDE_FILES
    include/hashfunc.hpp
    include/hashtable.hpp
    include/list.hpp
    include/textutils.hpp
)

add_compile_options(-O3 -mavx2)

add_executable(optimize  src/opt.cpp  ${SRC_FILES} ${INCLUDE_FILES})
add_executable(hashtable src/main.cpp  ${SRC_FILES} ${INCLUDE_FILES})
target_include_directories(optimize PRIVATE include)
target_include_directories(hashtable PRIVATE include)
target_link_libraries(optimize PRIVATE -no-pie)  # добавляем флаг линковщику
target_link_libraries(hashtable PRIVATE -no-pie)  # добавляем флаг линковщику



