#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void printStackTrace()
{
    void *array[10];
    size_t size;
    size = backtrace(array, 10);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
}
