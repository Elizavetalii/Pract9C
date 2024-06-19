#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <clocale>

class MergeSort {
public:
    // Метод для слияния двух отсортированных подмассивов arr[left..middle] и arr[middle+1..right]
    void merge(std::vector<int>& arr, int left, int middle, int right) {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; ++i) {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < n2; ++j) {
            R[j] = arr[middle + 1 + j];
        }

        int i = 0, j = 0, k = left;

        // Объединяем два подмассива в итоговый отсортированный массив arr
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                ++i;
            }
            else {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        // Добавляем оставшиеся элементы из подмассива L
        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        // Добавляем оставшиеся элементы из подмассива R
        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }

    // Рекурсивная функция для сортировки подмассива arr[left..right] сортировкой слиянием
    void mergeSort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int middle = left + (right - left) / 2;

            // Рекурсивно сортируем левую и правую половины массива
            mergeSort(arr, left, middle);
            mergeSort(arr, middle + 1, right);

            // Сливаем две отсортированные части массива
            merge(arr, left, middle, right);
        }
    }

    // Метод для запуска сортировки слиянием для переданного массива arr
    void Sort(std::vector<int>& arr) {
        mergeSort(arr, 0, arr.size() - 1);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<int> numbers(10);
    std::cout << "Введите 10 целых чисел для сортировки:\n";
    for (int i = 0; i < 10; ++i) {
        std::cin >> numbers[i];
    }

    MergeSort mergeSort;

    // Создаем анонимную функцию, которая вызывает метод Sort
    // объекта MergeSort для сортировки массива numbers
    auto sortFunc = [&mergeSort, &numbers]() {
        mergeSort.Sort(numbers);
        };

    // Создаем поток mergeSortThread,
    //  в котором выполняется анонимная функция sortFunc
    std::thread mergeSortThread(sortFunc);

    // Ожидаем завершения сортировки в дочернем потоке
    mergeSortThread.join();

    // Выводим отсортированный массив на экран
    std::cout << "Отсортированный массив:\n";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}