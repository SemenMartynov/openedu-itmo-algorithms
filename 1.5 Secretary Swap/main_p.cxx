#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mx;
std::condition_variable cv;
std::queue<std::pair<int, int>> q;
bool finished = false;

void producer()
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
                    continue;
                }
                break;
            }
            std::lock_guard<std::mutex> lk(mx);
            q.push({i, j});
        }
    }
    std::lock_guard<std::mutex> lk(mx);
    finished = true;
    cv.notify_all();
}

void consumer()
{
    const char out_file_name[] = "output.txt";
    FILE *pFile = fopen(out_file_name, "w");

    while (true)
    {
        size_t j, i;
        {
            std::unique_lock<std::mutex> lk(mx);
            cv.wait(lk, [] { return finished || !q.empty(); });
            if (finished && q.empty())
            {
                fprintf(pFile, "No more swaps needed.\n");
                fclose(pFile);
                break;
            }
            if (!q.empty())
            {
                auto pair = q.front();
                i = pair.first;
                j = pair.second;
                q.pop();
            }
        }

        for (size_t k = i; k != j; --k)
        {
            fprintf(pFile, "Swap elements at indices %d and %d.\n", k, k + 1);
        }
    }
}

int main(int argc, char **argv)
{
    std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();

    return 0;
}