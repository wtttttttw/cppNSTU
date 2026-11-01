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
            else if (stacks.count(name) && stacks[name]) stacks[name]->print(); // <-- ДОБАВЛЕНО
            else if (queues.count(name) && queues[name]) queues[name]->print(); // <-- ДОБАВЛЕНО
            else if (trees.count(name) && trees[name]) trees[name]->print();
            else cout << "-> NOT FOUND or not supported for PRINT" << endl;
        }
