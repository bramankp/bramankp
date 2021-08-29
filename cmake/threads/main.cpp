#include <iostream>
#include <thread>

static void DoSomething()
{
    std::cout << "Hello, World!" << "\n";
}

int main()
{
    std::thread thread{DoSomething};
    thread.join();
}
