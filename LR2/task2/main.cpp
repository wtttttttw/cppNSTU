#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "MySet.h"

using namespace std;

class DBMS {
private:
    map<string, MySet*> sets;
    map<string, vector<string>> storage_log;

public:
    ~DBMS() {
        for (auto& p : sets) delete p.second;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return;

        string line, cmd, name, arg;
        while (getline(file, line)) {
            stringstream ss(line);
            if (ss >> cmd >> name >> arg) {
                if (!sets[name]) sets[name] = new MySet();
                if (cmd == "SETADD") {
                    sets[name]->set_add(arg);
                    storage_log[name].push_back("SETADD " + arg);
                } else if (cmd == "SETDEL") {
                    sets[name]->set_del(arg);
                    storage_log[name].push_back("SETDEL " + arg);
                }
            }
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (auto const& [name, log] : storage_log) {
            for (const string& cmd : log) {
                file << cmd.substr(0, 6) << " " << name << " " << cmd.substr(7) << "\n";
            }
        }
    }

    void executeQuery(const string& query) {
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
                storage_log[name].push_back("SETADD " + arg);
                cout << "-> OK (Added " << arg << " to " << name << ")" << endl;
            }
            else if (cmd == "SETDEL") {
                s->set_del(arg);
                storage_log[name].push_back("SETDEL " + arg);
                cout << "-> OK (Deleted " << arg << " from " << name << ")" << endl;
            }
            else if (cmd == "SET_AT") {
                cout << "-> " << (s->set_at(arg) ? "TRUE" : "FALSE") << endl;
            }
        }
        else {
            cout << "-> ERROR: Unknown command" << endl;
        }
    }
};

int main(int argc, char* argv[]) {
    string filename = "db_state.txt";
    string query = "";
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) { filename = argv[i + 1]; i++; }
        else if (arg == "--query" && i + 1 < argc) { query = argv[i + 1]; i++; }
    }

    DBMS db;
    
    db.loadFromFile(filename);

    if (!query.empty()) {
        db.executeQuery(query);
    } else {
        cout << "No query provided. Use --query \"YOUR_COMMAND\"" << endl;
        return 0;
    }

    db.saveToFile(filename);

    return 0;
}
