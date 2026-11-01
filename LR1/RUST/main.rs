mod array;
mod linked_list;
mod doubly_list;
mod stack;
mod queue;

use std::collections::HashMap;
use std::env;
use std::fs::{OpenOptions, File};
use std::io::{self, BufRead, Write};

use array::MyArray;
use linked_list::ForwardList;
use doubly_list::DoubleList;
use stack::MyStack;
use queue::MyQueue;

struct DBMS {
    arrays: HashMap<String, MyArray>,
    flists: HashMap<String, ForwardList>,
    dlists: HashMap<String, DoubleList>,
    stacks: HashMap<String, MyStack>,
    queues: HashMap<String, MyQueue>,
}

impl DBMS {
    fn new() -> Self {
        DBMS {
            arrays: HashMap::new(), flists: HashMap::new(), dlists: HashMap::new(),
            stacks: HashMap::new(), queues: HashMap::new(),
        }
    }

    fn execute(&mut self, query: &str, load: bool) {
        let mut p = query.split_whitespace();
        let cmd = p.next().unwrap_or("");
        if cmd.is_empty() { return; }
        let name = p.next().unwrap_or("");
        let a1 = p.next().unwrap_or("");
        let a2 = p.next().unwrap_or("");
        let action = &cmd[1..];

        match cmd.chars().next().unwrap() {
            'M' => {
                let arr = self.arrays.entry(name.to_string()).or_insert_with(MyArray::new);
                match action {
                    "CREATE" => arr.create(),
                    "PUSH" => arr.push_back(a1.to_string()),
                    "INSERT" => if let Ok(i) = a1.parse::<usize>() { arr.insert_at(i, a2.to_string()) },
                    "GET" => if !load { if let Ok(i) = a1.parse::<usize>() { println!("-> {}", arr.get(i)) } },
                    "DEL" => if let Ok(i) = a1.parse::<usize>() { arr.remove_at(i) },
                    "SET" => if let Ok(i) = a1.parse::<usize>() { arr.set(i, a2.to_string()) },
                    "LEN" => if !load { println!("-> {}", arr.length()) },
                    _ => {}
                }
            }
            'F' => {
                let fl = self.flists.entry(name.to_string()).or_insert_with(ForwardList::new);
                match action {
                    "CREATE" => fl.create(),
                    "PUSH" => if a2 == "front" { fl.push_front(a1.to_string()) } else { fl.push_back(a1.to_string()) },
                    "INSERTAFTER" => fl.insert_after(a1.to_string(), a2.to_string()),
                    "INSERTBEFORE" => fl.insert_before(a1.to_string(), a2.to_string()),
                    "DEL" => fl.remove(a1.to_string()),
                    "GET" => if !load { println!("-> {}", if fl.find(a1.to_string()) { "TRUE" } else { "FALSE" }) },
                    "GETFIRST" => if !load { println!("-> {}", fl.get_first()) },
                    "GETLAST" => if !load { println!("-> {}", fl.get_last()) },
                    _ => {}
                }
            }
            'L' => {
                let dl = self.dlists.entry(name.to_string()).or_insert_with(DoubleList::new);
                match action {
                    "CREATE" => dl.create(),
                    "PUSH" => if a2 == "front" { dl.push_front(a1.to_string()) } else { dl.push_back(a1.to_string()) },
                    "INSERTAFTER" => dl.insert_after(a1.to_string(), a2.to_string()),
                    "INSERTBEFORE" => dl.insert_before(a1.to_string(), a2.to_string()),
                    "DEL" => dl.remove(a1.to_string()),
                    "GET" => if !load { println!("-> {}", if dl.find(a1.to_string()) { "TRUE" } else { "FALSE" }) },
                    "GETFIRST" => if !load { println!("-> {}", dl.get_first()) },
                    "GETLAST" => if !load { println!("-> {}", dl.get_last()) },
                    _ => {}
                }
            }
            'S' => {
                let st = self.stacks.entry(name.to_string()).or_insert_with(MyStack::new);
                match action {
                    "CREATE" => st.create(),
                    "PUSH" => st.push(a1.to_string()),
                    "POP" => if !load { println!("-> {}", st.pop()) },
                    "GET" => if !load { println!("-> {}", st.peek()) },
                    _ => {}
                }
            }
            'Q' => {
                let q = self.queues.entry(name.to_string()).or_insert_with(MyQueue::new);
                match action {
                    "CREATE" => q.create(),
                    "PUSH" => q.push(a1.to_string()),
                    "POP" => if !load { println!("-> {}", q.pop()) },
                    "GET" => if !load { println!("-> {}", q.peek()) },
                    _ => {}
                }
            }
            _ => {
                if cmd == "PRINT" && !load {
                    if let Some(a) = self.arrays.get(name) {
                        print!("-> "); for i in 0..a.length() { print!("{} ", a.get(i)); } println!();
                    } else if let Some(f) = self.flists.get(name) { f.print(); }
                    else if let Some(d) = self.dlists.get(name) { d.print(); }
                    else if let Some(s) = self.stacks.get(name) { s.print(); }
                    else if let Some(q) = self.queues.get(name) { q.print(); }
                    else { println!("-> NOT FOUND"); }
                }
            }
        }
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let (mut file, mut query) = (String::new(), String::new());
    let mut i = 1;
    while i < args.len() {
        if args[i] == "--file" { file = args[i+1].clone(); i += 2; }
        else if args[i] == "--query" { query = args[i+1].clone(); i += 2; }
        else { i += 1; }
    }

    let mut db = DBMS::new();
    if !file.is_empty() {
        if let Ok(f) = File::open(&file) {
            for line in io::BufReader::new(f).lines().flatten() {
                db.execute(&line, true);
            }
        }
    }
    if !query.is_empty() { db.execute(&query, false); }
    if !file.is_empty() {
        if let Ok(mut f) = OpenOptions::new().append(true).create(true).open(&file) {
            if query.starts_with("SPUSH") || query.starts_with("QPUSH") || 
               query.starts_with("MPUSH") || query.starts_with("FPUSH") || 
               query.starts_with("LPUSH") || query.starts_with("MDEL") || 
               query.starts_with("FDEL") || query.starts_with("LDEL") ||
               query.starts_with("SPOP") || query.starts_with("QPOP") {
                let _ = writeln!(f, "{}", query);
            }
        }
    }
}
