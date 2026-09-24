#pragma once

/*
 * ===========================================================================
 * cpp-dump Wrapper (debug.hpp)
 * ===========================================================================
 * 
 * ACTIVATION:
 * This header is completely disabled by default to ensure zero runtime 
 * overhead in production. To activate the debugging macros, you MUST compile 
 * with the DEBUG flag defined:
 *   - CMake (Method 1): target_compile_definitions(your_target PUBLIC DEBUG)
 *   - CMake (Method 2): cmake -DCMAKE_CXX_FLAGS="-DDEBUG" ..
 *   - GCC/Clang:        g++ -DDEBUG main.cpp
 *
 * CORE MACROS:
 *   INIT_DEBUG() : Call once at the start of main() to apply default 
 *                  configurations (e.g., max recursion depth, line width, 
 *                  and enabling filename/line number labels).
 *   DUMP(...)    : The main printing macro. Accepts comma-separated variables 
 *                  of almost any type (vectors, maps, variants, etc.) and 
 *                  prints them with auto-indentation and syntax highlighting.
 *                  Example: DUMP(my_vector, my_map);
 *
 * MANIPULATORS (On-the-fly formatting):
 *   Use the pipe operator (|) and the 'cp::' namespace alias inside DUMP.
 *   - cp::front(n)       : Print only the first 'n' elements of a container.
 *   - cp::both_ends(f, b): Print 'f' elements from the start, 'b' from the end.
 *   - cp::hex()          : Print numbers in hexadecimal format.
 *   Example: DUMP(huge_vector | cp::both_ends(3, 3));
 *
 * CUSTOM TYPES:
 *   To print custom structs/classes without writing std::ostream operators, 
 *   use the export macro in your code:
 *   CPP_DUMP_DEFINE_EXPORT_OBJECT(ClassName, member1, member2)
 * ===========================================================================
 */

#ifdef DEBUG
  #include <cpp-dump.hpp>
  
  namespace cp = cpp_dump;
  
  
  #define DUMP(...) cpp_dump(__VA_ARGS__)

  // default configs for better debug
  #define INIT_DEBUG() \
      do { \
          CPP_DUMP_SET_OPTION(log_label_func, cp::log_label::filename(true)); \
          CPP_DUMP_SET_OPTION(max_line_width, 100); \
          CPP_DUMP_SET_OPTION(max_depth, 4); \
      } while(0)

#else

  // if not debugging, does nothing
  #define DUMP(...) 
  #define INIT_DEBUG() 

#endif
