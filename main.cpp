#include <iostream>
#include <sstream>
#include "dynamic_array.h"

int main() {
    dynamic_array the_array; // Create an instance of the dynamic array
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "ADD") {
            int year;
            double value;
            iss >> year >> value;
          	bool added = the_array.ADD(year, value);
            if (added){
                std::cout<<"success\n";
            }
        } else if (command == "LOAD") {
            std::string filename;
            iss >> filename;
            the_array.LOAD(filename);
        } else if (command == "UPDATE") {
            int year;
            double value;
            iss >> year >> value;
            the_array.UPDATE(year, value);
        } else if (command == "PRINT") {
            the_array.PRINT();
        } else if (command == "MEAN") {
            the_array.mean();
        } else if (command == "MONOTONIC") {
            the_array.is_monotonic();
        } else if (command == "FIT") {
            double m, b;
            the_array.best_fit(m, b);
        } else if (command == "EXIT") {
            break;
        } else {
            std::cerr << "Unknown command\n";
        }
    }

    return 0;
}
