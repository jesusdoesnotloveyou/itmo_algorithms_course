#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "time.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string>

int died_from_starving_summary = 0;//
int acre_per_citizen = 0;

int citizens_num = 100;//
int bushel_of_wheat = 2800;//
int acre_of_city = 1000;//

int died_starving_citizens = 0;//
int new_citizens = 0;//
int bushel_per_acre = 0;//
int bushel_eaten_by_rats = 0;//

int acre_price;//

int bIsTherePlague;//
bool bIsLost = false;

int acre_to_buy = 0;
int acre_to_sell = 0;
int bushel_to_eat = 0;
int acre_to_seed = 0;

int randBetween(const int from, const int to)
{
    if (to == from) return to;    
    if (from > to) return randBetween(to, from);
    return from + rand() % (from - to + 1);
}

void update()
{
    acre_price = randBetween(17, 26);
    bushel_per_acre = randBetween(1, 6);
    
    acre_of_city += acre_to_buy;
    bushel_of_wheat -= acre_to_buy * acre_price;
    acre_of_city -= acre_to_sell;
    bushel_of_wheat += acre_to_sell * acre_price;
    
    bushel_eaten_by_rats = randBetween(0, (int)(0.07f * (float)bushel_of_wheat));
    bushel_of_wheat += (acre_to_seed * bushel_per_acre - int(acre_to_seed * 0.5f));
    bushel_of_wheat -= (bushel_to_eat + bushel_eaten_by_rats);
    
    bushel_to_eat -= citizens_num * 20;
    if (bushel_to_eat < 0) {
        died_starving_citizens = bushel_to_eat * (-1) / 20;
        if ((bushel_to_eat * (-1) % 20) > 0) {
            ++died_starving_citizens;
        }
        int prev_citizens_num = citizens_num;
        citizens_num -= died_starving_citizens;
        
        if (float(prev_citizens_num / citizens_num) > 1.45f) {
            bIsLost = true;
            return;
        }

        died_from_starving_summary += died_starving_citizens;
    }
    if (bushel_to_eat >= 0) {
        died_starving_citizens = 0;
        bushel_of_wheat += bushel_to_eat;
    }
    new_citizens = died_starving_citizens / 2 + (5 - bushel_per_acre) * bushel_of_wheat / 600 + 1;
    if (new_citizens > 50) new_citizens = 50;
    if (new_citizens < 0) new_citizens = 0;
    citizens_num += new_citizens;

    bIsTherePlague = randBetween(1, 100);
    if (bIsTherePlague <= 15) {
        citizens_num /= 2;
    }
}

bool checkCommands() {
    if (acre_to_buy * acre_price > bushel_of_wheat) return false;
    if (acre_to_sell > acre_of_city) return false;
    if (bushel_to_eat > bushel_of_wheat + acre_to_sell * acre_price + acre_to_seed) return false;
    if (acre_to_seed > citizens_num * 10
        || acre_to_seed * 0.5f > bushel_of_wheat
        || acre_of_city - acre_to_sell + acre_to_buy < acre_to_seed) return false;
    return true;
}

bool loadSavedGame(int& year) {
    std::ifstream in("save_data.txt", std::ios_base::in);
    if (!in.is_open()) {
        std::cout << "Some error when loading game\n";
        return false;
    }
    else if (in.peek() == EOF)
    {
        std::cout << "There is no saved game:(\n";
        return false;
    }

    std::string str;
    std::getline(in, str);
    year = stoi(str);
    std::getline(in, str);
    died_from_starving_summary = stoi(str);
    std::getline(in, str);
    citizens_num = stoi(str);
    std::getline(in, str);
    bushel_of_wheat = stoi(str);
    std::getline(in, str);
    acre_of_city = stoi(str);
    std::getline(in, str);
    died_starving_citizens = stoi(str);
    std::getline(in, str);
    new_citizens = stoi(str);
    std::getline(in, str);
    bushel_per_acre = stoi(str);
    std::getline(in, str);
    bushel_eaten_by_rats = stoi(str);
    std::getline(in, str);
    acre_price = stoi(str);
    std::getline(in, str);
    bIsTherePlague = stoi(str);
    return true;
}

void saveGame(int& year) {

    std::ofstream out("save_data.txt");
    if (!out.is_open()) {
        std::cout << "Some error while saving game\n";
        return;
    }
    out << year << "\n";
    out << died_from_starving_summary << "\n";
    out << citizens_num << "\n";
    out << bushel_of_wheat << "\n";
    out << acre_of_city << "\n";
    out << died_starving_citizens << "\n";
    out << new_citizens << "\n";
    out << bushel_per_acre << "\n";
    out << bushel_eaten_by_rats << "\n";
    out << acre_price << "\n";
    out << bIsTherePlague;

    out.close();
    std::cout << "Game successfully saved!\n";
}

