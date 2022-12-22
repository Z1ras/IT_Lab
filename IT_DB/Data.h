#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <list>
#include <tuple>
#include <map>
#include <unordered_map>
#include <Windows.h>

using namespace std;

enum Type
{
    Integer,
    Real,
    Char,
    String,
    Time,
    TimeInvl
};

Type get_Type(string& name);

string get_strType(Type type);


class Value
{
public:
    int integer_value;
    double real_value;
    char char_value;
    string string_value;
    unsigned time_value;
    pair<unsigned, unsigned> time_interval_value;
    Type type;

    Value(int integer_value) : integer_value(integer_value) { type = Type::Integer; }
    Value(double real_value) : real_value(real_value) { type = Type::Real; }
    Value(char char_value) : char_value(char_value) { type = Type::Char; }
    Value(string string_value) : string_value(string_value) { type = Type::String; }
    Value(unsigned time_value) : time_value(time_value) { type = Type::Time; }
    Value(pair<unsigned, unsigned> time_interval_value) : time_interval_value(time_interval_value) { type = Type::TimeInvl; }

    string value_to_time(unsigned _time_value);

    void print_value();

    string get_strValue();

    bool operator< (const Value& v) const {
        if (this->type == v.type) {
            if (this->type == Type::Integer)
                return this->integer_value < v.integer_value;
            else if (this->type == Type::Real)
                return this->real_value < v.real_value;
            else if (this->type == Type::Char)
                return this->char_value < v.char_value;
            else if (this->type == Type::String)
                return this->string_value < v.string_value;
            else if (this->type == Type::Time)
                return this->time_value < v.time_value;
            else if (this->type == Type::TimeInvl)
                return (this->time_interval_value.first - this->time_interval_value.second) < (v.time_interval_value.first - v.time_interval_value.second);
        }

    }
};


class Column
{
public:
    string name;
    Type t;
    vector<Value> column;

    Column(string name, Type t, vector<Value> column) :name(name), t(t), column(column) {}

    void add_empty_el();

    void change_cell(int number_row, Value new_value)
    {
        column[number_row] = new_value;
    }

    int size()
    {
        return column.size();
    }

};

class Table
{
public:
    string name;
    vector<Column> table;
    Table()
    {
        vector<Value> empty_col;
        table.push_back({ "id", Type::Integer, empty_col }); //перша колонка id
    }
    Table(string name) :name(name)
    {
        vector<Value> empty_col;
        table.push_back({ "id", Type::Integer, empty_col }); //перша колонка id
    }

    void addcol(string name, Type t, int size);

    void addcol(string mame, Type t, vector<Value> column);

    void change_cell(int number_col, int number_row, Value new_value)
    {
        table[number_col].change_cell(number_row, new_value);
    }

    void addrow();

    void print_table();

    vector<Column> get_table() { return table; }

    int get_sizeN();
    int get_sizeM();

    Type get_ColumnType(int M) { return table[M].t; }

    void sort(int M, bool ascending);

    void deletecol(int M);

    void deleterow(int N);
};


struct Database_Manager
{
    unordered_map<string, Table> tables;
    string chosen_table;
    bool table_is_chosen = 0;
    int state_menu;
    int state_table_menu;

    void menu()
    {
        cout << "Вибір дії: " << endl
            << "(0) Вихід з програми" << endl
            << "(1) Читати БД з файлу" << endl
            << "(2) Вибрати таблицю" << endl
            << "(3) Зберегти БД у файл" << endl
            << "(4) Створити таблицю" << endl
            << "(5) Видалити таблицю" << endl;
        cin >> state_menu;
    }

    void table_menu()
    {
        cout << "Вибір дії: " << endl
            << "(0) Вийти з таблиці" << endl
            << "(1) Відобразити таблицю" << endl
            << "(2) Додати порожній рядок" << endl
            << "(3) Додати порожню колонку" << endl
            << "(4) Додати та ініціалізувати колонку" << endl
            << "(5) Змінити значення клітинки" << endl
            << "(6) Сортувати таблицю за колонкою" << endl
            << "(7) Видалити колонку" << endl
            << "(8) Видалити рядок" << endl;
        cin >> state_table_menu;
    }

    void run();

    void run_table();
};