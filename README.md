# Backtrace
Backtrace class based on <i>Binary File Descriptor</i> library.

<p>First need to install <i>binutils-dev</i>.</p>
```apt-get install binutils-dev```

<p>Compile:</p>
```g++ stack.cpp parent.cpp -o stack -I/usr/include/libxml2/ -lmlpack -std=c++11```

<p>Output should be:</p>
```
[DEBUG] Compiled with debugging symbols.
[FATAL] Cannot give backtrace because program was compiled without: -g -rdynamic
[FATAL] For a backtrace, recompile with: -g -rdynamic.
[FATAL] FATALITY!
terminate called after throwing an instance of 'std::runtime_error'
  what():  fatal error; see Log::Fatal output
Aborted
```
<p>Compile:</p>
```g++ stack.cpp parent.cpp -o stack -I/usr/include/libxml2/ -lmlpack -std=c++11 -g -rdynamic```

<p>Output should be:</p>
```
[DEBUG] Compiled with debugging symbols.
[FATAL] [bt]: (1) /home/kirizaki/Projects/stacktrace-master/parent.cpp:Parent::PublicStaticFoo():19
[FATAL] [bt]: (2) /home/kirizaki/Projects/stacktrace-master/parent.cpp:Parent::ProtectedParentFoo():27
[FATAL] [bt]: (3) /home/kirizaki/Projects/stacktrace-master/parent.cpp:Parent::PublicParentFoo():14
[FATAL] [bt]: (4) /home/kirizaki/Projects/stacktrace-master/parent.cpp:Parent::Parent():8
[FATAL] [bt]: (5) /home/kirizaki/Projects/stacktrace-master/stack.cpp:short nonTypeFoo<short>(short):31
[FATAL] [bt]: (6) /home/kirizaki/Projects/stacktrace-master/stack.cpp:short tmpFoo<short>(short&):16
[FATAL] [bt]: (7) /home/kirizaki/Projects/stacktrace-master/stack.cpp:inFoo(int&):23
[FATAL] [bt]: (8) /home/kirizaki/Projects/stacktrace-master/stack.cpp:fooA(int):38
[FATAL] [bt]: (9) /home/kirizaki/Projects/stacktrace-master/stack.cpp:fooB(void*):45
[FATAL] [bt]: (10) /home/kirizaki/Projects/stacktrace-master/stack.cpp:fooC(char*):52
[FATAL] [bt]: (11) /home/kirizaki/Projects/stacktrace-master/stack.cpp:main:61
[FATAL] FATALITY!
terminate called after throwing an instance of 'std::runtime_error'
  what():  fatal error; see Log::Fatal output
Aborted
```