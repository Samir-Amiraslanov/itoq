#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Point{
    double x,y;
public:
    Point(double a=0.0,double b=0.0):x(a),y(b){}
    double get_x() const { return x; }
    double get_y() const { return y; }
};

class Triangle {
    Point p1, p2, p3;

    double dist(const Point& a, const Point& b) const {
        double dx=a.get_x()-b.get_x();
        double dy=a.get_y()-b.get_y();
        return sqrt(dx*dx+dy*dy);
    }

public:
    Triangle():p1(0,0),p2(0,0),p3(0,0){}
    Triangle(const Point& a, const Point& b, const Point& c):p1(a),p2(b),p3(c){}

    bool is_valid() const {
        double a=dist(p1,p2);
        double b=dist(p2,p3);
        double c=dist(p1,p3);
        return (a+b > c) && (a+c > b) && (b+c > a);
        
    }
    

		bool ravnobedr() const{
		double a=dist(p1,p2);
        double b=dist(p2,p3);
        double c=dist(p1,p3);
        double eps=1e-16;
       // cout<<a<<" "<<b<<" "<<c<<endl;
        //cout<<eps<<endl;
		
        if(abs(a-b)<eps || abs(a-c)<eps || abs(b-c)<eps){
			
			return 1;
		}
		else return 0;
	}

    double perimeter() const {
        return dist(p1,p2)+dist(p2,p3)+dist(p3,p1);
    }

    double area() const {
        double a=dist(p1,p2);
        double b=dist(p2,p3);
        double c=dist(p3, p1);
        double p=(a+b+c)/2.0;
        double t=p*(p-a)*(p-b)*(p-c);
        if (t <= 0) return 0;
        return sqrt(t);
    }
};

class List {
private:
struct Node {
    Triangle value;
    Node* next;
    Node(Triangle v = Triangle(), Node* n = nullptr):value(v),next(n) {}
};

    Node base;
    Node* current;

    void clear() {
        Node* p=base.next;
        while (p!=&base) {
            Node* tmp=p->next;
            delete p;
            p=tmp;
        }
        base.next=&base;
        current=&base;
    }

public:
    List() : base(Triangle(),0), current(&base){
        base.next = &base;
    }

    List(const List& other) : base(Triangle(),0),current(&base){
        base.next=&base;

        Node* tail=&base;
        Node* p=other.base.next;

        try {
            while (p!=&other.base) {
                Node* n=new Node(p->value,&base);
                tail->next=n;
                tail=n;
                if (p==other.current) current=n;
                p = p->next;
            }
        } catch (...) {
            clear();
        }

        if (other.current==&other.base)
            current=&base;
    }

    ~List() { clear(); }

    List& operator=(const List& other) {
        if (this==&other) return *this;

        clear();

        Node* tail=&base;
        Node* p=other.base.next;

        try {
            while (p!=&other.base) {
                Node* n=new Node(p->value,&base);
                tail->next=n;
                tail=n;
                if (p==other.current) current=n;
                p=p->next;
            }
        } catch (...) {
            clear();
        }

        if (other.current==&other.base)
            current=&base;

        return *this;
    }

    void GotoBeg() {current=&base; }

    int StepForward() {
        if (current->next==&base) return -1;
        current=current->next;
        return 0;
    }

    int Insert(const Triangle& t) {
        try {
            Node* n=new Node(t,current->next);
            n->next=current->next;
            current->next=n;
            return 0;
        } catch (...) {
            return -1;
        }
    }

    int Delete() {
        Node* v = current->next;
        if (v == &base) return -1;
        current->next = v->next;
        delete v;
        return 0;
    }

    int CurrentValid(bool& res) const {
        if (current==&base) return -1;
        res=current->value.is_valid();
        return 0;
    }

    int CurrentPerimeter(double& p) const {
        if (current==&base) return -1;
        p=current->value.perimeter();
        return 0;
    }

    int CurrentArea(double& s) const {
        if (current==&base) return -1;
        s=current->value.area();
        return 0;
    }

    void Write(ofstream& fout) const {
        const Node* p =base.next;
        int i = 1;
        int count=0;
        while (p!=&base) {
            if (p->value.is_valid()) {
                fout <<"Triangle "<<i<<" P="<< p->value.perimeter()<<" S="<<p->value.area();
                if(p->value.ravnobedr()){
					fout<<" ravnobedreniy";
					count++;
				}
				fout<<endl;
				
            }
            i++;
            p=p->next;
        }
        fout<<"kolvo ravnobedr: "<<count<<endl;
    }
};

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cout<<"файл не открылся\n";
        return 1;
    }

    int n;
    fin>>n;
    if (!fin || n <= 0) {
        cout <<"Ошибка при чтении\n";
        return 2;
    }

    List l;
    l.GotoBeg();

    for (int i=0; i<n; i++) {
        double x1, y1, x2, y2, x3, y3;
        fin>>x1>>y1>>x2>>y2>>x3>>y3;
        if (!fin) {
            cout << "Ошибка чтения координат\n";
            return 3;
        }

        Triangle t(Point(x1,y1),Point(x2,y2), Point(x3,y3));
        if (l.Insert(t) < 0) {
            cout<<"Ошибка памяти\n";
            return 4;
        }
        l.StepForward();
    }

    ofstream fout("output.txt");
    if (!fout) {
        cout << "Ошибка открытия output.txt\n";
        return 5;
    }

    l.Write(fout);

   
    return 0;
}
