#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
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

public:
    ~DBMS() {
        for (auto& p : arrays) { delete p.second; }
        for (auto& p : flists) { delete p.second; }
        for (auto& p : dlists) { delete p.second; }
        for (auto& p : stacks) { delete p.second; }
        for (auto& p : queues) { delete p.second; }
        for (auto& p : trees) { delete p.second; }
    }

    void executeQuery(const string& query) {
        stringstream ss(query);
        string cmd, name, arg1, arg2;
        ss >> cmd >> name >> arg1 >> arg2;

        if (cmd.empty()) return;
        char type = cmd[0];
        string action = cmd.substr(1);

        // --- ÌÀÑÑÈÂ ---
        if (type == 'M') {
            if (!arrays[name]) arrays[name] = new MyArray();
            MyArray* arr = arrays[name];
            if (action == "CREATE") arr->create();
            else if (action == "PUSH") arr->push_back(arg1);
            else if (action == "INSERT") arr->insert_at(stoi(arg1), arg2);
            else if (action == "GET") cout << "-> " << arr->get(stoi(arg1)) << endl;
            else if (action == "DEL") arr->remove_at(stoi(arg1));
            else if (action == "SET") arr->set(stoi(arg1), arg2);
            else if (action == "LEN") cout << "-> " << arr->length() << endl;
        }
        // --- ÎÄÍÎÑÂßÇÍÛÉ ÑÏÈÑÎÊ ---
        else if (type == 'F') {
            if (!flists[name]) flists[name] = new ForwardList();
            ForwardList* fl = flists[name];
            if (action == "CREATE") fl->create();
            else if (action == "PUSH") {
                if (arg2 == "front") fl->push_front(arg1);
                else fl->push_back(arg1);
            }
            else if (action == "INSERTAFTER") fl->insert_after(arg1, arg2);
            else if (action == "INSERTBEFORE") fl->insert_before(arg1, arg2);
            else if (action == "DEL") fl->remove(arg1);
            else if (action == "GET") cout << "-> " << (fl->find(arg1) ? "TRUE" : "FALSE") << endl;
            else if (action == "GETFIRST") cout << "-> " << fl->get_first() << endl;
            else if (action == "GETLAST") cout << "-> " << fl->get_last() << endl;
        }
        // --- ÄÂÓÑÂßÇÍÛÉ ÑÏÈÑÎÊ ---
        else if (type == 'L') {
            if (!dlists[name]) dlists[name] = new DoubleList();
            DoubleList* dl = dlists[name];
            if (action == "CREATE") dl->create();
            else if (action == "PUSH") {
                if (arg2 == "front") dl->push_front(arg1);
                else dl->push_back(arg1);
            }
            else if (action == "INSERTAFTER") dl->insert_after(arg1, arg2);
            else if (action == "INSERTBEFORE") dl->insert_before(arg1, arg2);
            else if (action == "DEL") dl->remove(arg1);
            else if (action == "GET") cout << "-> " << (dl->find(arg1) ? "TRUE" : "FALSE") << endl;
            else if (action == "GETFIRST") cout << "-> " << dl->get_first() << endl;
            else if (action == "GETLAST") cout << "-> " << dl->get_last() << endl;
        }
        // --- ÑÒÅÊ ---
        else if (type == 'S') {
            if (!stacks[name]) stacks[name] = new MyStack();
            MyStack* st = stacks[name];
            if (action == "CREATE") st->create();
            else if (action == "PUSH") st->push(arg1);
            else if (action == "POP") cout << "-> " << st->pop() << endl;
            else if (action == "GET") cout << "-> " << st->peek() << endl; // SGET
        }
        // --- Î×ÅÐÅÄÜ ---
        else if (type == 'Q') {
            if (!queues[name]) queues[name] = new MyQueue();
            MyQueue* q = queues[name];
            if (action == "CREATE") q->create();
            else if (action == "PUSH") q->push(arg1);
            else if (action == "POP") cout << "-> " << q->pop() << endl;
            else if (action == "GET") cout << "-> " << q->peek() << endl; // QGET
        }
        // --- ÄÅÐÅÂÎ ---
        else if (type == 'T') {
            if (!trees[name]) trees[name] = new RBTree();
            RBTree* t = trees[name];
            if (action == "CREATE") t->create();
            else if (action == "INSERT") t->insert(arg1);
            else if (action == "GET") cout << "-> " << (t->find(arg1) ? "TRUE" : "FALSE") << endl;
            else if (action == "DEL") t->remove(arg1);
        }
        // --- PRINT ---
        else if (cmd == "PRINT") {
            if (arrays.count(name) && arrays[name]) {
                MyArray* arr = arrays[name];
                cout << "-> ";
                for (int i = 0; i < arr->length(); i++) cout << arr->get(i) << " ";
                cout << endl;
            }
            else if (flists.count(name) && flists[name]) flists[name]->print();
            else if (dlists.count(name) && dlists[name]) dlists[name]->print();
            else if (trees.count(name) && trees[name]) trees[name]->print();
            else cout << "-> NOT FOUND or not supported for PRINT" << endl;
        }
        else {
            cout << "Unknown command: " << cmd << endl;
        }
    }
};

int main(int argc, char* argv[]) {
    string filename = "";
    string query = "";

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
            if (!line.empty()) {
                if (line.find("TINSERT") == 0) {
                    stringstream ss(line);
                    string c, n;
                    ss >> c >> n;
                    string key, color;
                    while (ss >> key >> color) db.executeQuery("TINSERT " + n + " " + key);
                } else {
                    db.executeQuery(line);
                }
            }
        }
        file.close();
    }

    if (!query.empty()) {
        db.executeQuery(query);

        if (!filename.empty()) {
            ofstream file(filename, ios::app);
            file << query << endl;
            file.close();
        }
    }

    return 0;
}
