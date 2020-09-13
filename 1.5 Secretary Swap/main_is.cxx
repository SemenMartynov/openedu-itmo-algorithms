#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

/*
#include <unistd.h> // lseek, close
#include <sys/mman.h>
#include <fcntl.h> // O_RDONLY, SEEK_END
*/

int main(int argc, char **argv)
{
    std::vector<int> nums;
    size_t nums_c = 0;

    /*
    // Read data
    const char in_file_name[] = "input.txt";
    int fd = open(in_file_name, O_RDONLY);

    off_t file_size = lseek(fd, 0, SEEK_END);
    char *buffer = (char *)mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    bool item_in_proccess = false;
    int item = 0;

    for (char *it = buffer; it != buffer + file_size + 1; ++it)
    {
        if (*it == '\n' || *it == ' ' || *it == '\0')
        {
            if (item_in_proccess)
            {
                if (nums_c)
                {
                    nums[nums_i++] = item;
                }
                else
                {
                    nums_c = item;
                    nums.reserve(nums_c);
                }
            }
            item = 0;
            item_in_proccess = false;
        }
        else if (*it >= '0' && *it <= '9')
        {
            item_in_proccess = true;
            item *= 10;
            item += *it - '0';
        }
        else
        {
            std::cerr << "NaN" << std::endl;
        }
    }

    close(fd);
    munmap(buffer, file_size);
*/

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
                        //                        std::cout << item << std::endl;
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
    /*
    std::for_each(std::cbegin(nums), std::cend(nums), [](const auto& val) {
        std::cout << val << " ";
    });
    std::cout << std::endl;
*/
    const char out_file_name[] = "output.txt";
    FILE *pFile = fopen(out_file_name, "w");
    //setbuf(pFile, buf);

    // sort
    for (size_t i = 1; i < nums_c; ++i)
    {
        if (nums[i] < nums[i - 1])
        {
            size_t j = i;
            for (; j > 0; --j)
            {
                if (nums[j] < nums[j - 1])
                {
                    std::swap(nums[j], nums[j - 1]);
                    fprintf(pFile, "Swap elements at indices %d and %d.\n", j, j + 1);
                    //                    std::cout << "Swap elements at indices " << j << " and " << j + 1 << "." << std::endl;
                    continue;
                }
                break;
            }
            /*            
            std::for_each(std::cbegin(nums), std::cend(nums), [](const auto& val) {
                std::cout << val << " ";
            });
            std::cout << std::endl;
*/
        }
    }
    fprintf(pFile, "No more swaps needed.\n");
    fclose(pFile);

    return 0;
}