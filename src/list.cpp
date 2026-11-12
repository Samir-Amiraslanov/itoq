#include "../include/list.h"

List::Node::Node(Triangle v, std::unique_ptr<Node> n) : value(v), next(std::move(n)) {}


void List::clear() {

    base.next.reset();
    current = &base;
}


List::List() : base(Triangle(), nullptr), current(&base) {}

List::List(const List& other) : base(Triangle(), nullptr), current(&base) {
    Node* tail = &base;
    Node* p = other.base.next.get();


    while (p != nullptr) {
        tail->next = std::make_unique<Node>(p->value, nullptr);
        if (p == other.current) current = tail->next.get();
        tail = tail->next.get();
        p = p->next.get();
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
    Node* p = other.base.next.get();

    while (p != nullptr) {
        tail->next = std::make_unique<Node>(p->value, nullptr);
        if (p == other.current) current = tail->next.get();
        tail = tail->next.get();
        p = p->next.get();
    }

    if (other.current == &other.base)
        current = &base;

    return *this;
}

void List::GotoBeg() {
    current = &base;
}

int List::StepForward() {
    if (current->next == nullptr) return -1;
    current = current->next.get();
    return 0;
}

void List::showbase(std::ofstream& fout) {
    base.value.show(fout);
}

int List::Insert(const Triangle& t) {
    try {

        auto n = std::make_unique<Node>(t, std::move(current->next));
        current->next = std::move(n);
        return 0;
    } catch (...) {
        return -1;
    }
}

int List::Delete() {
    if (current->next == nullptr) return -1;
    current->next = std::move(current->next->next);
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
    const Node* p = base.next.get();
    int i = 1;
    while (p != nullptr) {
        if (p->value.is_valid()) {
            fout << "Triangle " << i << " ";
            p->value.show(fout);
            fout << " P=" << p->value.perimeter() << " S=" << p->value.area();
            if(p->value.ravnobedr()){
                fout << "ravnobedr";
            }
            fout << std::endl;
        }
        i++;
        p = p->next.get();
    }
}