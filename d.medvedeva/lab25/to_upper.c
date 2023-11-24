#include <unistd.h>
#include <limits.h>
#include <ctype.h>

#define MAX BC_STRING_MAX

int main() {
    char buffer[MAX];
    ssize_t count = read(0, buffer, MAX);
    int i = 0;
    for (; i < count; ++i)
        buffer[i] = (char)toupper(buffer[i]);
    write(1, buffer, count);
    write(1, "\n", 2);
    return 0;
}
