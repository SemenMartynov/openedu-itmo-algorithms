#include <fstream>

int main(int argc, char **argv)
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int a;
    int b;
    fin >> a >> b;
    fout << (a + b * static_cast<long long>(b)) << std::endl;

    return 0;
}