type Link = Option<Box<Node>>;

struct Node {
    value: String,
    next: Link,
}

pub struct ForwardList {
    head: Link,
}

impl ForwardList {
    pub fn new() -> Self { ForwardList { head: None } }
    pub fn create(&mut self) { self.head = None; }

    pub fn push_front(&mut self, val: String) {
        self.head = Some(Box::new(Node { value: val, next: self.head.take() }));
    }

    pub fn push_back(&mut self, val: String) {
        let mut current = &mut self.head;
        while let Some(ref mut node) = *current { 
            current = &mut node.next; 
        }
        *current = Some(Box::new(Node { value: val, next: None }));
    }

    pub fn insert_after(&mut self, target: String, val: String) {
        let mut current = &mut self.head;
        while let Some(ref mut node) = *current {
            if node.value == target {
                node.next = Some(Box::new(Node { value: val, next: node.next.take() }));
                return;
            }
            current = &mut node.next;
        }
    }

    pub fn insert_before(&mut self, target: String, val: String) {
        if let Some(ref head_node) = self.head {
            if head_node.value == target { 
                self.push_front(val); 
                return; 
            }
        }
        let mut current = &mut self.head;
        while let Some(ref mut node) = *current {
            if let Some(ref mut next_node) = node.next {
                if next_node.value == target {
                    node.next = Some(Box::new(Node { value: val, next: node.next.take() }));
                    return;
                }
            }
            current = &mut node.next;
        }
    }

    pub fn remove(&mut self, val: String) {
        Self::remove_helper(&mut self.head, val);
    }

    fn remove_helper(link: &mut Link, val: String) {
        match link {
            None => return,
            Some(node) => {
                if node.value == val {
                    *link = node.next.take();
                } else {
                    Self::remove_helper(&mut node.next, val);
                }
            }
        }
    }

    pub fn find(&self, val: String) -> bool {
        let mut current = &self.head;
        while let Some(ref node) = *current {
            if node.value == val { return true; }
            current = &node.next;
        }
        false
    }

    pub fn print(&self) {
        let mut current = &self.head;
        if current.is_none() { 
            println!("-> EMPTY"); 
            return; 
        }
        print!("-> ");
        while let Some(ref node) = *current {
            print!("{} ", node.value);
            current = &node.next;
        }
        println!();
    }

    pub fn get_first(&self) -> String {
        self.head.as_ref().map_or("EMPTY".to_string(), |n| n.value.clone())
    }

    pub fn get_last(&self) -> String {
        let mut current = &self.head;
        let mut last = "EMPTY".to_string();
        while let Some(node) = current { 
            last = node.value.clone(); 
            current = &node.next; 
        }
        last
    }
}
