@echo off

SET work_dir=%~dp0

SET c_cflags=/std:c11 /Z7

SET tests=(array base64 blowfish cxx filesystem hash_table ini socket shared_library str)

REM Builds DLL for shared_library test.
cl %work_dir%\shared_library_sample.c /std:c11 /link /DLL /OUT:%work_dir%\shared_library_sample.dll

echo "Running C tests..."

for %%i in %tests% do cl /Z7 /std:c11 /utf-8 %work_dir%\%%i.c /link /OUT:%work_dir%\%%i.exe
for %%i in %tests% do %%i.exe

echo "Finished running C tests."

echo "Running C++ tests..."

for %%i in %tests% do cl /Z7 /std:c++20 /utf-8 /Tp %work_dir%\%%i.c /link /OUT:%work_dir%\%%i_cpp.exe
for %%i in %tests% do %%i_cpp.exe

echo "Finished running C++ tests."