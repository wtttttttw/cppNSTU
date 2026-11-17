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

    void executeQuery(const string& query, bool printResult = true) {
        if (query.empty()) return;

        stringstream ss(query);
        string cmd, name, arg;
        ss >> cmd >> name >> arg;
        if (cmd.empty()) return;

        if (cmd == "SETADD" || cmd == "SETDEL" || cmd == "SET_AT") {
            if (!sets[name]) sets[name] = new MySet();
            MySet* s = sets[name];

            if (cmd == "SETADD") {
                s->set_add(arg);
            }
            else if (cmd == "SETDEL") {
                s->set_del(arg);
            }
            else if (cmd == "SET_AT") {
                if (printResult) {
                    cout << "-> " << (s->set_at(arg) ? "TRUE" : "FALSE") << endl;
                }
            }
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
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            if (!line.empty()) db.executeQuery(line, false);
        }
        file.close();
    }

    if (!query.empty()) db.executeQuery(query, true);

    return 0;
}
