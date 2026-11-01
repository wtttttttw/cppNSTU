type Link = Option<Box<Node>>;

struct Node {
    value: String,
    next: Link,
}

pub struct ForwardList {
    head: Link,
}

impl ForwardList {
    pub fn new() -> Self {
        ForwardList { head: None }
    }

    pub fn create(&mut self) {
        self.head = None; // В Rust при обнулении head память освобождается автоматически
    }

    pub fn push_front(&mut self, val: String) {
        let new_node = Box::new(Node {
            value: val,
            next: self.head.take(),
        });
        self.head = Some(new_node);
    }

    pub fn push_back(&mut self, val: String) {
        let mut current = &mut self.head;
        while let Some(ref mut node) = *current {
            current = &mut node.next;
        }
        *current = Some(Box::new(Node {
            value: val,
            next: None,
        }));
    }

    pub fn insert_after(&mut self, target: String, val: String) {
        let mut current = &mut self.head;
        while let Some(ref mut node) = *current {
            if node.value == target {
                let new_node = Box::new(Node {
                    value: val,
                    next: node.next.take(),
                });
                node.next = Some(new_node);
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
                    let new_node = Box::new(Node {
                        value: val,
                        next: node.next.take(),
                    });
                    node.next = Some(new_node);
                    return;
                }
            }
            current = &mut node.next;
        }
    }

    pub fn remove(&mut self, val: String) {
        let mut current = &mut self.head;
        while let Some(ref mut node) = *current {
            if node.value == val {
                *current = node.next.take();
                return;
            }
            current = &mut node.next;
        }
    }

    pub fn find(&self, val: String) -> bool {
        let mut current = &self.head;
        while let Some(ref node) = *current {
            if node.value == val {
                return true;
            }
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
}