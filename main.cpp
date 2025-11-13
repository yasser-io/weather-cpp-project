#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <map>
#include <sstream>
#include <limits>

using namespace std;

struct WeatherData {
    string date;
    string time;
    double temperature;
    double humidity;
    double pressure;
    double windSpeed;
    string condition;
    string city;
};

class WeatherManager {
private:
    vector<WeatherData> weatherRecords;

public:
    string getCurrentDateTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream ss;
        ss << (1900 + ltm->tm_year) << "-"
           << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "-"
           << setw(2) << setfill('0') << ltm->tm_mday;
        return ss.str();
    }

    string getCurrentTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream ss;
        ss << setw(2) << setfill('0') << ltm->tm_hour << ":"
           << setw(2) << setfill('0') << ltm->tm_min;
        return ss.str();
    }

    void addWeatherRecord() {
        WeatherData newRecord;

        cout << "\n--- Add New Weather Record ---" << endl;
        cout << "Enter city: ";
        cin.ignore();
        getline(cin, newRecord.city);

        newRecord.date = getCurrentDateTime();
        newRecord.time = getCurrentTime();

        cout << "Enter temperature (C): ";
        cin >> newRecord.temperature;

        cout << "Enter humidity (%): ";
        cin >> newRecord.humidity;

        cout << "Enter pressure (hPa): ";
        cin >> newRecord.pressure;

        cout << "Enter wind speed (km/h): ";
        cin >> newRecord.windSpeed;

        cout << "Enter condition: ";
        cin.ignore();
        getline(cin, newRecord.condition);

        weatherRecords.push_back(newRecord);
        cout << "Record added successfully!" << endl;
    }

    void displayAllRecords() {
        if (weatherRecords.empty()) {
            cout << "No records found." << endl;
            return;
        }

        cout << "\n--- All Weather Records ---" << endl;
        cout << "==================================================================================" << endl;
        cout << left << setw(12) << "Date"
             << setw(8) << "Time"
             << setw(12) << "City"
             << setw(10) << "Temp(C)"
             << setw(10) << "Humidity"
             << setw(10) << "Pressure"
             << setw(12) << "Wind Speed"
             << setw(15) << "Condition" << endl;
        cout << "==================================================================================" << endl;

        for (const auto& record : weatherRecords) {
            cout << left << setw(12) << record.date
                 << setw(8) << record.time
                 << setw(12) << record.city
                 << setw(10) << record.temperature
                 << setw(10) << record.humidity
                 << setw(10) << record.pressure
                 << setw(12) << record.windSpeed
                 << setw(15) << record.condition << endl;
        }
    }

    void searchByDate() {
        string searchDate;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> searchDate;

        bool found = false;
        for (const auto& record : weatherRecords) {
            if (record.date == searchDate) {
                if (!found) {
                    cout << "\n--- Search Results ---" << endl;
                    cout << "==================================================================================" << endl;
                    cout << left << setw(12) << "Date"
                         << setw(8) << "Time"
                         << setw(12) << "City"
                         << setw(10) << "Temp(C)"
                         << setw(10) << "Humidity"
                         << setw(10) << "Pressure"
                         << setw(12) << "Wind Speed"
                         << setw(15) << "Condition" << endl;
                    cout << "==================================================================================" << endl;
                    found = true;
                }
                cout << left << setw(12) << record.date
                     << setw(8) << record.time
                     << setw(12) << record.city
                     << setw(10) << record.temperature
                     << setw(10) << record.humidity
                     << setw(10) << record.pressure
                     << setw(12) << record.windSpeed
                     << setw(15) << record.condition << endl;
            }
        }

        if (!found) {
            cout << "No records found." << endl;
        }
    }

    void searchByCity() {
        string searchCity;
        cout << "Enter city: ";
        cin.ignore();
        getline(cin, searchCity);

        bool found = false;
        for (const auto& record : weatherRecords) {
            if (record.city == searchCity) {
                if (!found) {
                    cout << "\n--- Search Results for " << searchCity << " ---" << endl;
                    cout << "==================================================================================" << endl;
                    cout << left << setw(12) << "Date"
                         << setw(8) << "Time"
                         << setw(12) << "City"
                         << setw(10) << "Temp(C)"
                         << setw(10) << "Humidity"
                         << setw(10) << "Pressure"
                         << setw(12) << "Wind Speed"
                         << setw(15) << "Condition" << endl;
                    cout << "==================================================================================" << endl;
                    found = true;
                }
                cout << left << setw(12) << record.date
                     << setw(8) << record.time
                     << setw(12) << record.city
                     << setw(10) << record.temperature
                     << setw(10) << record.humidity
                     << setw(10) << record.pressure
                     << setw(12) << record.windSpeed
                     << setw(15) << record.condition << endl;
            }
        }

        if (!found) {
            cout << "No records found." << endl;
        }
    }

    void displayCurrentWeather() {
        if (weatherRecords.empty()) {
            cout << "No data available." << endl;
            return;
        }

        WeatherData latest = weatherRecords.back();
        cout << "\n--- Current Weather ---" << endl;
        cout << "City: " << latest.city << endl;
        cout << "Date: " << latest.date << endl;
        cout << "Time: " << latest.time << endl;
        cout << "Temperature: " << latest.temperature << " C" << endl;
        cout << "Humidity: " << latest.humidity << " %" << endl;
        cout << "Pressure: " << latest.pressure << " hPa" << endl;
        cout << "Wind Speed: " << latest.windSpeed << " km/h" << endl;
        cout << "Condition: " << latest.condition << endl;
    }

    void displayStatistics() {
        if (weatherRecords.empty()) {
            cout << "No data available." << endl;
            return;
        }

        double totalTemp = 0, totalHumidity = 0, totalPressure = 0, totalWind = 0;
        double maxTemp = weatherRecords[0].temperature;
        double minTemp = weatherRecords[0].temperature;

        for (const auto& record : weatherRecords) {
            totalTemp += record.temperature;
            totalHumidity += record.humidity;
            totalPressure += record.pressure;
            totalWind += record.windSpeed;

            if (record.temperature > maxTemp) maxTemp = record.temperature;
            if (record.temperature < minTemp) minTemp = record.temperature;
        }

        int count = weatherRecords.size();

        cout << "\n--- Statistics ---" << endl;
        cout << "Total records: " << count << endl;
        cout << "Average temperature: " << fixed << setprecision(1) << totalTemp / count << " C" << endl;
        cout << "Max temperature: " << maxTemp << " C" << endl;
        cout << "Min temperature: " << minTemp << " C" << endl;
        cout << "Average humidity: " << totalHumidity / count << " %" << endl;
        cout << "Average pressure: " << totalPressure / count << " hPa" << endl;
        cout << "Average wind speed: " << totalWind / count << " km/h" << endl;
    }

    void saveToFile() {
        ofstream file("weather.txt");
        for (const auto& record : weatherRecords) {
            file << record.date << " "
                 << record.time << " "
                 << record.city << " "
                 << record.temperature << " "
                 << record.humidity << " "
                 << record.pressure << " "
                 << record.windSpeed << " "
                 << record.condition << endl;
        }
        file.close();
        cout << "Data saved successfully." << endl;
    }

    void loadFromFile() {
        ifstream file("weather.txt");
        if (!file) {
            cout << "No data file found." << endl;
            return;
        }

        weatherRecords.clear();
        WeatherData record;
        while (file >> record.date >> record.time >> record.city
               >> record.temperature >> record.humidity >> record.pressure
               >> record.windSpeed) {
            getline(file, record.condition);
            weatherRecords.push_back(record);
        }
        file.close();
        cout << "Data loaded successfully." << endl;
    }

    void generateSampleData() {
        WeatherData sample1;
        sample1.date = "2024-01-15";
        sample1.time = "10:30";
        sample1.city = "New York";
        sample1.temperature = 25.5;
        sample1.humidity = 65;
        sample1.pressure = 1013.2;
        sample1.windSpeed = 12.3;
        sample1.condition = "Sunny";

        WeatherData sample2;
        sample2.date = "2024-01-16";
        sample2.time = "14:45";
        sample2.city = "London";
        sample2.temperature = 22.1;
        sample2.humidity = 78;
        sample2.pressure = 1010.5;
        sample2.windSpeed = 18.7;
        sample2.condition = "Cloudy";

        WeatherData sample3;
        sample3.date = "2024-01-17";
        sample3.time = "09:15";
        sample3.city = "Tokyo";
        sample3.temperature = 19.8;
        sample3.humidity = 82;
        sample3.pressure = 1008.9;
        sample3.windSpeed = 25.1;
        sample3.condition = "Rainy";

        weatherRecords.push_back(sample1);
        weatherRecords.push_back(sample2);
        weatherRecords.push_back(sample3);

        cout << "Sample data generated." << endl;
    }

    void deleteRecord() {
        if (weatherRecords.empty()) {
            cout << "No records to delete." << endl;
            return;
        }

        displayAllRecords();
        cout << "Enter record number to delete (1-" << weatherRecords.size() << "): ";
        int index;
        cin >> index;

        if (index < 1 || index > static_cast<int>(weatherRecords.size())) {
            cout << "Invalid number." << endl;
            return;
        }

        weatherRecords.erase(weatherRecords.begin() + index - 1);
        cout << "Record deleted." << endl;
    }
};

void showMenu() {
    cout << "\n=== WEATHER SYSTEM ===" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Show All" << endl;
    cout << "3. Search by Date" << endl;
    cout << "4. Search by City" << endl;
    cout << "5. Current Weather" << endl;
    cout << "6. Statistics" << endl;
    cout << "7. Save to File" << endl;
    cout << "8. Load from File" << endl;
    cout << "9. Add Sample Data" << endl;
    cout << "10. Delete Record" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose: ";
}

int main() {
    WeatherManager manager;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: manager.addWeatherRecord(); break;
            case 2: manager.displayAllRecords(); break;
            case 3: manager.searchByDate(); break;
            case 4: manager.searchByCity(); break;
            case 5: manager.displayCurrentWeather(); break;
            case 6: manager.displayStatistics(); break;
            case 7: manager.saveToFile(); break;
            case 8: manager.loadFromFile(); break;
            case 9: manager.generateSampleData(); break;
            case 10: manager.deleteRecord(); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
