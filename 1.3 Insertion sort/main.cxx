#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    size_t nums_c;
    fin >> nums_c;

    std::vector<int> nums(nums_c);
    std::vector<size_t> poss(nums_c);

    // read numbers
    for (size_t i = 0; i != nums_c; ++i)
    {
        fin >> nums[i];
    }

    poss[0] = 1;
    for (size_t i = 1; i < std::size(nums); ++i)
    {
        size_t j = i;
        while (j > 0)
        {
            if (nums[j] < nums[j - 1])
            {
                std::swap(nums[j], nums[j - 1]);
                --j;
                continue;
            }
            break;
        }
        poss[i] = j + 1;
    }

    std::for_each(std::cbegin(poss), std::cend(poss), [&fout](auto const &val) {
        fout << val << " ";
    });
    fout << std::endl;

    std::for_each(std::cbegin(nums), std::cend(nums), [&fout](auto const &val) {
        fout << val << " ";
    });
    fout << std::endl;
}