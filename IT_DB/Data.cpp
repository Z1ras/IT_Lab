#include "Data.h"


Type get_Type(string& name)
{
    if (name == "Integer")
        return Type::Integer;
    else if (name == "Real")
        return Type::Real;
    else if (name == "Char")
        return Type::Char;
    else if (name == "String")
        return Type::String;
    else if (name == "Time")
        return Type::Time;
    else if (name == "TimeInvl")
        return Type::TimeInvl;
}

string get_strType(Type type)
{
    if (type == Type::Integer)
        return "Integer";
    else if (type == Type::Real)
        return "Real";
    else if (type == Type::Char)
        return "Char";
    else if (type == Type::String)
        return "String";
    else if (type == Type::Time)
        return "Time";
    else if (type == Type::TimeInvl)
        return "TimeInvl";
}

Value ValueInit(stringstream& ss, string col_type)
{
    if (col_type == "Integer")
    {
        int temp;
        ss >> temp;
        Value temp_V(temp);
        return temp_V;
    }
    else if (col_type == "Real")
    {
        double temp;
        ss >> temp;
        Value temp_V(temp);
        return temp_V;
    }
    else if (col_type == "Char")
    {
        char temp;
        ss >> temp;
        Value temp_V(temp);
        return temp_V;
    }
    else if (col_type == "String")
    {
        Value temp_V(ss.str());
        return temp_V;
    }
    else if (col_type == "Time")
    {
        unsigned temp;
        ss >> temp;
        Value temp_V(temp);
        return temp_V;
    }
    else if (col_type == "TimeInvl")
    {
        unsigned temp1, temp2;
        ss >> temp1 >> temp2;
        pair<unsigned, unsigned> temp = make_pair(temp1, temp2);
        Value temp_V(temp);
        return temp_V;
    }
    else
    {
        cout << "Некоректний тип!";
    }
}

string Value::value_to_time(unsigned _time_value)
{
    stringstream ss;
    unsigned h = _time_value / 3600;
    ss << h;
    ss << ":";
    _time_value -= (_time_value / 3600) * 3600;
    unsigned m = _time_value / 60;
    ss << m; 
    ss << ":";
    _time_value -= (_time_value / 60) * 60;
    ss << _time_value;
    return ss.str();
}

void Value::print_value()
{
    if (type == Type::Integer)
        cout << integer_value << "\t";
    else if (type == Type::Real)
        cout << real_value << "\t";
    else if (type == Type::Char)
        cout << char_value << "\t";
    else if (type == Type::String)
        cout << string_value << "\t";
    else if (type == Type::Time)
        cout << value_to_time(time_value) << "\t";
    else if (type == Type::TimeInvl)
        cout << value_to_time(time_interval_value.first) + "-" + value_to_time(time_interval_value.second) << "\t";
}

string Value::get_strValue()
{
    stringstream ss;
    if (type == Type::Integer)
    {
        ss << integer_value;
        return ss.str();
    }
    else if (type == Type::Real)
    {
        ss << real_value;
        return ss.str();
    }
    else if (type == Type::Char)
    {
        ss << char_value;
        return ss.str();
    }
    else if (type == Type::String)
    {
        ss << string_value;
        return ss.str();
    }
    else if (type == Type::Time)
    {
        ss << time_value;
        return ss.str();
    }
    else if (type == Type::TimeInvl)
    {
        ss << time_interval_value.first << " " << time_interval_value.second;
        return ss.str();
    }
}

void Column::add_empty_el()
{
    if (t == Type::Integer) column.push_back(Value(0));
    if (t == Type::Real) column.push_back(Value(0.0));
    if (t == Type::Char) column.push_back(Value('0'));
    if (t == Type::String) column.push_back(Value(""));
    if (t == Type::Time) column.push_back(Value((unsigned)0));
    if (t == Type::TimeInvl) column.push_back(Value(make_pair(0, 0)));
}

void Table::addcol(string name, Type t, int size)
{
    vector<Value> empty_col;
    for (int i = 0; i < size; i++) {
        empty_col.push_back(NULL);
    }
    Column temp{ name, t, empty_col };
    table.push_back(temp);
}

void Table::addcol(string name, Type t, vector<Value> column)
{
    if (column.size() > table[0].column.size())
    {
        int max = -1; //знаходимо максимальний id й доіндексовуємо
        for (int i = 0; i < table[0].column.size(); i++)
            if (max < table[0].column[i].integer_value) max = table[0].column[i].integer_value;
        int odds = column.size() - table[0].column.size();
        for (int i = 1; i <= odds; i++)
            table[0].column.push_back(Value(max + i));
    }
    Column temp{ name, t, column };
    table.push_back(temp);
}

