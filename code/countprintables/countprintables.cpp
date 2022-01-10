#include <fstream>
#include <iostream>
#include <iterator>
#include <limits.h>
#include <vector>

int main()
{
    std::ifstream ifs{"asf-standalone-archive-3.51.0.110.zip", std::ios::binary};
    if (ifs)
    {
        ifs.ignore(std::numeric_limits<std::streamsize>::max());
        auto size = ifs.gcount();
        ifs.clear();
        ifs.seekg(0, std::ios_base::beg);
        std::vector<char> data(size);
        data.insert(data.begin(), std::istream_iterator<char>(ifs), std::istream_iterator<char>());
        unsigned printable = 0;
        unsigned unprintable = 0;
        for (auto c : data)
        {
            if (!std::isprint(c) && !std::isspace(c))
            {
                ++unprintable;
            }
            else
            {
                ++printable;
            }
        }
        std::cout << printable << " " << unprintable << std::endl;
    }
}
