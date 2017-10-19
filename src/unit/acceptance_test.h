#ifndef __UNIT_ACCEPTANCE_TEST_H__
#define __UNIT_ACCEPTANCE_TEST_H__

#include <unistd.h>
#include <string>
#include <cxxtest/TestSuite.h>
#include "setproctitle/setproctitle.h"

extern char** environ;

class AcceptanceTest : public CxxTest::TestSuite
{

public:
    void testOne()
    {
        const char* argv_0 = "my_program";
        int len_argv_0 = std::strlen(argv_0);
        const char* argv_1 = "my_arg";
        int len_argv_1 = std::strlen(argv_1);
        const char* env_1 = "my_env_1=val_1";
        int len_env_1 = std::strlen(env_1);
        const char* env_2 = "my_env_2=val_2";
        int len_env_2 = std::strlen(env_2);

        char** argv = new char*[2];
        char** env = new char*[3];

        char argv_environ_buf[128] = {0};
        int offset = 0;
        std::memcpy(argv_environ_buf + offset, argv_0, len_argv_0);
        argv[0] = (argv_environ_buf + offset);
        offset += len_argv_0 + 1;
        std::memcpy(argv_environ_buf + offset, argv_1, len_argv_1);
        argv[1] = (argv_environ_buf + offset);
        offset += len_argv_1 + 1;
        std::memcpy(argv_environ_buf + offset, env_1, len_env_1);
        env[0] = (argv_environ_buf + offset);
        offset += len_env_1 + 1;
        std::memcpy(argv_environ_buf + offset, env_2, len_env_2);
        env[1] = (argv_environ_buf + offset);
        offset += len_env_2 + 1;
        env[2] = nullptr;

        char** old_env = environ;
        environ = env;

        TS_ASSERT(std::string(getenv("my_env_1")) == "val_1");
        TS_ASSERT(std::string(getenv("my_env_2")) == "val_2");

        setproctitle("some process title which is longer than argv+environ", 2, argv);

        TS_ASSERT(std::string(getenv("my_env_1")) == "val_1");
        TS_ASSERT(std::string(getenv("my_env_2")) == "val_2");
        TS_ASSERT(std::string("some process title which is lo") == std::string(argv[0]));

        environ = old_env;

        delete[] argv;
        delete[] env;
    }

    void testTwo()
    {
        TS_ASSERT(true);
    }
};

#endif //__UNIT_ACCEPTANCE_TEST_H__
