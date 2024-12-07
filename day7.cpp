#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <chrono>
#include <functional>
#include <algorithm>
#include <cmath>

const bool PART1 = true;
const bool PART2 = true;

void input(const std::string &filename, std::vector<std::pair<int64_t, std::vector<int64_t>>> &equations)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string left, right;
        if (std::getline(ss, left, ':'))
        {
            int64_t test_value = std::stoll(left);
            std::vector<int64_t> numbers;
            int64_t num;
            while (ss >> num)
            {
                numbers.push_back(num);
            }
            equations.push_back({test_value, numbers});
        }
    }
}

int64_t concatenate(int64_t a, int64_t b)
{
    int64_t multiplier = 1;    
    while (b >= multiplier)
    {
        multiplier *= 10;
    }

    return a * multiplier + b;
}


bool evaluate_expression(int64_t test_value, const std::vector<int64_t> &numbers, const std::vector<std::function<int64_t(int64_t, int64_t)>> &ops)
{
    int64_t result = numbers[0];
    for (size_t i = 0; i < ops.size(); ++i)
    {
        result = ops[i](result, numbers[i + 1]);
    }
    return result == test_value;
}

bool check_equation(int64_t test_value, const std::vector<int64_t> &numbers, bool include_concat)
{
    std::vector<std::function<int64_t(int64_t, int64_t)>> ops = {
        [](int64_t a, int64_t b) { return a + b; },
        [](int64_t a, int64_t b) { return a * b; }};

    if (include_concat)
    {
        ops.push_back(concatenate);
    }

    size_t n = numbers.size() - 1;
    size_t combinations = std::pow(ops.size(), n);

    for (size_t mask = 0; mask < combinations; ++mask)
    {
        std::vector<std::function<int64_t(int64_t, int64_t)>> chosen_ops;
        size_t temp_mask = mask;
        for (size_t i = 0; i < n; ++i)
        {
            chosen_ops.push_back(ops[temp_mask % ops.size()]);
            temp_mask /= ops.size();
        }

        if (evaluate_expression(test_value, numbers, chosen_ops))
        {
            return true;
        }
    }
    return false;
}

void part1(const std::vector<std::pair<int64_t, std::vector<int64_t>>> &equations)
{
    int64_t total_calibration = 0;
    for (const auto &[test_value, numbers] : equations)
    {
        if (check_equation(test_value, numbers, false))
        {
            total_calibration += test_value;
        }
    }
    std::cout << total_calibration << std::endl;
}

// Takes about 7 seconds with -O3
void part2(const std::vector<std::pair<int64_t, std::vector<int64_t>>> &equations)
{
    int64_t total_calibration = 0;
    for (const auto &[test_value, numbers] : equations)
    {
        if (check_equation(test_value, numbers, true))
        {
            total_calibration += test_value;
        }
    }
    std::cout << total_calibration << std::endl;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::pair<int64_t, std::vector<int64_t>>> equations;
    input("input.txt", equations);

    if (PART1)
    {
        std::cout << "PART 1:" << std::endl;
        part1(equations);
    }

    if (PART2)
    {
        std::cout << "PART 2:" << std::endl;
        part2(equations);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time elapsed: " << elapsed.count() << " seconds\n";

    return 0;
}
