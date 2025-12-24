#define bool _Bool
#define size_t unsigned int

void *malloc(size_t size);

void *calloc(size_t num, size_t size);

char *strcat(char *dest, const char *src);

char *builtin_strcat(char *dest, const char *src) {
    return strcat(dest, src);
}

size_t strlen(const char *str);

void *memcpy(void *dest, const void *src, size_t n);

int atoi(const char *str);

int putchar(int ch); //declare here so that we don't need to incorporate a whole library

int printf(const char *fmt, ...);

int sprintf(char *str, const char *fmt, ...);

int scanf(const char *fmt, ...);

void *builtin_callocArray(size_t len) {
    int *ptr = calloc(len + 1, sizeof(int));
    ptr[0] = len;
    return ptr + 1;
}

void print(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '\\') {
            putchar(str[i]);
        } else if (str[i + 1] == 'n') {
            putchar('\n');
        } else if (str[i + 1] == '\\') {
            putchar('\\');
        } else if (str[i + 1] == '"') {
            putchar('"');
        }
    }
}

void println(const char *str) {
    print(str);
    putchar('\n');
}

void printInt(int num) {
    printf("%d", num);
}

void printlnInt(int num) {
    printInt(num);
    putchar('\n');
}

void getString() {
    char str[1024];
    scanf("%s", str);
}

void getInt() {
    int val;
    scanf("%d", &val);
}

char* toString(int num) {
    char *str = malloc(16);
    sprintf(str, "%d", num);
    return str;
}

int String_length(char *str) {
    return strlen(str);
}

char *String_substring(char *str, int start, int end) {
    char *ret = malloc(end - start + 1);
    memcpy(ret, str + start, end - start);
    ret[end - start] = '\0';
    return ret;
}

int String_parseInt(char *str) {
    return atoi(str);
}

int String_ord(char *str, int start) {
    return str[start];
}

int Array_size(int *ptr) {
    return *(ptr - 1);
}