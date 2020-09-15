#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

using ull_t = unsigned long long;

void mergesort(ull_t& counter, std::vector<int>& nums, size_t lidx, size_t ridx) {
    if (ridx - lidx < 2) {
        return;
    }

    const size_t pivot = (lidx + ridx) / 2;

    mergesort(counter, nums, lidx, pivot);
    mergesort(counter, nums, pivot, ridx);

    std::vector<int> tmp;
    tmp.reserve(ridx - lidx);

    size_t i = lidx;
    size_t j = pivot;
    while(i != pivot || j != ridx) {
        if(j == ridx || (i != pivot && nums[i] <= nums[j])) {
            tmp.push_back(nums[i++]);
        } else {
            if (i != pivot) counter += pivot - i;
            tmp.push_back(nums[j++]);
        }
    }
    
    std::copy(tmp.cbegin(), tmp.cend(), nums.begin() + lidx);
}

int main(int argc, char **argv)
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    size_t nums_c;
    fin >> nums_c;

    std::vector<int> nums;
    nums.reserve(nums_c);

    std::istream_iterator<int> eos;
    std::istream_iterator<int> iis(fin);
    std::copy(iis, eos, std::back_inserter(nums));

    ull_t counter = 0;
    mergesort(counter, nums, 0, nums_c);
    fout << counter << std::endl;

    return 0;
}