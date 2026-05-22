#include <vector>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>


template <typename T>
T get_weighted_element(double x, const std::vector<T>& a, const std::vector<double>& w) {
    if (a.empty() || w.empty() || a.size() != w.size()) {
        throw std::invalid_argument("Arrays must be non-empty and of the same size.");
    }

    // Считаем общую сумму весов
    double total_weight = std::accumulate(w.begin(), w.end(), 0.0);

    if (total_weight <= 0.0) {
        throw std::invalid_argument("Total weight must be greater than zero.");
    }
    
    // Заполняем массив кумулятивных сумм
    std::vector<double> cum_weights(w.size());
    double current_sum = 0.0;
    for (size_t i = 0; i < w.size(); ++i) {
        current_sum += w[i];
        cum_weights[i] = current_sum / total_weight;
    }

    // Двоичный поиск
    auto it = std::lower_bound(cum_weights.begin(), cum_weights.end(), x);
    size_t index = it - cum_weights.begin();

    if (index >= a.size()) {
        index = a.size() - 1;
    }

    return a[index];
}


int main() {
    size_t n;
    std::cout << "Количество элементов: ";
    std::cin >> n;

    std::vector<std::string> a(n);
    std::vector<double> w(n);

    std::cout << "Введите через пробел [элемент] [вес] для каждого пункта:\n";
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i] >> w[i];
    }

    double x;
    std::cout << "Введите число x (0.0 - 1.0): ";
    std::cin >> x;

    std::cout << "Выбрано число: " << get_weighted_element(x, a, w) << std::endl;

    return 0;
}
