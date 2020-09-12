#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

struct citizen_t
{
    long id;
    double account;
};

int main(int argc, char **argv)
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    size_t citezens_c;
    fin >> citezens_c;

    std::vector<citizen_t> citezens(citezens_c);

    // read data
    for (size_t i = 0; i != citezens_c; ++i)
    {
        fin >> citezens[i].account;
        citezens[i].id = static_cast<long>(i) + 1;
    }

    // sort
    for (size_t i = 1; i < citezens_c; ++i)
    {
        for (size_t j = i; j > 0; --j)
        {
            if (citezens[j].account < citezens[j - 1].account)
            {
                std::swap(citezens[j], citezens[j - 1]);
                continue;
            }
            break;
        }
    }

    // show results
    fout << citezens[0].id << " " << citezens[citezens_c / 2].id << " " << citezens[citezens_c - 1].id << std::endl;

    return 0;
}