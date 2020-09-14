#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    std::vector<int> nums;
    size_t nums_c = 0;

    int item = 0;
    bool item_in_proccess = false;
    bool item_is_negative = false;

    std::ifstream fin("input.txt");
    char buf[4096];
    do
    {
        fin.read(buf, sizeof(buf));
        int k = fin.gcount();

        for (int i = 0; i != k + 1; ++i)
        {
            switch (buf[i])
            {
            case '\n':
            case ' ':
            case '\0':
                if (item_in_proccess)
                {
                    if (nums_c)
                    {
                        if (item_is_negative)
                            item *= -1;
                        nums.push_back(item);
                    }
                    else
                    {
                        nums_c = item;
                        nums.reserve(nums_c);
                    }
                }
                item = 0;
                item_in_proccess = false;
                item_is_negative = false;
                break;
            case '-':
                item_is_negative = true;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                item_in_proccess = true;
                item = 10 * item + buf[i] - '0';
                break;
            default:
                std::cerr << "NaN" << std::endl;
            }
        }
    } while (fin);

    const char out_file_name[] = "output.txt";
    FILE *pFile = fopen(out_file_name, "w");

    // sort
    for (size_t i = 0; i != nums_c - 1; ++i) 
    {
        size_t min = i;
        for (size_t j = i + 1; j != nums_c; ++j) 
        {
            if (nums[j] < nums[min]) 
            {
                min = j;
            }
        }
        if (min != i) 
        {
            std::swap(nums[i], nums[min]);
            fprintf(pFile, "Swap elements at indices %d and %d.\n", i + 1, min + 1);
        }
    }
    fprintf(pFile, "No more swaps needed.\n");
    fclose(pFile);

    return 0;
}