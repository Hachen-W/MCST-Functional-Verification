#include <iostream>
#include <vector>
#include <unordered_map>

// Структура для хранения данных одного запроса
struct Request {
    size_t address;
    size_t size;
};

// Формирование непрерывных последовательностей
std::vector<std::vector<size_t>> form_sequences(const std::vector<Request>& requests) {
    std::vector<std::vector<size_t>> result;
    std::unordered_map<size_t, size_t> chain_ends;

    for (size_t i = 0; i < requests.size(); ++i) {
        auto it = chain_ends.find(requests[i].address);
        
        if (it != chain_ends.end()) {
            // Нашли подходящую цепочку
            size_t chain_index = it->second;
            result[chain_index].push_back(i);

            // Обновляем адрес конца для этой цепочки
            chain_ends.erase(it);
            chain_ends[requests[i].address + requests[i].size] = chain_index;
        } else {
            // Подходящей цепочки нет. Создаем новую
            result.push_back({i});
            // Регистрируем её конец
            chain_ends[requests[i].address + requests[i].size] = result.size() - 1;
        }
    }

    return result;
}

// Печать подпоследовательностей в требуемом формате
void print_sequences(
        const std::vector<std::vector<size_t>>& sequences, const std::vector<Request>& requests
        ) {
    for (const auto& chain : sequences) {
        for (size_t i = 0; i < chain.size(); ++i) {
            size_t id = chain[i];
            const auto& req = requests[id];
            // Формат: #<n>[<адрес>; <размер>]
            std::cout << "#" << id << "[" << req.address << "; " << req.size << "]";

            if (i + 1 < chain.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<Request> requests = {
        {100, 20}, 
        {300, 50},
        {120, 30},
        {350, 20}
    };

    std::cout << "Исходные запросы:" << std::endl;
    for (size_t i = 0; i < requests.size(); ++i) {
        std::cout << "#" << i << "[" << requests[i].address << "; " << requests[i].size << "] ";
    }
    std::cout << "\n\nРезультаты:" << std::endl;

    auto sequences = form_sequences(requests);
    print_sequences(sequences, requests);

    return 0;
}
