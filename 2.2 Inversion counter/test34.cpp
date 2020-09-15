#include <fstream>

int main(int argc, char** argv) {
    std::ofstream fout("input.txt");

    const size_t max = 100'000;
    fout << max << std::endl;
    long long sum = 0;

    for (size_t i = max; i != 0; --i) {
        sum += i;
        fout << i << " ";
    }
    std::cout << i << std::endl;

    return 0;
}