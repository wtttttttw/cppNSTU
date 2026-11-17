#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "stack.h"
#include "LogicCalc.h"

using namespace std;

class DBMS {
private:
    map<string, MyStack<string>*> stacks;

public:
    ~DBMS() {
        for (auto& p : stacks) delete p.second;
    }

    void executeQuery(const string& query, bool printResult = true) {
        if (query.empty()) return;

        if (query.rfind("XEVAL", 0) == 0) {
            size_t pos = 5;
            while (pos < query.size() && query[pos] == ' ') pos++;
            string expr = query.substr(pos);
            int res = LogicCalc::evaluate(expr);
            if (printResult) {
                if (res < 0) cout << "-> ERROR" << endl;
                else         cout << "-> " << res << endl;
            }
            return;
        }

        stringstream ss(query);
        string cmd, name, arg;
        ss >> cmd >> name >> arg;
        if (cmd.empty()) return;

        char type = cmd[0];
        string action = cmd.substr(1);

        if (type == 'S') {
            if (!stacks[name]) stacks[name] = new MyStack<string>();
            MyStack<string>* st = stacks[name];
            if (action == "CREATE") { st->create(); }
            else if (action == "PUSH") { st->push(arg); }
            else if (action == "POP") {
                if (st->empty()) { if (printResult) cout << "-> EMPTY" << endl; }
                else { string val = st->pop(); if (printResult) cout << "-> " << val << endl; }
            }
            else if (action == "GET" && printResult) {
                if (st->empty()) cout << "-> EMPTY" << endl;
                else cout << "-> " << st->peek() << endl;
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
