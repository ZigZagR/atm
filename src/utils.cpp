#include "../include/utils.h"
#include <cstdlib>

namespace Utils {

int calculateLuhnCheckDigit(int base) {
    int sum = 0;
    bool doubleDigit = true;
    int temp = base;

    while (temp > 0) {
        int digit = temp % 10;

        if (doubleDigit) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        doubleDigit = !doubleDigit;
        temp /= 10;
    }
    return (10 - (sum % 10) % 10) % 10;
}

int generateRandomID(const std::unordered_map<int, std::unique_ptr<account>>& database) {
    int newID;
    bool unique = false;

    while (!unique) {
        int base = rand() % 90000 + 10000;
        int luhnDigit = calculateLuhnCheckDigit(base);
        newID = (base * 10) + luhnDigit;

        if (database.find(newID) == database.end()) {
            unique = true;
        }
    }
    return newID;
}

bool isValidLuhn(int id) {
    int sum = 0;
    bool doubleDigit = false;
    int temp = id;

    while (temp > 0) {
        int digit = temp % 10;

        if (doubleDigit) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        doubleDigit = !doubleDigit;
        temp /= 10;
    }
    return (sum % 10 == 0);
}

} // namespace Utils
