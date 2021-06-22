#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::string fish,temp;
    std::cout << "What kind of fish do we catch?" << std::endl;
    std::cin >> fish;

    std::ifstream fishing("C:\\files\\write\\river.txt");
    std::ofstream basket("C:\\files\\write\\basket.txt", std::ios::app);
    while (!fishing.eof()) {
        fishing >> temp;
        if (temp == fish) {
            basket << temp << std::endl;
        }
    }
    fishing.close();
    basket.close();
    return 0;
}
