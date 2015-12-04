# Backtrace
Backtrace class based on <i>Binary File Descriptor</i> library.

<p>First need to install <i>binutils-dev</i>.</p>
```apt-get install binutils-dev```

<p>Compile:</p>
```g++ stack.cpp backtrace.hpp backtrace.cpp parent.hpp parent.cpp -o stack -g -rdynamic -lbfd -ldl -I/usr/include/libxml2/ -lmlpack -std=c++11```

<p>Output should be:</p>
```
 > g++ stack.cpp backtrace.hpp backtrace.cpp parent.hpp parent.cpp -o stack -g -rdynamic -lbfd -ldl -I/usr/include/libxml2/ -lmlpack -std=c++11
 > ./stack
[DEBUG] Compiled with debugging symbols.
[bt]: (1) /home/kirizaki/Projects/backtrace/trash/backtrace.cpp:Backtrace::Backtrace(int):38
[bt]: (2) /home/kirizaki/Projects/backtrace/trash/parent.cpp:Parent::PublicStaticFoo():17
[bt]: (3) /home/kirizaki/Projects/backtrace/trash/parent.cpp:Parent::ProtectedParentFoo():23
[bt]: (4) /home/kirizaki/Projects/backtrace/trash/parent.cpp:Parent::PublicParentFoo():12
[bt]: (5) /home/kirizaki/Projects/backtrace/trash/parent.cpp:Parent::Parent():6
[bt]: (6) /home/kirizaki/Projects/backtrace/trash/stack.cpp:fooA(int):12
[bt]: (7) /home/kirizaki/Projects/backtrace/trash/stack.cpp:fooB(void*):19
[bt]: (8) /home/kirizaki/Projects/backtrace/trash/stack.cpp:fooC(char*):26
[bt]: (9) /home/kirizaki/Projects/backtrace/trash/stack.cpp:main:35
```
