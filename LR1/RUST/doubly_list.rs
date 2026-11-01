use std::rc::Rc;
use std::cell::RefCell;

type Link = Option<Rc<RefCell<Node>>>;

struct Node {
    value: String,
    next: Link,
    prev: Link,
}

pub struct DoubleList {
    head: Link,
    tail: Link,
}

impl DoubleList {
    pub fn new() -> Self {
        DoubleList { head: None, tail: None }
    }

    pub fn create(&mut self) {
        self.head = None;
        self.tail = None;
    }

    pub fn push_front(&mut self, val: String) {
        let new_node = Rc::new(RefCell::new(Node {
            value: val,
            next: self.head.clone(),
            prev: None,
        }));
        match self.head.take() {
            Some(old_head) => {
                old_head.borrow_mut().prev = Some(new_node.clone());
            }
            None => {
                self.tail = Some(new_node.clone());
            }
        }
        self.head = Some(new_node);
    }

    pub fn push_back(&mut self, val: String) {
        let new_node = Rc::new(RefCell::new(Node {
            value: val,
            next: None,
            prev: self.tail.clone(),
        }));
        match self.tail.take() {
            Some(old_tail) => {
                old_tail.borrow_mut().next = Some(new_node.clone());
            }
            None => {
                self.head = Some(new_node.clone());
            }
        }
        self.tail = Some(new_node);
    }

    pub fn insert_after(&mut self, target: String, val: String) {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().value == target {
                let new_node = Rc::new(RefCell::new(Node {
                    value: val,
                    prev: Some(node.clone()),
                    next: node.borrow().next.clone(),
                }));
                if let Some(next) = node.borrow().next.clone() {
                    next.borrow_mut().prev = Some(new_node.clone());
                } else {
                    self.tail = Some(new_node.clone());
                }
                node.borrow_mut().next = Some(new_node);
                return;
            }
            let next = node.borrow().next.clone();
            current = next;
        }
    }

    pub fn insert_before(&mut self, target: String, val: String) {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().value == target {
                let new_node = Rc::new(RefCell::new(Node {
                    value: val,
                    prev: node.borrow().prev.clone(),
                    next: Some(node.clone()),
                }));
                if let Some(prev) = node.borrow().prev.clone() {
                    prev.borrow_mut().next = Some(new_node.clone());
                } else {
                    self.head = Some(new_node.clone());
                }
                node.borrow_mut().prev = Some(new_node);
                return;
            }
            let next = node.borrow().next.clone();
            current = next;
        }
    }

    pub fn remove(&mut self, val: String) {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().value == val {
                let prev = node.borrow().prev.clone();
                let next = node.borrow().next.clone();
                
                if let Some(p) = prev.clone() {
                    p.borrow_mut().next = next.clone();
                } else {
                    self.head = next.clone();
                }
                if let Some(n) = next.clone() {
                    n.borrow_mut().prev = prev.clone();
                } else {
                    self.tail = prev.clone();
                }
                return;
            }
            let next = node.borrow().next.clone();
            current = next;
        }
    }

    pub fn find(&self, val: String) -> bool {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().value == val {
                return true;
            }
            let next = node.borrow().next.clone();
            current = next;
        }
        false
    }

    pub fn print(&self) {
        if self.head.is_none() {
            println!("-> EMPTY");
            return;
        }
        print!("-> ");
        let mut current = self.head.clone();
        while let Some(node) = current {
            print!("{} ", node.borrow().value);
            let next = node.borrow().next.clone();
            current = next;
        }
        println!();
    }
}