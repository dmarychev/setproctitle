#include "setproctitle/setproctitle.h"
#include <cstring>
#include <cstdlib>

extern char** environ;

struct environ_guard
{
public:
    ~environ_guard()
    {
        if (env_buf) {
            delete[] env_buf;
            env_buf = nullptr;
        }
        if (environ) {
            delete[] environ;
            environ = nullptr;
        }
    }

    char* env_buf;
    char** environ;
};

environ_guard g_new_environ_guard{nullptr, nullptr};

int realloc_environ()
{
    int var_count = 0;
    int env_size = 0;
    {
        char** ep = environ;
        while (*ep) {
            env_size += std::strlen(*ep) + 1;
            ++var_count;
            ++ep;
        }
    }

    char* new_env_buf = new char[env_size];
    std::memcpy((void *)new_env_buf, (void *)*environ, env_size);

    char** new_env = new char*[var_count + 1];
    {
        int var = 0;
        int offset = 0;
        char** ep = environ;
        while (*ep) {
            new_env[var++] = (new_env_buf + offset);
            offset += std::strlen(*ep) + 1;
            ++ep;
        }
    }
    new_env[var_count] = 0;

    // RAII to prevent memory leak
    g_new_environ_guard = environ_guard{new_env_buf, new_env};

    environ = new_env;

    return env_size;
}

void setproctitle(const char* title, int argc, char** argv)
{
    int argv_size = 0;
    for (int i = 0; i < argc; ++i) {
        int len = std::strlen(argv[i]);
        std::memset(argv[i], 0, len);
        argv_size += len;
    }

    int to_be_copied = std::strlen(title);
    if (argv_size <= to_be_copied) {
        int env_size = realloc_environ();
        if (env_size < to_be_copied) {
            to_be_copied = env_size;
        }
    }

    std::strncpy(argv[0], title, to_be_copied);
    *(argv[0] + to_be_copied) = 0;
}
