#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <regex>
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

    std::regex int_pattern(R"(^\s*[1-9]\d*\s*$)");
    std::regex coords_pattern(R"(^\s*([+-]?\d+(\.\d+)?\s+){5}[+-]?\d+(\.\d+)?\s*$)");

    std::string line;
    if (!std::getline(fin, line) || !std::regex_match(line, int_pattern)) {
        std::cout << "Ошибка при чтении количества треугольников\n";
        return 2;
    }
    int n = std::stoi(line);

    List l;
    l.GotoBeg();

    for (int i=0; i<n; i++) {
        if (!std::getline(fin, line) || !std::regex_match(line, coords_pattern)) {
            std::cout << "Ошибка чтения координат в строке " << (i + 2) << "\n";
            return 3;
        }

        double x1, y1, x2, y2, x3, y3;
        std::istringstream iss(line);
        iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

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
