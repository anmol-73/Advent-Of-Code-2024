#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <utility>

const bool PART1 = true;
const bool PART2 = true;

void input(const std::string &filename, std::vector<std::pair<int, int>> &rules, std::vector<std::vector<int>> &updates)
{
    std::ifstream file(filename);
    std::string line;
    bool reading_updates = false;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            reading_updates = true;
            continue;
        }

        if (reading_updates)
        {
            std::vector<int> update;
            size_t pos = 0;
            while ((pos = line.find(',')) != std::string::npos)
            {
                update.push_back(std::stoi(line.substr(0, pos)));
                line.erase(0, pos + 1);
            }
            update.push_back(std::stoi(line));
            updates.push_back(update);
        }
        else
        {
            size_t pos = line.find('|');
            int u = std::stoi(line.substr(0, pos));
            int v = std::stoi(line.substr(pos + 1));
            rules.emplace_back(u, v);
        }
    }
}

bool is_order_valid(const std::vector<int> &update, const std::vector<std::pair<int, int>> &rules)
{
    std::unordered_map<int, int> page_index;
    for (size_t i = 0; i < update.size(); ++i)
    {
        page_index[update[i]] = i;
    }

    for (const auto &rule : rules)
    {
        int u = rule.first, v = rule.second;
        if (page_index.count(u) && page_index.count(v))
        {
            if (page_index[u] > page_index[v])
            {
                return false;
            }
        }
    }
    return true;
}

int dependency_count(int page, const std::vector<int> &update, const std::vector<std::pair<int, int>> &rules)
{
    int count = 0;
    for (const auto &rule : rules)
    {
        if (rule.second == page && std::find(update.begin(), update.end(), rule.first) != update.end())
        {
            ++count;
        }
    }
    return count;
}

std::vector<int> reorder_update(const std::vector<int> &update, const std::vector<std::pair<int, int>> &rules)
{
    std::vector<int> sorted_update = update;
    std::sort(sorted_update.begin(), sorted_update.end(), [&](int a, int b)
              { return dependency_count(a, update, rules) < dependency_count(b, update, rules); });
    return sorted_update;
}

int find_middle(const std::vector<int> &update)
{
    return update[update.size() / 2];
}

void part1(const std::vector<std::pair<int, int>> &rules, const std::vector<std::vector<int>> &updates)
{
    int total_middle_sum = 0;

    for (const auto &update : updates)
    {
        if (is_order_valid(update, rules))
        {
            total_middle_sum += find_middle(update);
        }
    }

    std::cout << total_middle_sum << std::endl;
}

void part2(const std::vector<std::pair<int, int>> &rules, const std::vector<std::vector<int>> &updates)
{
    int incorrect_middle_sum = 0;

    for (const auto &update : updates)
    {
        if (!is_order_valid(update, rules))
        {
            std::vector<int> corrected_update = reorder_update(update, rules);
            incorrect_middle_sum += find_middle(corrected_update);
        }
    }

    std::cout << incorrect_middle_sum << std::endl;
}

int main()
{
    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;

    input("input.txt", rules, updates);

    if (PART1)
    {
        std::cout << "PART 1:" << std::endl;
        part1(rules, updates);
    }

    if (PART2)
    {
        std::cout << "PART 2:" << std::endl;
        part2(rules, updates);
    }

    return 0;
}
