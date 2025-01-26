#include "TimeSeries.h"

// Constructor
dynamic_array::dynamic_array() {
/*
    CITATION:
This function was developed with guidance from an example provided by chat.openai.com.
Prompt: "Teach me how to write a typical dynamic array. Give me an example."
The AI example helped me understand the structure of a dynamic array, and I wrote this 
constructor independently based on that understanding.
*/
 
    capacity = 2;
    size = 0;
    years = new int[capacity];
    datas = new double[capacity];
}

// Destructor
dynamic_array::~dynamic_array() {
    delete[] years;
    delete[] datas;
}

// Resize Array
void dynamic_array::resize_array(int new_capacity) {
/*
    CITATION:
    This function was written with the assistance of ChatGPT. 
    Prompt: "Write a C++ function to resize a dynamic array while preserving its contents."
    The AI provided the structure for resizing and copying data.
*/

    if (new_capacity < 2) {
        new_capacity = 2; // Minimum capacity is 2
    }

    int* new_years = new int[new_capacity];
    double* new_datas = new double[new_capacity];

    for (int i = 0; i < size; i++) {
        new_years[i] = years[i];
        new_datas[i] = datas[i];
    }

    delete[] years;
    delete[] datas;

    years = new_years;
    datas = new_datas;
    capacity = new_capacity;
}

// ADD Function
bool dynamic_array::ADD(int add_year, double add_data) {
    for (int i = 0; i < size; i++) {
        if (years[i] == add_year) {
            std::cout << "failure\n";
            return false;
        }
    }
/*
    CITATION:
    This function was modified by chat.openai.com with the prompt:
    "My ADD function always report error when operating. Can you point out my
    problem?"
    The AI tool pointed out that I didn't resize my array, and it fixed a few
    syntax problems for me after generating the following block that doubled
    array size.
*/
 
    if (size == capacity) {
        resize_array(capacity * 2);
    }
    years[size] = add_year;
    datas[size] = add_data;
    size++;
    return true;
}

// LOAD Function
/*
    CITATION:
    This function was modified by chat.openai.com with the prompt:
    "Teach me how to access a dynamic array as I intend to load the csv file into 
    a new string, and then transfer the string into double"
    The AI tool generated an example of a load function, and it showed example
    of std::stod(element). Using the example code as guide, I wrote the other
    part of this function.
*/
 
void dynamic_array::LOAD(const std::string& filename) {
    std::ifstream inputfile(filename);
    if (!inputfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    size = 0;

    std::string target_string;
    while (std::getline(inputfile, target_string)) {
        std::stringstream theline(target_string);
        std::string element;

        // Skip the first four columns
        for (int i = 0; i < 4; i++) {
            std::getline(theline, element, ',');
        }

        int year = year_begin;

        while (std::getline(theline, element, ',')) {
            double value = std::stod(element);
            if (value != -1) {
                ADD(year, value);
            }
            year++;
        }
    }

    std::cout << "success\n";
    inputfile.close();
}

// UPDATE Function
bool dynamic_array::UPDATE(int update_year, double update_data) {
    for (int i = 0; i < size; i++) {
        if (years[i] == update_year) {
            datas[i] = update_data;
            std::cout << "success\n";
            return true;
        }
    }
    std::cout << "failure\n";
    return false;
}

// Mean Function
double dynamic_array::mean() {
    if (size == 0) {
        std::cout << "failure\n";
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
/*
    CITATION:
    This function was modified by chat.openai.com with the prompt:
    "why is sum += sum not working here?"
    The AI tool changed my line into sum += datas[i] and fixed this minor error
*/
        sum += datas[i];
    }
    double avg = sum / size;
    std::cout << "mean is " << avg << "\n";
    return avg;
}

// Monotonic Check
bool dynamic_array::is_monotonic() {
    if (size == 0) {
        std::cout << "failure\n";
        return false;
    }
/*
    CITATION:
    This function was modified by chat.openai.com with the prompt:
    "I have problems with monotonic test. My code could only interpret if
    a function is monotonic as init has a positive slope. Give me 3 ideas of
    how people would normally judge if a series of number keeps increasing
    or decreasing"
    The AI tool suggested that boolean function is a good idea.
*/
    bool increasing = true, decreasing = true;
    for (int i = 1; i < size; i++) {
        if (datas[i] < datas[i - 1]) increasing = false;
        if (datas[i] > datas[i - 1]) decreasing = false;
    }
    if (increasing || decreasing) {
        std::cout << "series is monotonic\n";
        return true;
    } else {
        std::cout << "series is not monotonic\n";
        return false;
    }
}

// Best Fit Function
void dynamic_array::best_fit(double &m, double &b) {
    if (size == 0) {
        std::cout << "failure\n";
        return;
    }
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
/*
    CITATION:
    This function was modified by chat.openai.com with the prompt:
    "I have trouble changing these two math functions into cpp code. Can 
    you help me fix my wrong equations?"
    The AI tool corrected my mistake in the math functions that did the calculation wrong
*/
    for (int i = 0; i < size; i++) {
        sum_x += years[i];
        sum_y += datas[i];
        sum_xy += years[i] * datas[i];
        sum_x2 += years[i] * years[i];
    }
    double n = size;
    m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    b = (sum_y - m * sum_x) / n;
    std::cout << "slope is " << m << " intercept is " << b << "\n";
}

// PRINT Function
void dynamic_array::PRINT() {
/*
    CITATION:
    This function was modified by chat.openai.com with the prompt:
    "This PRINT function has errors I couldn't find. I think it may be about 
    the for loop I wrote. Can you please correct the mistake and point out 
    in which part I did wrong? How can I correct the mistake?"
    The AI tool changed the index of the original for loop 
*/
    if (size == 0) {
        std::cout << "failure\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        if(datas[i] != -1){
        std::cout << "(" << years[i] << "," << datas[i] << ") ";
        }
    }
    std::cout << "\n";
}