void clear_save()
{
    std::ofstream out("save_data.txt");
    if (!out.is_open()) {
        std::cout << "Some error while saving game\n";
        return;
    }
    out.clear();
    out.close();
}

void getCommands() {
    bool b_commands_are_correct = false;
    bool b_is_mistaken = false;
    while(!b_commands_are_correct) {

        if (b_is_mistaken) {
            std::cout << "\nПовелитель, подумай еще раз о своем решении!";
        }

        std::cout << "\nЧто пожелаешь, повелитель?";
        std::cout << "\nСколько акров земли повелеваешь купить? ";
        std::cin >> acre_to_buy;
        std::cout << "Сколько акров земли повелеваешь продать? ";
        std::cin >> acre_to_sell;
        std::cout << "Сколько бушелей пшеницы повелеваешь съесть? "; 
        std::cin >> bushel_to_eat;
        std::cout << "Сколько акров земли повелеваешь засеять? ";
        std::cin >> acre_to_seed;

        b_is_mistaken = true;

        if (checkCommands())
        {
           b_commands_are_correct = true;
           b_is_mistaken = false;
        }
    }
}

void printRoundNumber(int round) {
    if (round > 10) {
        std::cout << "\n=============== ЭПИЛОГ ===============\n";
        return;
    }
    std::cout << "\n=============== " << round << " РАУНД " << "===============\n";
}

void showReport(int idx) {
    printRoundNumber(idx);
    if (idx == 1) {
        std::cout << "\nЗдравствуй, повелитель!\n\t"
        "Население нашего великого города сейчас составляет " << citizens_num << " человек;\n\t"
            "В закромах города " << bushel_of_wheat << " бушелей пшеницы;\n\t"
            "Город занимает " << acre_of_city << " акров земли;\n";
    }
    else
    {
        std::cout << "\nМой повелитель, соизволь поведать тебе\n\t" << "в году " << idx - 1 << " твоего высочайшего правления\n\t";
        if (died_starving_citizens > 0) {
            std::cout << died_starving_citizens << " человек умерли с голоду\n\t";
        }
        
        if (new_citizens > 0) {
            std::cout << new_citizens << " человек прибыли в наш великий город;\n\t";
        }
        if (bIsTherePlague <= 15) {
            std::cout << "Чума уничтожила половину населения;\n\t";
        }
        std::cout << "Население города сейчас составляет " << citizens_num << " человек;\n\t"
            "Мы собрали " << bushel_per_acre * acre_to_seed << " бушелей пшеницы, по " << bushel_per_acre << " бушеля с акра;\n\t";
        if (bushel_eaten_by_rats) {
            std::cout <<"Крысы истребили " << bushel_eaten_by_rats << " бушелей пшеницы, оставив " << bushel_of_wheat << " бушеля в амбарах;\n\t";
        }
        std::cout << "Город сейчас занимает " << acre_of_city << " акров;\n\t"
            "1 акр земли стоит сейчас " << acre_price << " бушелей.\n";
    }
}

void setMark()
{   
    died_from_starving_summary = died_from_starving_summary / 10;
    acre_per_citizen = acre_of_city / citizens_num;
    if (died_from_starving_summary > 33 && acre_per_citizen < 7) {
        std::cout << "\nИз-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города."
        "\nТеперь вы вынуждены влачить жалкое существование в изгнании.\n";
    } else if (died_from_starving_summary > 10 && acre_per_citizen < 9) {
        std::cout << "\nВы правили железной рукой, подобно Нерону и Ивану Грозному."
        "\nНарод вздохнул с облегчением, и никто больше не желает видеть вас правителем.\n";
    } else if (died_from_starving_summary > 3 && acre_per_citizen < 10)
    {
        std::cout << "\nВы справились вполне неплохо, у вас, конечно, есть недоброжелатели,"
        " но многие хотели бы увидеть вас во главе города снова!\n";
    } else {
        std::cout << "\nФантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше!\n";
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(unsigned(time(0)));
    
    int year = 1;
 
    char ch = ' ';
    std::cout << "Welcome to Hammurabi game!\n"; 
    
    while (ch != 'y' && ch != 'n')
    {
        std::cout << "Do you want to load the saved game ? (y / n) ";
        std::cin >> ch;
        std::cout << "\n";
        if (ch == 'y') {
            if (!loadSavedGame(year))
                break;
        }
    }

    while (year <= 10)
    {
        showReport(year);
        ch = ' ';
        while (ch != 'y' && ch != 'n')
        {
            std::cout << "\nDo you want to save the game and take a break? (y / n) ";
            std::cin >> ch;
            if (ch == 'y') {
                saveGame(year);
                return 0;
            }
        }
        getCommands();
        update();
        if (bIsLost)
        {   
            clear_save();
            std::cout << "\nПочти половина жителей нашего города погибла от голода! Вы ужасный правитель!\n";
            return 0;
        }
        year++;
    }
    showReport(year);
    setMark();

    return 0;
}