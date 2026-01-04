#define bool _Bool
#define size_t unsigned int

void *malloc(size_t size);

void *Builtin_malloc(int size) {
    return malloc(size);
}

void *calloc(size_t num, size_t size);

//char *strcat(char *dest, const char *src);



size_t strlen(const char *str);

void *memcpy(void *dest, const void *src, size_t n);

int putchar(int ch); //declare here so that we don't need to incorporate a whole library

int printf(const char *fmt, ...);

int sprintf(char *str, const char *fmt, ...);

int scanf(const char *fmt, ...);

char *Builtin_strcat(char *dest, char *src) {
    if (!dest) return src;
    if (!src) return dest;

    size_t len1 = strlen(dest);
    size_t len2 = strlen(src);

    char *ret = malloc(len1 + len2 + 1);

    memcpy(ret, dest, len1);
    memcpy(ret + len1, src, len2);
    ret[len1 + len2] = '\0';
    return ret;
}

void *Builtin_callocArray(size_t len) {
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
            i++;
        } else if (str[i + 1] == '\\') {
            putchar('\\');
            i++;
        } else if (str[i + 1] == '"') {
            putchar('"');
            i++;
        } else {
            putchar('0');
            putchar('0');
            putchar('0');
            putchar('0');
            putchar('0');
            putchar('0');

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

char* getString() {
    char* str = malloc(1024);
    scanf("%s", str);
    return str;
}

int getInt() {
    int val;
    scanf("%d", &val);
    return val;
}

char* toString(int num) {
    char *str = malloc(128);
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
    int ret = 0;
    for (int i = 0; i < strlen(str); i++) {
        ret = ret * 10 + str[i] - '0';
    }
    return ret;
}

int String_ord(char *str, int start) {
    return str[start];
}

int Array_size(int *ptr) {
    return *(ptr - 1);
}