#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <tuple>
#include <chrono>
#include <string>

const bool PART1 = true;
const bool PART2 = true;

using Grid = std::vector<std::string>;
using Position = std::pair<int, int>;
using State = std::tuple<int, int, char>;

void input(const std::string& filename, Grid& grid)
{
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line))
    {
        grid.push_back(line);
    }
}

Position find_guard(const Grid& grid, char& direction)
{
    for (int r = 0; r < grid.size(); ++r)
    {
        for (int c = 0; c < grid[r].size(); ++c)
        {
            if (grid[r][c] == '^' || grid[r][c] == 'v' || grid[r][c] == '<' || grid[r][c] == '>')
            {
                direction = grid[r][c];
                return {r, c};
            }
        }
    }
    return {-1, -1};
}

Position next_position(int row, int col, char direction)
{
    if (direction == '^') 
        return {row - 1, col};
    if (direction == 'v') 
        return {row + 1, col};
    if (direction == '<') 
        return {row, col - 1};
    if (direction == '>') 
        return {row, col + 1};
    return {row, col};
}

char turn_right(char direction)
{
    if (direction == '^') 
        return '>';
    if (direction == '>') 
        return 'v';
    if (direction == 'v') 
        return '<';
    if (direction == '<') 
        return '^';
    return direction;
}

bool is_within_bounds(const Grid& grid, int row, int col)
{
    return row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size();
}

bool simulate_patrol_with_loop_detection(Grid& grid, int guard_row, int guard_col, char direction)
{
    std::set<State> visited_states;

    while (true)
    {
        State current_state = {guard_row, guard_col, direction};
        if (visited_states.count(current_state)) return true;

        visited_states.insert(current_state);
        auto [next_row, next_col] = next_position(guard_row, guard_col, direction);

        if (!is_within_bounds(grid, next_row, next_col)) return false;

        if (grid[next_row][next_col] == '#')
        {
            direction = turn_right(direction);
        }
        else
        {
            guard_row = next_row;
            guard_col = next_col;
        }
    }
}

int count_positions_causing_loops(Grid grid)
{
    char direction;
    Position guard = find_guard(grid, direction);
    int guard_row = guard.first, guard_col = guard.second;

    int valid_positions = 0;
    for (int r = 0; r < grid.size(); ++r)
    {
        for (int c = 0; c < grid[r].size(); ++c)
        {
            if ((r == guard_row && c == guard_col) || grid[r][c] == '#') 
                continue;

            grid[r][c] = '#'; // Temporarily add obstruction
            if (simulate_patrol_with_loop_detection(grid, guard_row, guard_col, direction))
            {
                ++valid_positions;
            }
            grid[r][c] = '.'; // Remove obstruction
        }
    }

    return valid_positions;
}

void part1(const Grid& grid)
{
    char direction;
    Position guard = find_guard(grid, direction);
    int guard_row = guard.first, guard_col = guard.second;

    std::set<Position> visited;
    visited.insert(guard);

    while (true)
    {
        auto [next_row, next_col] = next_position(guard_row, guard_col, direction);

        if (!is_within_bounds(grid, next_row, next_col)) 
            break;

        if (grid[next_row][next_col] == '#')
        {
            direction = turn_right(direction);
        }
        else
        {
            guard_row = next_row;
            guard_col = next_col;
            visited.insert({guard_row, guard_col});
        }
    }

    int distinct_positions = visited.size();
    std::cout << distinct_positions << std::endl;
}

// Takes around 60 seconds with -O3
void part2(const Grid& grid)
{
    int loop_positions = count_positions_causing_loops(grid);
    std::cout << loop_positions << std::endl;
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    Grid lab_map;
    input("input.txt", lab_map);

    if (PART1)
    {
        std::cout << "PART 1:" << std::endl;
        part1(lab_map);
    }

    if (PART2)
    {
        std::cout << "PART 2:" << std::endl;
        part2(lab_map);
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cerr << "Total time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
