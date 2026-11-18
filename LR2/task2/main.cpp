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

        if (cmd == "SETADD" || cmd == "SETDEL" || cmd == "SET_AT") {
            if (!sets[name]) sets[name] = new MySet();
            MySet* s = sets[name];

            if (cmd == "SETADD") {
                s->set_add(arg);
                if (printResult) cout << "-> OK" << endl;
                isModified = true;
            }
            else if (cmd == "SETDEL") {
                s->set_del(arg);
                if (printResult) cout << "-> OK" << endl;
                isModified = true;
            }
            else if (cmd == "SET_AT") {
                if (printResult) {
                    cout << "-> " << (s->set_at(arg) ? "TRUE" : "FALSE") << endl;
                }
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
