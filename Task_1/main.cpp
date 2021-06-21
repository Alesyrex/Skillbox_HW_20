#include <iostream>
#include <fstream>
#include <string>

bool correct_date (std::string date) {
    if (date.length() != 10) return false;
    else {
        int DD[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        int month = std::stoi(date.substr(3,2));
        int day = std::stoi(date.substr(0,2));
        int year = std::stoi(date.substr(6,4));
        if ((month > 12 || month < 1) || (year < 1970 || year > 2038)
            || (day < 1 || day > DD[month - 1])) return false;
        else return true;
    }
}

int main() {

    std::string name,dateOfIssue;
    double payAmount;
    std::cout << "Enter first and last name:";
    std::getline(std::cin,name);
    do {
        std::cout << "Date of issue of money (DD.MM.YYYY):";
        std::cin >> dateOfIssue;
        if (!correct_date(dateOfIssue)) std::cout << "Incorrect date.";
    } while (!correct_date(dateOfIssue));
    do {
        std::cout << "Payout amount:";
        std::cin >> payAmount;
        if (payAmount < 0) std::cout << "Incorrect amount.";
    } while (payAmount < 0);

    std::ofstream bill("C:\\files\\write\\bill.txt", std::ios::app);
    bill << name << " " << dateOfIssue << " " << payAmount << std::endl;
    bill.close();

    return 0;
}
