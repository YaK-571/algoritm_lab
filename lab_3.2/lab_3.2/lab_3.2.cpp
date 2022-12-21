#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include  "Header.h"

int Random(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

template<typename T>

void Save(int a, T b, T c)
{
    std::ofstream outData;
    outData.open("Save.csv", std::ios::app);
    outData << a <<";" << b <<";" << c << std::endl;

}

int main()
{
    setlocale(LC_ALL, "Russian");

    //создание массивов разной длины, для проверки скорости сортировок
    for (int size = 5; size <= 100; size++) {

        std::chrono::nanoseconds insertTime = std::chrono::nanoseconds(0);
        std::chrono::nanoseconds quickSortTime = std::chrono::nanoseconds(0);

        int* arrInsert = new int[size];
        int* arrQuickSort = new int[size];

        for (int j = 0; j < 100; j++) {
            //создание двух рандомных массивов. Первый для сортировки вставками, второй для быстрой сортировки
            for (int i = size - 1, k = 1; i >= 0; i--, k++) {
                arrInsert[i] = k;
            }

            for (int i = 0; i < size; i++) {
                arrQuickSort[i] = Random(1, 100);
            }


            //таймер и сортировка
            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(arrInsert, arrInsert + size - 1, [](int a, int b) {return a < b; });
            auto end = std::chrono::high_resolution_clock::now();
            insertTime = (end - start);

            //таймер и сортировка
            start = std::chrono::high_resolution_clock::now();
            quickSort(arrQuickSort, arrQuickSort + size - 1, [](int a, int b) {return a < b; });
            end = std::chrono::high_resolution_clock::now();
            quickSortTime = (end - start);


        }
       
        Save(size, insertTime.count(), quickSortTime.count());
       
        //очистка массивов
        delete[] arrInsert;
        delete[] arrQuickSort;

    }

}