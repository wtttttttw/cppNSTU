use std::collections::VecDeque;

pub struct MyQueue {
    data: VecDeque<String>,
}

impl MyQueue {
    pub fn new() -> Self { MyQueue { data: VecDeque::new() } }
    pub fn create(&mut self) { self.data.clear(); }
    pub fn push(&mut self, val: String) { self.data.push_back(val); }
    pub fn pop(&mut self) -> String { self.data.pop_front().unwrap_or_else(|| "EMPTY".to_string()) }
    pub fn peek(&self) -> String { self.data.front().cloned().unwrap_or_else(|| "EMPTY".to_string()) }
    
    pub fn print(&self) {
        if self.data.is_empty() { println!("-> EMPTY"); return; }
        print!("-> ");
        for item in &self.data { print!("{} ", item); }
        println!();
    }
}
