#include <string>
#include <iostream>

const bool PART1 = true;
const bool PART2 = true;

void input(std::string &s)
{
    std::string t;
    while (getline(std::cin, t))
    {
        s = s.append(t);
    }
}

std::pair<int,int> get_mult(std::string &s, size_t index)
{
    std::string x, y;

    if (s.substr(index, 4) != "mul(")
    {
        return {-1, -1};
    }

    // Skip mul(
    index += 4;

    // Extract x
    while (index < s.size() && std::isdigit(s[index]))
    {
        x += s[index];
        index++;
    }

    // Ensure it ends with ','
    if (index < s.size() && s[index] == ',')
    {
        index++;
    }
    else
    {
        return {-1, -1};
    }

    // Extract y
    while (index < s.size() && std::isdigit(s[index]))
    {
        y += s[index];
        index++;
    }

    // Ensure it ends with ')'
    int sum = 0;
    if (index < s.size() && s[index] == ')')
    {
        if (!x.empty() && !y.empty())
        {
            int num1 = std::stoi(x);
            int num2 = std::stoi(y);
            return {num1, num2};
        }
    }

    return {-1, -1};
}

void part1(std::string &s)
{
    std::cout << "PART 1:" << std::endl;

    size_t sum = 0;
    for (int i = 0; i < s.size(); i++)
    {
        // Check if substring is of the form "mul(X,Y)"
        std::pair<int,int> p = get_mult(s, i);
        if(p.first != -1 && p.second != -1)
        {
            sum += p.first * p.second;
        }
    }
    std::cout << sum << std::endl;
}

void part2(std::string &s)
{
    std::cout << "PART 2:" << std::endl;

    size_t sum = 0;
    bool mult_enabled = true;
    for (int i = 0; i < s.size(); i++)
    {
        if(s.substr(i, 4) == "do()")
        {
            mult_enabled = true;
        }
        else if(s.substr(i, 7) == "don't()")
        {
            mult_enabled = false;
        }

        if (mult_enabled)
        {
            // Check if substring is of the form "mul(X,Y)"
            std::pair<int,int> p = get_mult(s, i);
            if(p.first != -1 && p.second != -1)
            {
                sum += p.first * p.second;
            }
        }
    }
    std::cout << sum << std::endl;
}

int main()
{
    freopen("input.txt", "r", stdin);

    std::string s;
    input(s);

    if (PART1)
    {
        part1(s);
    }

    if (PART2)
    {
        part2(s);
    }

    return 0;
}
