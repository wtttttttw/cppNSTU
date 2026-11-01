pub struct MyArray {
    data: Vec<String>,
}

impl MyArray {
    pub fn new() -> Self { MyArray { data: Vec::new() } }
    pub fn create(&mut self) { self.data.clear(); }
    pub fn push_back(&mut self, val: String) { self.data.push(val); }
    pub fn insert_at(&mut self, index: usize, val: String) {
        if index <= self.data.len() { self.data.insert(index, val); }
    }
    pub fn remove_at(&mut self, index: usize) {
        if index < self.data.len() { self.data.remove(index); }
    }
    pub fn get(&self, index: usize) -> String {
        if index < self.data.len() { self.data[index].clone() } else { "ERROR".to_string() }
    }
    pub fn set(&mut self, index: usize, val: String) {
        if index < self.data.len() { self.data[index] = val; }
    }
    pub fn length(&self) -> usize { self.data.len() }
}
