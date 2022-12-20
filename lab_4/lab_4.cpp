#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <iomanip>

int Random(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

void Save(int end)
{
    /*
    std::ofstream saveFile;
    saveFile.open("Save.txt");
    if (saveFile.is_open()) {
        saveFile << end << "\n";
    }
    else
    {
        std::cout << "ошибка в записи файла";
    }

    saveFile.close();*/

    std::ofstream outData;
    outData.open("Save.csv", std::ios::app);
    outData << end << std::endl;

}

//бросок одного кубика заданное число раз
int dice(int a, int b) 
{
    int i = 0;
    int resultat = 0;
    while (i < a)
    {
        resultat = resultat + Random(1, b);
        i = i + 1;
    }
    return resultat;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::string brosok;
    std::string grani;
    std::string summa;
    

    int end = 0;

    std::string cub;
    int prowerka = 0;

    //проверяем корректно ли пользователь ввёл данные
    while (prowerka < 1)
    {
        std::cout << "Введие сколько раз и какой кубик бросить в формате 2d6+5\n";
        std::cin >> cub;

        
        end = 0;
        int i = 0;
        int dlina = 1;

        
            //Броски каждого кубика по отдельности
            while (dlina > 0)
            {
                int brosok_int = 0;
                int grani_int = 0;
                int summa_int = 0;

                dlina = 1;
                int d = 0;
                int plus = 0;
                int komma = 0;

                summa_int = 0;
                int end_brosok;
                i = i + 1;
                try
                {
                    //считывание данных и разбиение их на блоки: количество бросков кубика, число его граней, нужно ли прибавлять число к результату броска
                    dlina = cub.length();
                    d = cub.find("d", 0);
                    brosok = cub.substr(0, d);
                    plus = cub.find("+", 0);
                    komma = cub.find(",", 0);


                    if (komma <= 0)
                    {
                        komma = dlina;
                    }

                    if ((d < plus) && (plus > 0) && (plus < komma))
                    {
                        grani = cub.substr(d + 1, plus);
                        summa = cub.substr(plus + 1, komma);
                    }
                    else
                    {
                        grani = cub.substr(d + 1, komma);
                        plus = 0;
                        summa = "0";
                    }

                    //перевод считанных данных в числа, если это невозможно сделать, значит игрок ввёл что-то кроме чисел, игрока просят ввести данные заново
                    brosok_int = stoi(brosok);
                    grani_int = stoi(grani);
                    summa_int = stoi(summa);
                    end_brosok = dice(brosok_int, grani_int) + summa_int;
                    end = end + end_brosok;
                    prowerka = 1;



                    if (komma == dlina)
                    {
                        dlina = 0;
                    }
                    else
                    {
                        cub = cub.substr(komma + 1, dlina);
                        dlina = cub.length();
                    }

                    //ещё одна проверка, ввёл ли игрок данные в нужном формате
                    if ((d <= 0) || ((plus > 0) && (plus < d + 1)))
                    {
                        prowerka = 0;
                        std::cout << "\nВЫ ВВЕЛИ НЕКОРРЕКТНОЕ ЗНАЧЕНИЕ\n";
                    }
                    else
                    {
                        std::cout << "Бросок кубика номер " << i << "\nВыпало " << end_brosok << "\n\n";
                    }

                }
                catch (...) {
                    prowerka = 0;
                    std::cout << "\nВЫ ВВЕЛИ НЕКОРРЕКТНОЕ ЗНАЧЕНИЕ\n";
                    break;
                };
                
            }
            
        
    }

    std::cout << "РЕЗУЛЬТАТ \n" << end << "\n";
    
}