void Table::addrow()
{
    for (Column& col : table)
    {
        col.add_empty_el();
    }

    int max = -1; //знаходимо максимальний id серед рядків й індексуємо новий рядок значенням max+1
    for (int i = 0; i < table[0].column.size() - 1; i++)
        if (max < table[0].column[i].integer_value) max = table[0].column[i].integer_value;
    table[0].change_cell(table[0].column.size() - 1, Value(max + 1));
}

void Table::print_table()
{
    cout << name;
    cout << "\n";
    for (int j = 1; j < table.size(); j++)
        cout << table[j].name + "\t";
    cout << "\n";
    for (int j = 1; j < table.size(); j++)
        cout << get_strType(table[j].t) + "\t";
    cout << "\n";
    for (Value i : table[0].column)
    {
        for (int j = 1; j < table.size(); j++)
        {
            table[j].column[i.integer_value].print_value();
        }
        cout << "\n";
    }
}

int Table::get_sizeN()
{
    int N = table[0].size();
    for (auto i : table)
    {
        if (N < i.size())
        {
            N = i.size();
            cout << "Таблиця недоіндексована!";
        }
    }
    return N;
}

int Table::get_sizeM()
{
    int M = table.size() - 1;
    return M;
}

void Table::sort(int M, bool ascending)
{
    Column temp = table[M];
    multimap < Value, int > temp_map;
    for (int i = 0; i < temp.size(); i++) {
        temp_map.insert({temp.column[i], i});
    }
    vector<Value> temp_id;
    if (ascending)
        for (multimap<Value, int>::iterator it = temp_map.begin(); it != temp_map.end(); it++) {
            Value temp_Value(it->second);
            temp_id.push_back(temp_Value);
        }
    else
        for (auto it = temp_map.rbegin(); it != temp_map.rend(); it++) {
            Value temp_Value(it->second);
            temp_id.push_back(temp_Value);
        }
    table[0].column = temp_id;
}

void Table::deletecol(int M)
{
    table.erase(table.begin() + M);
}

void Table::deleterow(int N)
{
    int actual_N = table[0].column[N].integer_value;
    for (int i = 1; i < table.size(); i++) {
        table[i].column.erase(table[i].column.begin() + actual_N);
    }
    for (auto& i : table[0].column) {
        if (i.integer_value > actual_N)
            i.integer_value--;
    }
    table[0].column.erase(table[0].column.begin() + N);
}


void Database_Manager::run()
{
    menu();
    switch (state_menu)
    {
    case 0:
    {

    }
    case 1:
    {
        string file_name;
        string line;
        cout << "Файл для зчитування\n";
        cin >> file_name;
        ifstream file(file_name);
        if (file.is_open())
        {
            while (!file.eof())
            {
                string table_name;
                getline(file, table_name);
                if (table_name == "") break;
                Table table(table_name);
                getline(file, line);
                int num_of_rows = stoi(line);
                getline(file, line);
                int num_of_cols = stoi(line);
                for (int i = 0; i < num_of_cols+1; i++)
                {
                    string col_name;
                    getline(file, col_name);
                    string col_type;
                    getline(file, col_type);
                    Type type = get_Type(col_type);
                    vector<Value> column;
                    for (int j = 0; j < num_of_rows; j++)
                    {
                        stringstream ss;
                        getline(file, line);
                        ss << line;
                        Value temp = ValueInit(ss, col_type);
                        column.push_back(temp);
                    }
                    table.addcol(col_name, type, column);
                }
                table.deletecol(0);
                tables[table_name] = table;
            }
        }
        file.close();
        break;
        /////////////////////
    }
    case 2:
    {
        run_table();
        break;
        /////////////////////
    }
    case 3:
    {
        string file_name;
        string line;
        cout << "Файл для збереження\n";
        cin >> file_name;
        ofstream file(file_name);
        if (file.is_open())
        {
            for (auto table : tables)
            {
                file << table.first << endl;
                auto _table = table.second.get_table();
                file << _table[0].size() << endl;
                file << _table.size() - 1 << endl;
                for (auto col : _table)
                {
                    file << col.name << endl;
                    file << get_strType(col.t) << endl;
                    for (auto value : col.column)
                    {
                        file << value.get_strValue() << endl;
                    }
                }
            } 
        }
        file.close();
        break;
        /////////////////////
    }
    case 4:
    {
        string table_name;
        cout << "Назва таблиці\n";
        cin >> table_name;
        Table table(table_name);
        tables[table_name] = table;
        break;
        /////////////////////
    }
    case 5:
    {
        string table_name;
        cout << "Назва таблиці, яку треба видалити\n";
        cin >> table_name;
        auto it = tables.find(table_name);
        tables.erase(it);
        break;
        /////////////////////
    }
    }
}

