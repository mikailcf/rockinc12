#if defined(__APPLE__) || defined(MACOSX)
#define RES(file_with_double_quotes) resourcePath() + file_with_double_quotes
#else
// Linux code
#endif