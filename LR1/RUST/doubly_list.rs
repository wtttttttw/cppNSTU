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
    pub fn new() -> Self { DoubleList { head: None, tail: None } }
    pub fn create(&mut self) { self.head = None; self.tail = None; }

    pub fn push_front(&mut self, val: String) {
        let new = Rc::new(RefCell::new(Node { value: val, next: self.head.clone(), prev: None }));
        match self.head.take() {
            Some(old) => old.borrow_mut().prev = Some(new.clone()),
            None => self.tail = Some(new.clone()),
        }
        self.head = Some(new);
    }

    pub fn push_back(&mut self, val: String) {
        let new = Rc::new(RefCell::new(Node { value: val, next: None, prev: self.tail.clone() }));
        match self.tail.take() {
            Some(old) => old.borrow_mut().next = Some(new.clone()),
            None => self.head = Some(new.clone()),
        }
        self.tail = Some(new);
    }

    pub fn insert_after(&mut self, target: String, val: String) {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().value == target {
                let new = Rc::new(RefCell::new(Node {
                    value: val,
                    prev: Some(node.clone()),
                    next: node.borrow().next.clone(),
                }));
                if let Some(next) = node.borrow().next.clone() { next.borrow_mut().prev = Some(new.clone()); }
                else { self.tail = Some(new.clone()); }
                node.borrow_mut().next = Some(new);
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
                let new = Rc::new(RefCell::new(Node {
                    value: val,
                    prev: node.borrow().prev.clone(),
                    next: Some(node.clone()),
                }));
                if let Some(prev) = node.borrow().prev.clone() { prev.borrow_mut().next = Some(new.clone()); }
                else { self.head = Some(new.clone()); }
                node.borrow_mut().prev = Some(new);
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
                if let Some(p) = prev.clone() { p.borrow_mut().next = next.clone(); }
                else { self.head = next.clone(); }
                if let Some(n) = next.clone() { n.borrow_mut().prev = prev.clone(); }
                else { self.tail = prev.clone(); }
                return;
            }
            let next = node.borrow().next.clone();
            current = next;
        }
    }

    pub fn pop_front(&mut self) {
        if let Some(old) = self.head.take() {
            self.head = old.borrow().next.clone();
            if let Some(new_head) = &self.head { new_head.borrow_mut().prev = None; }
            else { self.tail = None; }
        }
    }

    pub fn pop_back(&mut self) {
        if let Some(old) = self.tail.take() {
            self.tail = old.borrow().prev.clone();
            if let Some(new_tail) = &self.tail { new_tail.borrow_mut().next = None; }
            else { self.head = None; }
        }
    }

    pub fn remove_after(&mut self, target: String) {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().value == target {
                let next_opt = node.borrow().next.clone();
                if let Some(to_remove) = next_opt {
                    let after_remove = to_remove.borrow().next.clone();
                    node.borrow_mut().next = after_remove.clone();
                    if let Some(after) = after_remove {
                        after.borrow_mut().prev = Some(node.clone());
                    } else {
                        self.tail = Some(node.clone());
                    }
                }
                return;
            }
            let next_node = node.borrow().next.clone();
            current = next_node;
        }
    }

    pub fn remove_before(&mut self, target: String) {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().value == target {
                let prev_opt = node.borrow().prev.clone();
                if let Some(to_remove) = prev_opt {
                    let before_remove = to_remove.borrow().prev.clone();
                    node.borrow_mut().prev = before_remove.clone();
                    if let Some(before) = before_remove {
                        before.borrow_mut().next = Some(node.clone());
                    } else {
                        self.head = Some(node.clone());
                    }
                }
                return;
            }
            let next_node = node.borrow().next.clone();
            current = next_node;
        }
    }

    pub fn find(&self, val: String) -> bool {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().value == val { return true; }
            let next = node.borrow().next.clone();
            current = next;
        }
        false
    }

    pub fn print(&self) {
        if self.head.is_none() { println!("-> EMPTY"); return; }
        print!("-> ");
        let mut current = self.head.clone();
        while let Some(node) = current {
            print!("{} ", node.borrow().value);
            let next = node.borrow().next.clone();
            current = next;
        }
        println!();
    }

    pub fn get_first(&self) -> String {
        self.head.as_ref().map_or("EMPTY".to_string(), |n| n.borrow().value.clone())
    }

    pub fn get_last(&self) -> String {
        self.tail.as_ref().map_or("EMPTY".to_string(), |n| n.borrow().value.clone())
    }
}
