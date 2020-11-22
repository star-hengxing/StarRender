@echo off
:: Record: if detach implement and delcare(.cpp .hpp)
g++ test.cpp ../src/*.cpp -std=c++17 -Wall -Werror -O3 -o RayTracing
RayTracing