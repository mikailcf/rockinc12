#if defined(__APPLE__) || defined(MACOSX)
#define RES(file_with_double_quotes) resourcePath() + file_with_double_quotes
#else
#define RES(file_with_double_quotes) (std::string("./res/") + file_with_double_quotes)
#endif
