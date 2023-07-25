#ifndef TOKENIZE_H
#define TOKENIZE_H

#define TRUE (1)
#define FALSE (0)

#define INIT_TOKENIZE_STRINGS_LENGTH (2)

char** tokenize_malloc(const char* str, const char* delim);

#endif /* TOKENIZE_H */
