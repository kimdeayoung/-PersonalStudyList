#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tokenize.h"

int main(void)
{
    const char* str = "I like cookies. Do you like cookies? Cookies are good!";
    char** tokens = tokenize_malloc(str, " ?!.");
    char** tt = tokens;

    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "I") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "like") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "cookies") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "Do") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "you") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "like") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "cookies") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "Cookies") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "are") == 0);
    printf("%s\n",  *tt);
    assert(strcmp(*tt++, "good") == 0);
    printf("%s\n",  *tt == NULL ? "NULL DATA" : "Not NULL DATA");
    assert(*tt == NULL);

    tt = tokens;
    while (*tt != NULL) {
        free(*tt++);
    }

    free(tokens);

    return 0;
}
