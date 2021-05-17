#include <iostream>
#include <fstream>
#include <ctime> // for random
#include <cstdlib> // for random
#include <vector>
#include <algorithm>
#include <clocale> // for random
#include <string>

using namespace std;

fstream questions("questions.txt");
fstream rules("rules.txt");
fstream achiv("achiv.txt");

int score = 0;
int questionCount = 23; // count of all questions in file (size-1)
int rulesCount = 0;
int record = 0; // рекорд
int numOfQuestion; // количество вопросов
vector <bool> used;

// struct
vector <pair <string, vector <string>>> allQuestions; // все вопросы из файла
vector <pair<string, string>> allRules; // все правила из файла

string tmp; // переменная для getline();

bool print_question();  // печатает вопрос
void print_hello();     // печатает приветствие
void print_menu();      // печатает меню
void print_final();     // печатает финал/экран окончания
void print_rules();     // печатает правило
void start_printing_questions(int count);
void pause();
void print_achiv();
void gameMode1(int count);
void gameMode2();
void print_mark();




// РАБОТАЕТ
void pause() {
    cout << "\n" << "Нажмите Enter, чтобы продолжить...";
    while (!getline(cin, tmp)) {
         cout << "";
    }
    getline(cin, tmp);
    cout << "\n";
    for (int i = 0; i < 80; i++) {
        cout << '/';
    }
    cout << "\n\n";
}

// РАБОТАЕТ
void print_rules() {
    string rule;

    // ввывод первого правила
    cout << endl;
    cout << allRules[0].first;
    cout << endl << endl;

    // ввывод названию правил
    for (int i = 1; i < rulesCount; i++){
      cout << i << ") " << allRules[i].first << endl << endl;
    }
    cout << "Выбери номер правила который ты хочешь подучить или -1, если хочешь выйти:" << endl;
    
    // ввод номера и вывод правила
    int userInput = 0;
    while ((userInput < 1 || userInput >= rulesCount) && userInput != -1) {
      cin >> userInput;
      if (userInput < 1 || userInput >= rulesCount){
        cout << "Нет такого вопроса. Введи другой" << endl;
      }
    }
    cout << endl;

    if (userInput == -1) {
        cout << "Удачи!" << endl;
        pause();
        print_menu();
    }
    else if (userInput > 0 && userInput < rulesCount){
      cout << allRules[userInput].first << endl << allRules[userInput].second << endl;
    }

    pause();
    print_menu();
}

void print_mark() {
    double s = (double) score;
    double q = (double) numOfQuestion;

    double m = s / q;

    if (m >= 0.9) {
        cout << "Твоя оценка - 5" << endl;
        cout << "Молодец!";
    } else if (m >= 0.65) {
        cout << "Твоя оценка - 4";
    } else if (m > 0.4) {
        cout << "Твоя оценка - 3";
    } else {
        cout << "Твоя оценка - 2" << endl;
        cout << "Советую подучить правила";
    }
    record = max(record, score);
    cout << endl;
    pause();
    print_menu();
}

// печатает приветствие
void print_hello() {
    cout << "Привет! Тебе надо писать НОМЕР правильного варианта ответа, набрав таким образом как можнно больше очков подряд." << "\n";


    // заполняем массив вопросов
    string s;
    string a, b, c;

    for (int i = 0; i < questionCount; i++) {
        getline(questions, s);
        getline(questions, s);
        questions >> a >> b >> c;
        // cout << s << " " << a << " " << b << " " << c << endl;
        allQuestions.push_back({s, {a, b, c}});
    }


    // заполняем массив правил
    rulesCount = 5;
    // getline(rules, s);
    for (int i = 0; i < rulesCount; i++){
        getline(rules, s);
        getline(rules, a);
        allRules.push_back({s, a});
        // cout << s << endl << a << endl << endl;
    }

    pause();
    print_menu();
}

// menu
void print_menu() {
    cout << "Нажми 1, если хочешь проверить свои знания." << "\n";
    cout << "Нажми 2, чтобы подучить правила." << "\n";
    cout << "Нажми 3, чтобы посмотореть свой рекорд." << "\n";
    cout << "Нажми 4, если хочешь выйти." << endl;
    string n;
    cin >> n;
    while (n != "1" && n != "2" && n != "3"&& n != "4" && n != "007" && n != "kostyaloch") {
        cout << "Неправильный ввод" << "\n";
        cin >> n;
    }
    if (n == "1") {
        cout << "Выбери режим:" << endl;
        cout << "1. Вопросы на оценку" << endl;
        cout << "2. \"Бесконечный\" режим" << endl;
 

        while (true) {
            string chose;
            cin >> chose;

            if (chose == "1"){
                cout << "Ты выбрал вопросы на оценку." << endl;
                cout << "Тебе будет предложено несколько вопросов, по окончанию ответа на которые ты узнаешь свою оценку по пятибальной шкале." << endl;

                while (true) {
                    cout << endl << "Сколько ты хочешь вопросов?" << "\n";
                    cin >> numOfQuestion;
                    if (numOfQuestion > 0 && numOfQuestion <= questionCount) {
                        gameMode1(numOfQuestion);
                    } else {
                        cout << "Количество вопросов должно быть больше 0 и не больше, чем 20" << "\n";
                        continue;
                    }
                }
                break;
            } else if (chose == "2"){
                cout << endl << "Ты выбрал бесконечный режим!" << endl;
                cout << "Твоя задача отвечать правильно на все вопросы" << endl;
                cout << "Неправильный ответ - ты проиграл" << endl;

                gameMode2();
                break;
            } else {
                cout << "Выбери 1 или 2" << endl;
            }
        }
    } else if (n == "2") {
        print_rules();
    } else if (n == "3") {
        print_achiv();
    } else if (n == "4") {
        cout << "Удачи!" << endl;
        exit(0);
    } else if (n == "007") {
        cout << " .-.  .-.  --..::==" << endl;
        cout << "(   )(   )  /\"" << endl;
        cout << " '-'  '-'  /" << endl;
        pause();
        print_menu();
    } else if (n == "kostyaloch"){
        score = 1000000000;
        print_final();
        score = 0;
    }
}

