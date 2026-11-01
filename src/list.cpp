#include "../include/list.h"

List::Node::Node(Triangle v, Node* n) : value(v), next(n) {}

void List::clear() {
    Node* p = base.next;
    while (p != &base) {
        Node* tmp = p->next;
        delete p;
        p = tmp;
    }
    base.next = &base;
    current = &base;
}

List::List() : base(Triangle(), nullptr), current(&base) {
    base.next = &base;
}

List::List(const List& other) : base(Triangle(), nullptr), current(&base) {
    base.next = &base;
    Node* tail = &base;
    Node* p = other.base.next;

    try {
        while (p != &other.base) {
            Node* n = new Node(p->value, &base);
            tail->next = n;
            tail = n;
            if (p == other.current) current = n;
            p = p->next;
        }
    } catch (...) {
        clear();
    }

    if (other.current == &other.base)
        current = &base;
}

List::~List() {
    clear();
}

List& List::operator=(const List& other) {
    if (this == &other) return *this;
    clear();

    Node* tail = &base;
    Node* p = other.base.next;

    try {
        while (p != &other.base) {
            Node* n = new Node(p->value, &base);
            tail->next = n;
            tail = n;
            if (p == other.current) current = n;
            p = p->next;
        }
    } catch (...) {
        clear();
    }

    if (other.current == &other.base)
        current = &base;

    return *this;
}

void List::GotoBeg() {
    current = &base;
}

int List::StepForward() {
    if (current->next == &base) return -1;
    current = current->next;
    return 0;
}

void List::showbase(std::ofstream& fout) {
    base.value.show(fout);
}

int List::Insert(const Triangle& t) {
    try {
        Node* n = new Node(t, current->next);
        n->next = current->next;
        current->next = n;
        return 0;
    } catch (...) {
        return -1;
    }
}

int List::Delete() {
    Node* v = current->next;
    if (v == &base) return -1;
    current->next = v->next;
    delete v;
    return 0;
}

int List::Get(Triangle *x) {
    if(current == &base) return -1;
    *x = current->value;
    return 0;
}

int List::Set(Triangle x) {
    if(current == &base) return -1;
    current->value = x;
    return 0;
}

int List::CurrentValid(bool& res) const {
    if (current == &base) return -1;
    res = current->value.is_valid();
    return 0;
}

int List::CurrentPerimeter(double& p) const {
    if (current == &base) return -1;
    p = current->value.perimeter();
    return 0;
}

int List::CurrentArea(double& s) const {
    if (current == &base) return -1;
    s = current->value.area();
    return 0;
}

void List::Write(std::ofstream& fout) const {
    const Node* p = base.next;
    int i = 1;
    while (p != &base) {
        if (p->value.is_valid()) {
            fout << "Triangle " << i << " ";
            p->value.show(fout);
            fout << " P=" << p->value.perimeter() << " S=" << p->value.area();
            if(p->value.ravnobedr()){
                fout << "ravnobedr";
            }
            std::cout << std::endl;
        }
        i++;
        p = p->next;
    }
}