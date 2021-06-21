#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));

    int height,width;
    std::vector<int> picture;
    std::cout << "Enter the length and width of the pattern:";
    std::cin >> height >> width;

    std::ofstream pict("C:\\files\\write\\pict.txt");
    for (int i=0;i < (height * width);i++) {
        picture.push_back(std::rand()%2);
    }
    for (int i=0;i < height;i++) {
        for (int j=0;j < width;j++) {
            pict << picture[j+(i * width)];
        }
        pict << std::endl;
    }
    pict.close();
    return 0;
}
