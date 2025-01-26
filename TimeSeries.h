#ifndef TIMESERIES_H
#define TIMESERIES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Dynamic Array Class Declaration
class dynamic_array {
private:
    int* years;           // Array to store years
    double* datas;        // Array to store data corresponding to years
    int size;             // Current size of the dynamic array
    int capacity;         // Current capacity of the dynamic array
    const int year_begin = 1960;
    const int year_end = 2023;

    void resize_array(int new_capacity); // Function to resize the array

public:
    dynamic_array();                      // Constructor
    ~dynamic_array();                     // Destructor
    bool ADD(int add_year, double add_data); // Add a year-data pair
    void LOAD(const std::string& filename); // Load data from a file
    bool UPDATE(int update_year, double update_data); // Update existing data
    double mean();                        // Calculate mean of all valid data
    bool is_monotonic();                  // Check if the data series is monotonic
    void best_fit(double &m, double &b);  // Compute line of best fit
    void PRINT();                         // Print the time series
};

#endif // DYNAMIC_ARRAY_H
