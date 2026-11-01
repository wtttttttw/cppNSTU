pub struct MyStack {
    data: Vec<String>,
}

impl MyStack {
    pub fn new() -> Self { MyStack { data: Vec::new() } }
    pub fn create(&mut self) { self.data.clear(); }
    pub fn push(&mut self, val: String) { self.data.push(val); }
    pub fn pop(&mut self) -> String { self.data.pop().unwrap_or_else(|| "EMPTY".to_string()) }
    pub fn peek(&self) -> String { self.data.last().cloned().unwrap_or_else(|| "EMPTY".to_string()) }
    
    pub fn print(&self) {
        if self.data.is_empty() { println!("-> EMPTY"); return; }
        print!("-> ");
        for i in (0..self.data.len()).rev() { print!("{} ", self.data[i]); }
        println!();
    }
}
