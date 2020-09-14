#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

void merge_sort(std::ostream& fout, std::vector<int> &nums, const size_t idx_f, const size_t idx_l)
{
    if (idx_l - idx_f < 2) {
        return;
    }

    const size_t pivot = (idx_f + idx_l) / 2;

    // divide
    merge_sort(fout, nums, idx_f, pivot);
    merge_sort(fout, nums, pivot, idx_l);

    // ...and conqueror
    std::vector<int> buff;
    buff.reserve(idx_l - idx_f);

    // merge
    size_t i = idx_f;
    size_t j = pivot;
    while (i < pivot || j < idx_l)
    {
        if (j == idx_l || (i < pivot && nums[i] <= nums[j]))
        {
            buff.push_back(nums[i++]);
        }
        else
        {
            buff.push_back(nums[j++]);
        }
    }

    std::copy(std::cbegin(buff), std::cend(buff), nums.begin() + idx_f);
    fout << (idx_f + 1) << " " << idx_l << " " << nums[idx_f] << " " << nums[idx_l - 1] << std::endl;
}

int main(int argc, char **argv)
{
    std::ifstream fin("input.txt");

    // Get the quantity of the numbers
    size_t nums_c;
    fin >> nums_c;
    std::vector<int> nums;
    nums.reserve(nums_c);

    // Prepare a pair of iterators to read the data from file
    std::istream_iterator<int> eos;
    std::istream_iterator<int> iit(fin);
    // No loop is necessary, because you can use copy()
    std::copy(iit, eos, std::back_inserter(nums));

    std::ofstream fout("output.txt");

    // Sort
    merge_sort(fout, nums, 0, nums.size());

    std::ostream_iterator<int> out_it(fout, " ");
    std::copy(nums.begin(), nums.end(), out_it);
    return 0;
}