void print_final() {
    cout << endl;
    
    if (score == numOfQuestion) {
        cout << "Ты достиг превосходства!" << "\n";
    } else if (score * 2 <= numOfQuestion) {
        cout << "Надо бы подтянуть знания!" << "\n";
    } else {
        cout << "Поздравляем!" << "\n";
    }
    if (score == 0) {
        cout << "Учи правила!" << "\n";
    } else if (score % 10 == 0) {
        cout << "Ты набрал: " << score << " очков!" << "\n";
    } else if (score % 10 == 1)
        cout << "Ты набрал: " << score << " очко!" << "\n";
    else if (score % 10 < 5)
        cout << "Ты набрал: " << score << " очка!" << "\n";
    else
        cout << "Ты набрал: " << score << " очков!" << "\n";
    
    pause();
    if (score > record) {
        record = score;
    }
    score = 0;
    print_menu();
}

// print a question
bool print_question(){
    bool isAnsTrue = false;
    cout << "\n";
    cout << "Какой правильный вариант ответа?" << "\n";

    // создаем рандомный сид
    srand(time(nullptr));

// vector <pair <string, vector <char>>> allQuestions();


    // рандомное число от 0) questionCount
    int randomQ = rand() % questionCount + 0;

    while (!used[randomQ]) {
        randomQ = rand() % questionCount + 0;
    }
    used[randomQ] = 0;

    // выводим рандомный вопрос
    cout << allQuestions[randomQ].first << endl;
    
    int randomA = rand() % 3 + 0;

    int setAnswer = 0;
    if (randomA == 0) {
        cout << "1) ";
        cout << allQuestions[randomQ].second[0] << "   ";
        cout << "2) ";
        cout << allQuestions[randomQ].second[1] << "   ";
        cout << "3) ";
        cout << allQuestions[randomQ].second[2] << "";
        setAnswer = 1;
    } else if (randomA == 1) {
      cout << "1) ";
        cout << allQuestions[randomQ].second[1] << "   ";
        cout << "2) ";
        cout << allQuestions[randomQ].second[2] << "   ";
        cout << "3) ";
        cout << allQuestions[randomQ].second[0] << "";
        setAnswer = 3;
    } else if (randomA == 2) {
      cout << "1) ";
        cout << allQuestions[randomQ].second[2] << "   ";
        cout << "2) ";
        cout << allQuestions[randomQ].second[0] << "   ";
        cout << "3) ";
        cout << allQuestions[randomQ].second[1] << "";
        setAnswer = 2;
    }
    cout << endl;

    int userAns;
    // cout << "SA = " << setAnswer << endl;
    cin >> userAns;
    
    if (userAns == setAnswer) {
        cout << "Правильно!" << endl;
        isAnsTrue = true;
        score++;
    } else {
        isAnsTrue = false;
        cout << "Неправильно." << endl;
        cout << "Правильный ответ - " << allQuestions[randomQ].second[0] << endl;
        //print_final();
    }
    return isAnsTrue;
}

// режим с ограниченным количеством вопросов
void gameMode1(int count){
    score = 0;
    used = vector <bool> (questionCount, 1);
    for (int i = 0; i < count; i++){
        print_question();
    }
    print_mark();
}

void gameMode2(){ // режим выживания

    // создаем рандомный сид
    srand(time(nullptr));

    // рандомное число от 0 - questionCount
    int randomQ = rand() % 3 + 0;

    used = vector <bool> (questionCount, 1);
    bool cor = false;
    score = 0;
    numOfQuestion = questionCount - randomQ;
    for (int c = 0; c < numOfQuestion; c++){
        cor = print_question();
        if (!cor){
            print_final();
        }
    }
    cout << endl << "Можешь удалять программу, ты безупречен..." << endl;
    print_final();
}

void print_achiv() {
    if (record == 0) {
        cout << "Ты ещё не поставил свой рекорд!";
        pause();
        print_menu();
        return;
    } else if (record % 10 == 0) {
        cout << "Твой рекорд - " << record << " очков подряд!" << "\n";
    } else if (record % 10 == 1) {
        cout << "Твой рекорд - " << record << " очко подряд!" << "\n";
    } else if (record % 10 < 5) {
        cout << "Твой рекорд - " << record << " очка подряд!" << "\n";
    } else {
        cout << "Твой рекорд - " << record << " очков подряд!" << "\n";
    }
    pause();
    print_menu();
}

int main() {
    setlocale(LC_ALL,"Russian");
    
    for (int i = 0; i < 1e3; i++) cout << endl;
    

    if (!(questions.is_open())) {
        cout << "Не могу найти файл с вопросами(";
        return 0;
    }

    if (!(rules.is_open())){
        cout << "Не могу найти файл с правилами(";
        return 0;
    }

    print_hello();
}

