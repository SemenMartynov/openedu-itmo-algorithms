#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    std::ifstream fin("input.txt");

    size_t nums_c;
    fin >> nums_c;

    std::vector<int> nums;
    nums.reserve(nums_c);

    std::istream_iterator<int> eos;
    std::istream_iterator<int> iis(fin);
    std::copy(iis, eos, std::back_inserter(nums));

    long long c = 0;
    for (size_t i = 0; i != nums.size(); ++i)
    {
        for (size_t j = i + 1; j < nums.size(); ++j)
        {
            if (nums[i] > nums[j])
            {
                ++c;
            }
        }
    }

    std::ofstream fout("output.txt");
    fout << c << std::endl;

    return 0;
}