#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

const bool PART1 = true;
const bool PART2 = true;

void input(std::vector<int> &left, std::vector<int> &right)
{
    int l, r;
    while (std::cin >> l >> r)
    {
        left.push_back(l);
        right.push_back(r);
    }
}

void part1(std::vector<int> left, std::vector<int> right)
{
    std::cout << "PART 1:" << std::endl;

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    size_t sum = 0;
    for (int i = 0; i < left.size(); i++)
    {
        sum += abs(left[i] - right[i]);
    }

    std::cout << sum << std::endl;
}

void part2(std::vector<int> left, std::vector<int> right)
{
    std::cout << "PART 2:" << std::endl;

    std::unordered_map<int, int> right_map;
    for (auto elem : right)
    {
        right_map[elem]++;
    }

    size_t sum = 0;
    for (auto elem : left)
    {
        int elem_count = (right_map.find(elem) != right_map.end()) ? right_map[elem] : 0;
        sum += elem * elem_count;
    }
    std::cout << sum << std::endl;
}

int main()
{
    freopen("input.txt", "r", stdin);

    std::vector<int> left, right;
    input(left, right);

    if (PART1)
    {
        part1(left, right);
    }

    if (PART2)
    {
        part2(left, right);
    }

    return 0;
}
