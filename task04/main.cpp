#include <iostream>
#include <vector>
#include <unordered_map>

// Структура для хранения данных одного запроса
struct Request {
    size_t address;
    size_t size;
    size_t id;
};

// Формирование непрерывных последовательностей
std::vector<std::vector<Request>> form_sequences(const std::vector<Request>& requests) {
    std::vector<std::vector<Request>> result;
    std::unordered_map<size_t, size_t> chain_ends;

    for (const auto& current : requests) {
        auto it = chain_ends.find(current.address);
        
        if (it != chain_ends.end()) {
            // Нашли подходящую цепочку
            size_t chain_index = it->second;
            result[chain_index].push_back(current);
            
            // Обновляем адрес конца для этой цепочки
            chain_ends.erase(it);
            chain_ends[current.address + current.size] = chain_index;
        } else {
            // Подходящей цепочки нет. Создаем новую
            result.push_back({current}); 
            // Регистрируем её конец
            chain_ends[current.address + current.size] = result.size() - 1;
        }
    }
    return result;
}

// Печать подпоследовательностей в требуемом формате
void print_sequences(const std::vector<std::vector<Request>>& sequences) {
    for (const auto& chain : sequences) {
        for (size_t i = 0; i < chain.size(); ++i) {
            const auto& req = chain[i];
            // Формат: #<n>[<адрес>; <размер>]
            std::cout << "#" << req.id << "[" << req.address << "; " << req.size << "]";

            if (i + 1 < chain.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<Request> requests = {
        {100, 20, 0}, 
        {300, 50, 1},
        {120, 30, 2},
        {350, 20, 3}
    };

    std::cout << "Исходные запросы:" << std::endl;
    for (const auto& r : requests) {
        std::cout << "#" << r.id << "[" << r.address << "; " << r.size << "] ";
    }
    std::cout << "\n\nРезультаты:" << std::endl;

    auto sequences = form_sequences(requests);
    print_sequences(sequences);

    return 0;
}
