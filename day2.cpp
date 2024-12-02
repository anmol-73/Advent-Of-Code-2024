#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>

const bool PART1 = true;
const bool PART2 = true;

void input(std::vector<std::vector<int>> &v)
{
    std::string s;
    while (std::getline(std::cin, s))
    {
        if (s.empty())
            continue;

        std::vector<int> temp;
        std::istringstream ss(s);

        std::string word;
        while (ss >> word)
        {
            temp.push_back(std::stoi(word));
        }

        v.push_back(temp);
    }
}

bool check(std::vector<int> vec)
{
    if (vec.size() <= 1)
        return true;

    if (vec[0] == vec[1])
        return false;

    int inc = (vec[1] - vec[0] > 0) ? 1 : -1;
    bool flag = true;
    for (size_t i = 0; i < vec.size() - 1; i++)
    {
        int diff = (vec[i + 1] - vec[i]) / inc;
        if (diff < 1 || diff > 3)
        {
            flag = false;
            break;
        }
    }

    return flag;
}

void part1(std::vector<std::vector<int>> v)
{
    std::cout << "PART 1:" << std::endl;

    int count = 0;
    for (auto &vec : v)
    {
        count += check(vec);
    }

    std::cout << count << "\n";
}

void part2(std::vector<std::vector<int>> v)
{
    std::cout << "PART 2:" << std::endl;

    int count = 0;
    for (auto &vec : v)
    {
        bool flag = false;
        for (size_t i = 0; i < vec.size(); i++)
        {
            std::vector<int> temp;
            for (size_t j = 0; j < vec.size(); j++)
            {
                if (j != i)
                    temp.push_back(vec[j]);
            }

            flag |= check(temp);
        }
        flag |= check(vec);

        count += flag;
    }

    std::cout << count << "\n";
}

int main()
{
    freopen("input.txt", "r", stdin);

    std::vector<std::vector<int>> v;
    input(v);

    if (PART1)
    {
        part1(v);
    }

    if (PART2)
    {
        part2(v);
    }

    return 0;
}
