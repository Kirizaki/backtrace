# stacktrace
<i>external stacktrace</i>

compile: <b>g++ -ldl -g -rdynamic test.cpp stacktrace.cpp stacktrace.hpp parent.cpp parent.hpp -o test</b>

<p>Later implement this functionality in Log::Assert or inside Log class will be better, where Log::Assert gonna call.</p>
