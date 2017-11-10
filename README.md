# setproctitle

Sets a title for a program. Tools like ps and top will then display the given title instead of dull command line.

Usage is quite straightforward:

```c++
#include <setproctitle/setproctitle.h>

int main(int argc, char** argv)
{
    setproctitle("hello there", argc, argv);
    ... here we go
}
```

The library is statically linked.
