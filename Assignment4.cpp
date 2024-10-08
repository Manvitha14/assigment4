#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <ctime>
#include <regex>  // For regex validation

// Struct to hold sales record
struct SalesRecord {
    std::string date;  // Format YYYY-MM-DD
    int sales_id;
    std::string description;
    std::string item;
    int quantity;
    double unit_price;
};

// Helper function to validate date in YYYY-MM-DD format
bool validateDate(const std::string& date) {
    std::regex datePattern(R"(\d{4}-\d{2}-\d{2})");  // YYYY-MM-DD
    return std::regex_match(date, datePattern);
}

// Helper function to validate sales ID, quantity, and unit price
bool validatePositiveInteger(const int value) {
    return value > 0;
}

bool validatePositiveDouble(const double value) {
    return value > 0.0;
}

// Function to input sales data from the console with validation
void inputSalesData(std::vector<SalesRecord>& records) {
    SalesRecord record;
    std::cout << "Enter record details: \n";

    // Validate date input
    do {
        std::cout << "Date (YYYY-MM-DD): ";
        std::cin >> record.date;
        if (!validateDate(record.date)) {
            std::cout << "Invalid date format. Please enter a valid date in YYYY-MM-DD format.\n";
        }
    } while (!validateDate(record.date));

    // Validate sales ID input
    do {
        std::cout << "Sales ID: ";
        std::cin >> record.sales_id;
        if (!validatePositiveInteger(record.sales_id)) {
            std::cout << "Sales ID must be a positive integer.\n";
        }
    } while (!validatePositiveInteger(record.sales_id));

    std::cin.ignore();  // To handle leftover newline character

    // Validate non-empty description
    do {
        std::cout << "Description: ";
        std::getline(std::cin, record.description);
        if (record.description.empty()) {
            std::cout << "Description cannot be empty.\n";
        }
    } while (record.description.empty());

    // Validate non-empty item
    do {
        std::cout << "Item: ";
        std::cin >> record.item;
        if (record.item.empty()) {
            std::cout << "Item cannot be empty.\n";
        }
    } while (record.item.empty());

    // Validate quantity input
    do {
        std::cout << "Quantity: ";
        std::cin >> record.quantity;
        if (!validatePositiveInteger(record.quantity)) {
            std::cout << "Quantity must be a positive integer.\n";
        }
    } while (!validatePositiveInteger(record.quantity));

    // Validate unit price input
    do {
        std::cout << "Unit Price: ";
        std::cin >> record.unit_price;
        if (!validatePositiveDouble(record.unit_price)) {
            std::cout << "Unit Price must be a positive number.\n";
        }
    } while (!validatePositiveDouble(record.unit_price));

    records.push_back(record);
}

// Function to write data to a CSV file
void writeCSV(const std::string& filename, const std::vector<SalesRecord>& records) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& record : records) {
        file << record.date << ","
             << record.sales_id << ","
             << record.description << ","
             << record.item << ","
             << record.quantity << ","
             << record.unit_price << "\n";
    }
}

// Function to read CSV file and load data into a vector of SalesRecord
std::vector<SalesRecord> readCSV(const std::string& filename) {
    std::vector<SalesRecord> records;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
        return records;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        SalesRecord record;
        std::string temp;

        std::getline(ss, record.date, ',');
        std::getline(ss, temp, ',');
        record.sales_id = std::stoi(temp);
        std::getline(ss, record.description, ',');
        std::getline(ss, record.item, ',');
        std::getline(ss, temp, ',');
        record.quantity = std::stoi(temp);
        std::getline(ss, temp, ',');
        record.unit_price = std::stod(temp);

        records.push_back(record);
    }

    return records;
}

// Remaining functions are unchanged...
// Function to update, delete, sort, generate report, etc.

int main() {
    std::vector<SalesRecord> records;
    std::string inputFilename = "inputfile.csv";
    std::string tempFilename = "temp.csv";
    std::string reportFilename = "report.txt";

    char choice;
    do {
        std::cout << "\nChoose an operation:\n";
        std::cout << "1. Add record\n2. Update record\n3. Delete record\n4. View all records\n";
        std::cout << "5. Sort and save to temp file\n6. Generate sales report\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                inputSalesData(records);
                writeCSV(inputFilename, records);
                break;
            // Other cases for update, delete, etc.
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 'q');  // Use 'q' for quit

    return 0;
}
