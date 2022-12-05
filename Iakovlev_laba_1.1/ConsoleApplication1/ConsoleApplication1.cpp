
#include <iostream>;
#include <random>;
// библиотека для генерации рандомных чисел
#include <fstream>;

int Random(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
    // конструкция для генерации случайных чисел в заданном диапазоне
}

void Ex()
{
    std::cout << "\n\nГосподин, вы сошли с ума! ИГРА ЗАВЕРШЕНА! \n";
}

void Ex_Dead()
{
    std::cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города.Теперь вы вынуждены влачить жалкое существование в изгнании\n";
}

void SaveGame(int raundt_save, int naselenie_save, int akr_save, double pscheniza_save, double P_save, double L_save ) 
{
    std::ofstream saveFile;
    saveFile.open("SaveFile.txt");
    if (saveFile.is_open()) {
        saveFile << raundt_save << " " << naselenie_save << " " << akr_save << " " << pscheniza_save << " " << P_save << " " << L_save;
       }
    else
    {
        std::cout << "ошибка в записи файла";
    }

    saveFile.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //функция для использования русского текста. Без неё кириллица выводится неправильно
    // 
     //---------------объявление стартовых параметров--------------------
    int raundt = 0;

    int naselenie = 100;
    double pscheniza = 2800;
    int akr = 1000;
    int potreblenie = 20;
    int max_obrabotano_akr = 10;
    double semena = 0.5;
    int summa_pokupki;
    int i = 0;
    int b = 5;
    double P = 0, L = 0;


    
    int prodolschenie = 0;
      std::ifstream loadGame("SaveFile.txt");
      if (loadGame)
      {
          std::cout << "Обнаружено сохранение\n";
          std::cout << "Хотите продолжить игру с сохранения?\n";
          std::cout << "Введите цифру 1 для продолжения или другой символ, чтобы начать заново\n";
          std::cin >> prodolschenie;

          if (prodolschenie == 1)
          {
              loadGame >> raundt >> naselenie >> akr >> pscheniza >> P >> L;
              // Считывание значений из файла в переменные по порядку

              std::cout << "С возвращением, милорд\n";
          }
      }
       
           std::cout << "Приветствую вас в ваших новых владениях, господин\n";
           std::cout << "Размер вашего города " << akr << " акров\n";
           std::cout << "Численность ваших подданных " << naselenie << " человек \n";
           std::cout << "В наших закромах хронится " << pscheniza << " бушелей пшеницы\n";
       

    while (raundt<10)
    {
        int a = 0;
        std::cout << " Чтобы остановить игру и сохранится введите 1, чтобы продолжить игру введите введите любой другой символ, \n\n";
        std::cin >> a;
        if (a == 1)
        {
            SaveGame(raundt, naselenie, akr, pscheniza, P, L);
            return 0;
        }


        raundt = raundt + 1;
        std::cout << "\n\n " << raundt << " ГОД ПРАВЛЕНИЯ\n\n";
        

        //--------- Продажа земли ---------------

        int zena_akr = -Random(17, 26);
        std::cout << "Цена акра земли в этом году составляет " << zena_akr <<" бушелей пшеницы\n";

        int pokupka_akr;
        std::cout << "Сколько акров земли повелеваешь продать или купить? \n(введите отрицательное число, если хотите продать землю и положительное, чтобы купить)";
        std::cin >> pokupka_akr;
        int i = 0;
        if (pokupka_akr < 0)
            //если мы продаём землю
        {
            if (-pokupka_akr > akr)
                //проверяем есть ли у нас столько земель для продажи
            {
                i = 0;
                while ((-pokupka_akr > akr) && (i < b))
                {
                    i = i + 1;
                    if (i == b)
                    {
                        Ex();
                        return 0;
                    }
                    std::cout << "Господин, у нас нет столько земель для продажи! Сколько акров земли повелеваешь продать?";
                    std::cin >> pokupka_akr;
                    if (pokupka_akr>0)
                    {
                        pokupka_akr = -pokupka_akr;
                    }
                }
                
            }
            summa_pokupki = pokupka_akr * zena_akr;
        }

        else
            //если мы покупаем землю
        {
            summa_pokupki = pokupka_akr * zena_akr;
            if (abs(summa_pokupki) > pscheniza)
                //проверяем хватит ли нам денег для покупки земли
            {
                int i = 0;
                while ((abs(summa_pokupki) > pscheniza) && (i < b))
                {
                    i = i + 1;
                    if (i == b)
                    {
                        Ex();
                        return 0;
                    }
                    int max_pokupka = floor(pscheniza / abs(zena_akr));
                    std::cout << "Выдержит ли казна такие убытки? Наши запасы позволяют купить только " << max_pokupka << " акров земли. Сколько земли купить?";
                    std::cin >> pokupka_akr;
                    pokupka_akr = abs(pokupka_akr);
                    summa_pokupki = pokupka_akr * zena_akr;
                }

            }
        }
        akr = akr + pokupka_akr;
        pscheniza = pscheniza + summa_pokupki;
        
        if (summa_pokupki < 0)
        {
            std::cout << "Куплено акров " << pokupka_akr << ". Размер нашей земли " << akr << "\n";
            std::cout << "Потрачено " << summa_pokupki << " бушелей пшеницы. Осталось в закромах " << pscheniza << "\n";
        }
        else
        {
            std::cout << "Продано акров " << pokupka_akr << ". Размер нашей земли " << akr << "\n";
            std::cout << "Заработано " << summa_pokupki << " бушелей пшеницы. Осталось в закромах " << pscheniza << "\n";
        }

        //------------------- Сколько пшеницы съесть ----------------------
        double potrebit_pschena;
        std::cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
            std::cin >> potrebit_pschena;
            potrebit_pschena = abs(potrebit_pschena);
            if (potrebit_pschena> pscheniza)
                //проверяем есть ли у нас столько зерна, сколько указал игрок
            {
                i = 0;
                while ((potrebit_pschena > pscheniza)&&(i<b))
                {
                    i = i + 1;
                    if (i == b)
                    {
                        Ex();
                        return 0;
                    }
                    std::cout << "Господин, у нас нет столько еды, чтобы отдать крестьянам. Сколько сьесть еды? ";
                    std::cin >> potrebit_pschena;
                }

            }
            //---------------------Проверяем сколько еды съедено и есть ли голод---------------------
            int eda = naselenie * potreblenie;
            //сколько нужно пшеницы, чтобы еды хватало
            if (potrebit_pschena > pscheniza)
            {
                potrebit_pschena = pscheniza;
            }
            double golod = 0;
            //сколько жителей умерло от голода в раунде

            if (potrebit_pschena < eda)
                // проверяем хватает ли пшеницы
            {
                golod = (-1 * (potrebit_pschena - eda));
                golod = int(ceil(golod / potreblenie));
                //здесь был баг. При малом числе еды почему-то в любом случае выживал 1 человек из-за проблем с округлением.
                //После разделения этой операции на две части, всё почему-то заработало


            }
            pscheniza = pscheniza- potrebit_pschena;


            //---------------Засеивание земли----------------
            std::cout << "Сколько акров земли повелеваешь засеять? ";
            int zasejat_akr;
            std::cin >> zasejat_akr;
            if (zasejat_akr < 0)
            {
                zasejat_akr = zasejat_akr * -1;
            }

            if (zasejat_akr > akr)
                //проверяем есть ли у нас столько акров земли
            {
                int i = 0;
                while ((zasejat_akr > akr) && (i < b))
                {
                    i = i + 1;
                    if (i == b)
                    {
                        Ex();
                        return 0;
                    }
                    std::cout << "Господин, у нас нет столько земель. Сколько засеять акров? ";
                    std::cin >> zasejat_akr;
                }
            }
            double tserno = zasejat_akr * semena;
            //сколько нужно зерна, чтобы засеять указанное количество земли
            
            int tsasejano_max = pscheniza * 2;
            //Проверяем сколько позволяют засеять наши запасы
            if (tserno > pscheniza)
                //проверяем хватает ли нам зерна, чтобы засеять указанное количество земли
            {
                int i = 0;
                while ((tserno > pscheniza) && (i < b))
                {
                    i = i + 1;
                    if (i == b)
                    {
                        Ex();
                        return 0;
                    }
                    std::cout << "Господин, нам не хватит зерна, чтобы засеять такие просторы! Нашего зерна хватило бы, чтобы засеять " << tsasejano_max << " акров. Сколько акров земли засеять?";
                    std::cin >> zasejat_akr;
                    tserno = zasejat_akr * semena;
                    
                }

            }
            pscheniza = pscheniza - tserno;
            //отнимаем от запасов зерно, идущее на посев
        
        std::cout << " \n\n Мой повелитель, соизволь поведать тебе \n в году " << raundt <<" твоего высочайшего правления\n";
        
       

      
       
       double dead = 100*golod / naselenie;
       if (dead > 45)
       {
           std::cout << "Голод пришёл в наши земли! Умерло " << dead << "% населения города! \n";
           Ex_Dead();
           return 0;
       }
       naselenie = naselenie - golod;
       
             

       //---------------- Сколько урожая собрали -----------------
       int proiswoditelnost_plan = naselenie * max_obrabotano_akr;
       //проверяем сколько максимум акров могут засеять жители если бы у всех было много земли
       int proiswoditelnost_fakt;
       int uroschainost = Random(1, 6);
       // урожайность с акра в этом году
       if (proiswoditelnost_plan <= zasejat_akr)
       {
           proiswoditelnost_fakt = proiswoditelnost_plan * uroschainost;
           // сколько засеют крестьяне, если земли вдоволь
       }
       else
       {
           proiswoditelnost_fakt = zasejat_akr * uroschainost;
           // сколько засеют крестьяне, если земли меньше максимума, который они могли бы обработать
       }


       //----------- Сколько человек пришло ------------
       std::cout << golod << " человек умерли с голоду \n";
       int prischlo = int( ceil(golod / 2 + (5 - uroschainost) * pscheniza / 600 + 1));
       if (prischlo < 0)
       {
           prischlo = 0;
       }
       else if (prischlo > 50)
       {
           prischlo = 50;
       }
       naselenie = prischlo + naselenie;
       std::cout << prischlo << " человек прибыли в наш великий город. \n";



           //---------------Проверяем наступила ли чума---------------
           int tschuma = Random(1, 100);
           if (tschuma <= 15)
           {
               naselenie = naselenie / 2;
               std::cout << "Чума уничтожила половину населения!\n ";
           }
           else
           {
               std::cout << "В этот год болезни миновали наш город, милорд\n ";
           }
       std::cout << "Население города сейчас составляет " << naselenie << "\n";


       //----------- Сколько в итоге урожая ------------
       pscheniza = pscheniza + proiswoditelnost_fakt;
       //сколько пшеницы мы в итоге получили
       std::cout << "Мы собрали " << proiswoditelnost_fakt << " бушеля пшеницы, по " << uroschainost << " бушеля с акра.\n";
       
       int maus =  pscheniza * (Random (0, 7)*0.01);
       pscheniza = pscheniza - maus;
       std::cout << "Крысы истребили " << maus << " бушеля пшеницы, оставив " << pscheniza << " бушеля в амбарах.\n";
       
       double akr_na_schitelja =  akr/ naselenie;
      

       //---------- Подсчёт статистики ---------------
       P = P + dead;
       L = L + akr_na_schitelja;

    }
    
    P = P / 10;
    L = L / 10;

    //-------------- Результат игры ---------------------
    if ((P > 33) || (L < 7))
    {
        Ex_Dead();
    }
    else if ((P > 10) || (L < 9))
    {
        std::cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному.Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем\n";
    }
    else if ((P > 3) || (L < 10))
    {
        std::cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова\n";
    }
    else
    {
        std::cout << "\n\nФантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше\n\n";
    }


    std::cout << "ИГРА БЫЛА ПРОЙДЕНА\n";
    
}
