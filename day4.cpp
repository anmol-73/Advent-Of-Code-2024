#include <iostream>
#include <vector>
#include <string>

const bool PART1 = true;
const bool PART2 = true;

void input(std::vector<std::string>& grid)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (!line.empty())
        {
            grid.push_back(line);
        }
    }
}

void part1(const std::vector<std::string>& grid)
{
    const std::string word = "XMAS";
    int rows = grid.size(), cols = grid[0].size();
    int word_len = word.size();
    int count = 0;

    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {1, 1}, {1, -1},
        {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}
    };

    // Checks if the word is found in the given direction
    auto searchFrom = [&](int x, int y, int dx, int dy) -> bool
    {
        for (int i = 0; i < word_len; i++)
        {
            int nx = x + i * dx;
            int ny = y + i * dy;
            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols || grid[nx][ny] != word[i])
            {
                return false;
            }
        }
        return true;
    };

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            // Search in all possible directions
            for (auto [dx, dy] : directions)
            {
                if (searchFrom(x, y, dx, dy))
                {
                    ++count;
                }
            }
        }
    }

    std::cout << count << std::endl;
}

void part2(const std::vector<std::string>& grid)
{
    int rows = grid.size(), cols = grid[0].size();
    int count = 0;

    // Checks if the given pattern is centered at (x, y)
    auto isXMas = [&](int x, int y, const std::string& pattern_left, const std::string& pattern_right) -> bool
    {
        return grid[x - 1][y - 1] == pattern_left[0] && grid[x - 1][y + 1] == pattern_right[0] &&
               grid[x][y] == 'A' &&
               grid[x + 1][y - 1] == pattern_right[1] && grid[x + 1][y + 1] == pattern_left[1];
    };

    for (int x = 1; x < rows - 1; x++)
    {
        for (int y = 1; y < cols - 1; y++)
        {
            if (isXMas(x, y, "MS", "MS") || isXMas(x, y, "MS", "SM") || 
                isXMas(x, y, "SM", "MS") || isXMas(x, y, "SM", "SM"))
            {
                count++;
            }
        }
    }

    std::cout << count << std::endl;
}

int main()
{
    freopen("input.txt", "r", stdin);

    std::vector<std::string> grid;
    input(grid);

    if (PART1)
    {
        std::cout << "PART 1:" << std::endl;
        part1(grid);
    }

    if (PART2)
    {
        std::cout << "PART 2:" << std::endl;
        part2(grid);
    }

    return 0;
}
