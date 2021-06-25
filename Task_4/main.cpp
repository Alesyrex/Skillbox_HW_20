#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

std::fstream ATM;

void sort (int *bills) {
    for (int i=0;i < 1000;i++) {
        for (int j=0;j < 1000-i-1;j++) {
            if(bills[j+1] > bills[j]) {
                int temp = bills[j];
                bills[j] = bills[j+1];
                bills[j+1] = temp;
            }
        }
    }
}

void replenishment_ATM (int *bills) {
    std::srand(std::time(nullptr));
    int temp;
    ATM.open ("C:\\files\\write\\ATM.bin",std::ios::binary | std::ios::in);
    for (int i=0;i < 1000;i++) {
        ATM.read((char *)&bills[i], sizeof(bills[i]));
    }
    ATM.close();
    for (int i=0;i < 1000;i++){
        if (bills[i] == 0) {
            temp = rand() % 6;
            if (temp == 0) bills[i] = 100;
            if (temp == 1) bills[i] = 200;
            if (temp == 2) bills[i] = 500;
            if (temp == 3) bills[i] = 1000;
            if (temp == 4) bills[i] = 2000;
            if (temp == 5) bills[i] = 5000;
        }
    }
    sort(bills);
    ATM.open ("C:\\files\\write\\ATM.bin",std::ios::binary | std::ios::out);
    for (int i=0;i < 1000;i++){
        ATM.write((char*)&bills[i],sizeof(bills[i]));
    }
    ATM.close();
}

void withdraw_cash (int *bills) {
    int cash;
    std::cout << "Enter the amount to withdraw:";
    std::cin >> cash;

    ATM.open ("C:\\files\\write\\ATM.bin",std::ios::binary | std::ios::in);
    for (int i=0;i < 1000;i++) {
        ATM.read((char *)&bills[i], sizeof(bills[i]));
    }
    ATM.close();

    for (int i=0;i < 1000;i++){
        if (cash - bills[i] > 0) {
            cash -= bills[i];
            bills[i] = 0;
        }
        else if (cash - bills[i] == 0) {
            cash -= bills[i];
            bills[i] = 0;
            break;
        }
    }
    if (cash > 0) {
        std::cout << "Insufficient funds at the ATM.";
    }
    else{
        ATM.open ("C:\\files\\write\\ATM.bin",std::ios::binary | std::ios::out);
        for (int i=0;i < 1000;i++) {
            ATM.write((char*)&bills[i],sizeof(bills[i]));
        }
        ATM.close();
    }
}

int main() {
    int denomination [1000] = {0};
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