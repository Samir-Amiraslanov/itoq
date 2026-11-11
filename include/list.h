#pragma once
#include "triangle.h"
#include <fstream>
#include <iostream>
#include <memory>


class List {
private:
    struct Node {
        Triangle value;
        std::unique_ptr<Node> next;
        Node(Triangle v = Triangle(), std::unique_ptr<Node> n = nullptr);
    };

    Node base;
    Node* current;
    void clear();

public:
    List();
    List(const List& other);
    ~List();

    List& operator=(const List& other);

    void GotoBeg();
    int StepForward();
    void showbase(std::ofstream& fout);

    int Insert(const Triangle& t);
    int Delete();

    int Get(Triangle *x);
    int Set(Triangle x);

    int CurrentValid(bool& res) const;
    int CurrentPerimeter(double& p) const;
    int CurrentArea(double& s) const;

    void Write(std::ofstream& fout) const;
};