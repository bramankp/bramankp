g++ -std=c++17 -Wall -Wextra -I. -fPIC -c -o Prebuilt.o Prebuilt.cpp
g++ -rdynamic -shared -o libprebuilt.so Prebuilt.o
