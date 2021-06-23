#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

std::fstream ATM;

void sort_vec (std::vector<int> &vec) {
    for (int i=0;i < vec.size();i++) {
        for (int j=0;j < vec.size()-i-1;j++) {
            if(vec[j+1] > vec[j]) {
                int temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;
            }
        }
    }
}

void replenishment_ATM (std::vector<int> &bills) {
    std::srand(std::time(nullptr));
    int temp;
    ATM.open ("C:\\files\\write\\ATM.bin",std::ios::binary | std::ios::in | std::ios::out);
    while(!ATM.eof()){
        ATM.read((char*)&bills, sizeof(bills.size()));
    }
    for (int i=0;i < 1000;){
        temp = rand()%4901 + 100;
        if (bills[i] == 0 && (temp == 100 || temp == 200 || temp == 500 || temp == 1000
                                     || temp == 2000 || temp == 5000)) {
            bills[i] = temp;
            ATM.write((char*)&bills[i],sizeof(int));
            i++;
        }
    }
    sort_vec(bills);
    for (int i=0;i < 1000;i++){
        std::cout << bills[i] << " ";
    }
    ATM.close();
}

void withdraw_cash (std::vector<int> &bills) {
    int cash;
    std::cout << "Enter the amount to withdraw:";
    std::cin >> cash;

    sort_vec(bills);
    for (int i=0;i < 1000;i++){
        if (cash - bills[i] > 0) {
            cash -= bills[i];
            bills[i] = 0;
        }
        else if (cash - bills[i] == 0) {
            cash -= bills[i];
            bills[i] = 0;
            break;
        } else i++;
    }
    ATM.open ("C:\\files\\write\\ATM.bin", std::ios::binary | std::ios::out);
    if (cash > 0) {
        std::cout << "Insufficient funds at the ATM.";
    }
    else{
        for (int i=0;i < 1000;i++) {
            ATM.write((char*)&bills[i],sizeof(int));
        }
        ATM.close();
    }
}

int main() {
    std::vector<int> denomination(1000);
    char action;

    std::cout << "Input '+' to replenishment ATM or '-' to withdraw cash:";
    std::cin >> action;
    if (action != '+' && action != '-') {
        std::cout << "Incorrect input!";
        return 0;
    }
    else {
        if (action == '+') replenishment_ATM(denomination);
        else withdraw_cash(denomination);
    }
    return 0;
}