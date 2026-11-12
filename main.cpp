#include <iostream>
#include <fstream>
#include <cmath>
#include <windows.h>
#include "include/point.h"
#include "include/triangle.h"
#include "include/list.h"



int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cout<<"файл не открылся\n";
        return 1;
    }

    int n;
    fin>>n;
    if (!fin || n <= 0) {
        std::cout <<"Ошибка при чтении\n";
        return 2;
    }

    List l;
    l.GotoBeg();

    for (int i=0; i<n; i++) {
        double x1, y1, x2, y2, x3, y3;
        fin>>x1>>y1>>x2>>y2>>x3>>y3;
        if (!fin) {
            std::cout << "Ошибка чтения координат\n";
            return 3;
        }

        Triangle t(Point(x1,y1),Point(x2,y2), Point(x3,y3));
        if (l.Insert(t) < 0) {
            std::cout<<"Ошибка памяти\n";
            return 4;
        }
        l.StepForward();
    }

    std::ofstream fout("output.txt");
    if (!fout) {
        std::cout << "Ошибка открытия output.txt\n";
        return 5;
    }

    l.Write(fout);
    Triangle x;
    l.GotoBeg();
    l.StepForward();
    l.Get(&x);
    x.show(fout);
    fout<< std::endl;
    Triangle new_x(Point (2,2),Point (3,4),Point (9,2));
    l.Set( new_x);
    l.Write(fout);
    l.showbase(fout);

   
    return 0;
}
