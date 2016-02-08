@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -Wall -Wextra -Wno-unused-parameter -I../include -Dnop_CONFIG_CONFIRMS_COMPILATION_ERRORS=0 -Dnop_FEATURE_ALLOW_IMPLICIT_CONVERSION=0 -o observer_ptr.t.exe observer_ptr.t.cpp && observer_ptr.t.exe
@endlocal
