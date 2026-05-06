#ifndef UTILS_H
#define UTILS_H

#include <unordered_map>
#include <memory>
#include "account.h"

namespace Utils {
    int calculateLuhnCheckDigit(int base);
    int generateRandomID(const std::unordered_map<int, std::unique_ptr<account>>& database);
    bool isValidLuhn(int id);
}

#endif
