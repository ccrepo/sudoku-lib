#ifndef SUDOKU_SYSTEM_H
#define SUDOKU_SYSTEM_H

#include <string>

#undef SUDOKU_PLATFORM_SUPPORTED

#ifdef _WIN64
  static_assert(0, "platform NOT supported :)");
#elif _WIN32
  static_assert(0, "platform NOT supported :)");
#elif __APPLE__
  #include <TargetConditionals.h>
  #if TARGET_OS_IPHONE && TARGET_OS_SIMULATOR
    static_assert(0, "platform NOT supported :)");
  #elif TARGET_OS_IPHONE && TARGET_OS_MACCATALYST
    static_assert(0, "platform NOT supported :)");
  #elif TARGET_OS_IPHONE
    static_assert(0, "platform NOT supported :)");
  #else
    #define TARGET_OS_OSX 1
		#define SUDOKU_PLATFORM_SUPPORTED
  #endif
#elif __linux
		#define SUDOKU_PLATFORM_SUPPORTED
#elif __unix
  static_assert(0, "platform NOT supported :)");
#elif __posix
  static_assert(0, "platform NOT supported :)");
#else
static_assert(0, "platform NOT supported :)");
#endif

namespace cc {
namespace tools {
namespace sudoku {
namespace system {

#ifdef SUDOKU_PLATFORM_SUPPORTED

std::string getenv(const std::string& name);

constexpr char path_separator = '/';

constexpr const char* str_end(const char *s) {
	return *s ? str_end(s + 1) : s;
}

constexpr bool str_slant(const char *s) {
	return *s == path_separator ? true : (*s ? str_slant(s + 1) : false);
}

constexpr const char* r_slant(const char *s) {
	return *s == path_separator ? (s + 1) : r_slant(s - 1);
}

constexpr const char* basename(const char *s) {
	return str_slant(s) ? r_slant(str_end(s)) : s;
}

#endif // SUDOKU_PLATFORM_SUPPORTED

}
}
}
}

#endif