void Database_Manager::run_table()
{
    if (!table_is_chosen) {
        cout << "Введіть назву таблиці" << endl;
        cin >> chosen_table;
    }
    Table table = tables[chosen_table];
    table_is_chosen = true;
    table_menu();
    switch (state_table_menu)
    {
    case 0:
    {
        table_is_chosen = false;
        break;
        /////////////////////
    }
    case 1:
    {
        table.print_table();
        tables[chosen_table] = table;
        run_table();
        break;
        /////////////////////
    }
    case 2:
    {
        table.addrow();
        tables[chosen_table] = table;
        table.print_table();
        run_table();
        break;
        /////////////////////
    }
    case 3:
    {
        cout << "Введіть назву колонки: ";
        string col_name;
        cin >> col_name;
        cout << "Введіть тип колонки: ";
        string type;
        cin >> type;
        Type t = get_Type(type);
        int col_size = table.get_sizeN();
        table.addcol(col_name, t, col_size);
        table.print_table();
        tables[chosen_table] = table;
        run_table();
        break;
        /////////////////////
    }
    case 4:
    {
        cout << "Введіть назву колонки: ";
        string col_name;
        cin >> col_name;
        cout << "Введіть тип колонки: ";
        string col_type;
        cin >> col_type;
        Type t = get_Type(col_type);
        vector<Value> column;
        cout << "Введіть значення колонки: \n";
        for (int i = 0; i < table.get_sizeN(); i++)
        {
            stringstream ss;
            string line;
            if (i==0) cin.ignore();
            getline(cin, line);
            ss << line;
            Value temp = ValueInit(ss, col_type);
            column.push_back(temp);
        }
        table.addcol(col_name, t, column);
        table.print_table();
        tables[chosen_table] = table;
        run_table();
        break;
        /////////////////////
    }
    case 5:
    {
        int N, M;
        cout << "Введіть номер комірки (N, M >=1):";
        while (true)
        {
            cin >> N >> M;
            if ((N <= table.get_sizeN()) && (M <= table.get_sizeM()))
                break;
            cout << "Вихід за межі таблиці! Оберіть корекнту комірку (N, M >=1):";
        }
        stringstream ss;
        string line;
        cin.ignore();
        getline(cin, line);
        ss << line;
        Type t = table.get_ColumnType(M);
        string type = get_strType(t);
        Value temp = ValueInit(ss, type);
        table.change_cell(M, N - 1, temp);
        table.print_table();
        tables[chosen_table] = table;
        run_table();
        break;
        /////////////////////
    }
    case 6:
    {
        int M;
        cout << "Оберіть номер колонки (M >= 1):";
        while (true)
        {
            cin >> M;
            if (M <= table.get_sizeM())
                break;
            cout << "Вихід за межі таблиці! Оберіть корекнту колонку (M >= 1):";
        }
        bool ascending;
        cout << "За зростанням чи за спаданням? (true/fasle)";
        cin >> ascending;
        table.sort(M, ascending);
        tables[chosen_table] = table;
        table.print_table();
        run_table();
        break;
        /////////////////////
    }
    case 7:
    {
        int M;
        cout << "Оберіть номер колонки (M >= 1):";
        while (true)
        {
            cin >> M;
            if (M <= table.get_sizeM())
                break;
            cout << "Вихід за межі таблиці! Оберіть корекнту колонку (M >= 1):";
        }
        table.deletecol(M);
        tables[chosen_table] = table;
        table.print_table();
        run_table();
        break;
        /////////////////////
    }    
    case 8:
    {
        int N;
        cout << "Оберіть номер рядка (N >= 1):";
        while (true)
        {
            cin >> N;
            if (N <= table.get_sizeN())
                break;
            cout << "Вихід за межі таблиці! Оберіть корекнтий рядок (N >= 1):";
        }
        table.deleterow(N - 1);
        tables[chosen_table] = table;
        table.print_table();
        run_table();
        break;
        /////////////////////
    }
    }
}