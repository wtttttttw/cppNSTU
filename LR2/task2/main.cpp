#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "MySet.h"

using namespace std;

class DBMS {
private:
    map<string, MySet*> sets;

public:
    ~DBMS() {
        for (auto& p : sets) delete p.second;
    }

    bool executeQuery(const string& query, bool printResult = true) {
        if (query.empty()) return false;

        stringstream ss(query);
        string cmd, name, arg;
        ss >> cmd >> name >> arg;
        if (cmd.empty()) return false;

        bool isModified = false;

        if (cmd == "SETADD") {
            if (!sets[name]) sets[name] = new MySet();
            if (sets[name]->set_add(arg)) {
                if (printResult) cout << "-> элемент добавлен" << endl;
                isModified = true; // Изменилось, нужно записать в файл
            } else {
                if (printResult) cout << "-> элемент уже есть в множестве" << endl;
            }
        }
        else if (cmd == "SETDEL") {
            if (!sets[name]) sets[name] = new MySet();
            if (sets[name]->set_del(arg)) {
                if (printResult) cout << "-> элемент удалён" << endl;
                isModified = true;
            } else {
                if (printResult) cout << "-> элемента нет, множество не изменилось" << endl;
            }
        }
        else if (cmd == "SET_AT") {
            if (!sets[name]) sets[name] = new MySet();
            if (printResult) {
                cout << "-> " << (sets[name]->set_at(arg) ? "элемент присутствует" : "элемент отсутствует") << endl;
            }
        }
        else if (cmd == "SETPRINT") {
            if (!sets[name]) sets[name] = new MySet();
            if (printResult) {
                cout << "Множество " << name << ": ";
                sets[name]->print();
            }
        }
        else {
            if (printResult) cout << "-> ERROR: Unknown command" << endl;
        }

        return isModified;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            if (!line.empty()) executeQuery(line, false);
        }
        file.close();
    }

    void appendToFile(const string& filename, const string& query) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << query << endl;
            file.close();
        }
    }
};

int main(int argc, char* argv[]) {
    string filename = "", query = "";
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) { filename = argv[i + 1]; i++; }
        else if (arg == "--query" && i + 1 < argc) { query = argv[i + 1]; i++; }
    }

    DBMS db;

    if (!filename.empty()) {
        db.loadFromFile(filename);
    }

    if (!query.empty()) {
        bool modified = db.executeQuery(query, true);
        
        if (modified && !filename.empty()) {
            db.appendToFile(filename, query);
        }
    }

    return 0;
}
