#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "array.h"
#include "linkedList.h"
#include "doublyList.h"
#include "stack.h"
#include "Queue.h"
#include "Rbtree.h"

using namespace std;

class DBMS {
private:
    map<string, MyArray*> arrays;
    map<string, ForwardList*> flists;
    map<string, DoubleList*> dlists;
    map<string, MyStack*> stacks;
    map<string, MyQueue*> queues;
    map<string, RBTree*> trees;
    vector<string> history;

public:
    ~DBMS() {
        for (auto& p : arrays) delete p.second;
        for (auto& p : flists) delete p.second;
        for (auto& p : dlists) delete p.second;
        for (auto& p : stacks) delete p.second;
        for (auto& p : queues) delete p.second;
        for (auto& p : trees) delete p.second;
    }

    void executeQuery(const string& query, bool printResult = true, bool save = true) {
        stringstream ss(query);
        string cmd, name, arg1, arg2;
        ss >> cmd >> name >> arg1 >> arg2;
        if (cmd.empty()) return;

        char type = cmd[0];
        string action = cmd.substr(1);
        bool isModified = false;

        if (type == 'M') {
            if (!arrays[name]) arrays[name] = new MyArray();
            MyArray* arr = arrays[name];
            if (action == "CREATE") { arr->create(); isModified = true; }
            else if (action == "PUSH") { arr->push_back(arg1); isModified = true; }
            else if (action == "INSERT") { arr->insert_at(stoi(arg1), arg2); isModified = true; }
            else if (action == "GET" && printResult) cout << "-> " << arr->get(stoi(arg1)) << endl;
            else if (action == "DEL") { arr->remove_at(stoi(arg1)); isModified = true; }
            else if (action == "SET") { arr->set(stoi(arg1), arg2); isModified = true; }
            else if (action == "LEN" && printResult) cout << "-> " << arr->length() << endl;
        }
        else if (type == 'F') {
            if (!flists[name]) flists[name] = new ForwardList();
            ForwardList* fl = flists[name];
            if (action == "CREATE") { fl->create(); isModified = true; }
            else if (action == "PUSH") { if (arg2 == "front") fl->push_front(arg1); else fl->push_back(arg1); isModified = true; }
            else if (action == "INSERTAFTER") { fl->insert_after(arg1, arg2); isModified = true; }
            else if (action == "INSERTBEFORE") { fl->insert_before(arg1, arg2); isModified = true; }
            else if (action == "DEL") { fl->remove(arg1); isModified = true; }
            else if (action == "DELHEAD") { fl->pop_front(); isModified = true; }
            else if (action == "DELTAIL") { fl->pop_back(); isModified = true; }
            else if (action == "DELAFTER") { fl->remove_after(arg1); isModified = true; }
            else if (action == "DELBEFORE") { fl->remove_before(arg1); isModified = true; }
            else if (action == "GET" && printResult) cout << "-> " << (fl->find(arg1) ? "TRUE" : "FALSE") << endl;
            else if (action == "GETFIRST" && printResult) cout << "-> " << fl->get_first() << endl;
            else if (action == "GETLAST" && printResult) cout << "-> " << fl->get_last() << endl;
        }
        else if (type == 'L') {
            if (!dlists[name]) dlists[name] = new DoubleList();
            DoubleList* dl = dlists[name];
            if (action == "CREATE") { dl->create(); isModified = true; }
            else if (action == "PUSH") { if (arg2 == "front") dl->push_front(arg1); else dl->push_back(arg1); isModified = true; }
            else if (action == "INSERTAFTER") { dl->insert_after(arg1, arg2); isModified = true; }
            else if (action == "INSERTBEFORE") { dl->insert_before(arg1, arg2); isModified = true; }
            else if (action == "DEL") { dl->remove(arg1); isModified = true; }
            else if (action == "DELHEAD") { dl->pop_front(); isModified = true; }
            else if (action == "DELTAIL") { dl->pop_back(); isModified = true; }
            else if (action == "DELAFTER") { dl->remove_after(arg1); isModified = true; }
            else if (action == "DELBEFORE") { dl->remove_before(arg1); isModified = true; }
            else if (action == "GET" && printResult) cout << "-> " << (dl->find(arg1) ? "TRUE" : "FALSE") << endl;
            else if (action == "GETFIRST" && printResult) cout << "-> " << dl->get_first() << endl;
            else if (action == "GETLAST" && printResult) cout << "-> " << dl->get_last() << endl;
        }
        else if (type == 'S') {
            if (!stacks[name]) stacks[name] = new MyStack();
            MyStack* st = stacks[name];
            if (action == "CREATE") { st->create(); isModified = true; }
            else if (action == "PUSH") { st->push(arg1); isModified = true; }
            else if (action == "POP") { string val = st->pop(); if (printResult && val != "EMPTY") cout << "-> " << val << endl; isModified = true; }
            else if (action == "GET" && printResult) cout << "-> " << st->peek() << endl;
        }
        else if (type == 'Q') {
            if (!queues[name]) queues[name] = new MyQueue();
            MyQueue* q = queues[name];
            if (action == "CREATE") { q->create(); isModified = true; }
            else if (action == "PUSH") { q->push(arg1); isModified = true; }
            else if (action == "POP") { string val = q->pop(); if (printResult && val != "EMPTY") cout << "-> " << val << endl; isModified = true; }
            else if (action == "GET" && printResult) cout << "-> " << q->peek() << endl;
        }
        else if (type == 'T') {
            if (!trees[name]) trees[name] = new RBTree();
            RBTree* t = trees[name];
            if (action == "CREATE") { t->create(); isModified = true; }
            else if (action == "INSERT") { t->insert(arg1); isModified = true; }
            else if (action == "GET" && printResult) cout << "-> " << (t->find(arg1) ? "TRUE" : "FALSE") << endl;
            else if (action == "DEL") { t->remove(arg1); isModified = true; }
        }
        else if (cmd == "PRINT" && printResult) {
            if (arrays.count(name) && arrays[name]) {
                cout << "-> ";
                for (int i = 0; i < arrays[name]->length(); i++) cout << arrays[name]->get(i) << " ";
                cout << endl;
            }
            else if (flists.count(name) && flists[name]) flists[name]->print();
            else if (dlists.count(name) && dlists[name]) dlists[name]->print();
            else if (trees.count(name) && trees[name]) trees[name]->print();
            else if (stacks.count(name) && stacks[name]) stacks[name]->print();
            else if (queues.count(name) && queues[name]) queues[name]->print();
            else cout << "-> NOT FOUND" << endl;
        }

        if (isModified && save) history.push_back(query);
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const string& cmd : history) file << cmd << endl;
        file.close();
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
        while (getline(file, line)) if (!line.empty()) db.executeQuery(line, false, true);
        file.close();
    }
    if (!query.empty()) db.executeQuery(query, true, query.find("PRINT") != 0);
    if (!filename.empty()) db.saveToFile(filename);
    return 0;
}
