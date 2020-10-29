#include <str.h>
#include <string.h>


char *str_init(const char *src, String *dest) {
    if (dest == NULL)
        return NULL;
    else if (src == NULL) {
        dest->length = 0;
        dest->str.dynamic_str = NULL;
        return NULL;
    }
    else{
        dest->length = strlen(src);
        if (dest->length > STATIC_STR_DEFAULT_LENGTH) {
            dest->str.dynamic_str = strdup(src);
            return dest->str.dynamic_str;
        }
        else {
            strcpy(dest->str.static_str, src);
            return dest->str.static_str;
        }
    }
}

char *str_get(String *str) {
    if (str == NULL || str->length == 0)
        return NULL;
    else {

        if (str->length > STATIC_STR_DEFAULT_LENGTH)
            return str->str.dynamic_str;
        else
            return str->str.static_str;
    }
}

void str_release(String *str) {
    if (str == NULL)
        return;
    else{
        if (str->length > STATIC_STR_DEFAULT_LENGTH)
            free(str->str.dynamic_str);
        str->length = 0;
    }
}

