#include<iostream>
using namespace std;


/*=======================C++ class and object========================*/
class Box{
    private:
        char father;
        int *ptr;
    
    protected:
        double length;
        double breadth;
        double height;

    public:
        // static Member
        static int objectcount;
        static int getObjectcount(){ return objectcount; }


        // Member function declaration and definition
        void setlength(double l){ length = l; } // inline function
        void setbreadth(double b){ breadth = b; }
        void setheight(double h){ height = h; }
        double getVolume() const{
            return length * breadth * height; 
        }
        int getptr() const{ return *ptr; }
        double getlength() const{ return length; }
        Box(double l, double b, double h, int len): length(l), breadth(b), height(h)
        {
            ptr = new int;
            *ptr = len; // if the formal parameters name is same to the member variables,
                        // then use the 'this' pointer
            objectcount++;
            cout << "The object is be created!" << endl;
        }

        Box(const Box &bbox){ // if the class have the pointer variables, u must to difine a copy constructor
            cout << R"((Call the copy constructor))" << endl;
            ptr = new int;
            *ptr = *bbox.ptr; // 复制原始内存的内容到新的内存
                              // 不能简单地使用 ptr = bbox.ptr。这是因为这将使两个指针指向同一个内存位置，
                              // 当你释放其中一个指针所指向的内存时，另一个指针将变成悬空指针，这可能会导致未定义行为。

            length = bbox.length;   // if build a copy constructor function, need to define all the member variables
            breadth = bbox.breadth; // or they will be defined as the random values.
            height = bbox.height;
        }

        virtual ~Box(){
            delete ptr;
            ptr = nullptr;
            objectcount--;
            cout << R"((delete the Box object !))" << endl;
        }

        friend void getBoxLenFriend(const Box& b);
        friend class FriendOfBox;

};

int Box::objectcount = 0;

double getBoxVolume(const Box& b){
    double v = b.getVolume();
    return v;
}

void classBoxTest(){
    Box box1(3.00, 4.00, 5.00, 1);
    box1.setlength(1.00);
    box1.setbreadth(2.00);
    box1.setheight(3.00);

    double volume = ::getBoxVolume(box1); // global function getBoxVolume
    cout << "volume = " << volume << endl;

}

void getBoxLenFriend(const Box& b){
    cout << "This is the friend function of class Box:" << endl;
    cout << "the protected variable of b length = " << b.length << endl;
}
class FriendOfBox{
    public:
    void getBoxLen(const Box& b){
        cout << "This is the friend class member function of class Box:" << endl;
        cout << "the protected variable of b length = " << b.length << endl;
    }
};

void friendofBoxTest(){
    void getBoxLenFriend(const Box&);
    Box box1(3.00, 4.00, 5.00, 1);
    cout << "box1.getlength() = " << box1.getlength() << endl;
    FriendOfBox fb;
    getBoxLenFriend(box1);
    fb.getBoxLen(box1);

}


void PtrBoxTest(){
    Box box1(3.00, 4.00, 5.00, 1);
    Box* p = &box1;
    cout << "p->getVolume() = " << p->getVolume() << endl;
}


void staticMemberTest(){
    Box box1(3.00, 4.00, 5.00, 1);
    cout << "Created object number = " << Box::objectcount << endl;
    Box box2(3.00, 5.00, 4.00, 4);
    cout << "Created object number = " << Box::getObjectcount() << endl;
}



class smallBox: virtual public Box{  // 虚继承，解决菱形继承问题
    private:
        double smallLength;
        double smallBreath;
    public:
        void setsmallLength(double l){ length = l; }
        // constructor can't be inherited
        smallBox(double l, double b, double h, int len, double sb): 
        Box(l, b, h, len), smallLength(1.33), smallBreath(sb)
        {
            cout << "The object is be created!" << endl;
        }
        double getlength() const { return smallLength; }
        ~smallBox(){
            cout << R"((delete the smallBox object! ))" << endl; //R"()" is the raw string literal
        }
};

double getSmallBoxVolume(const smallBox &b){
    double v = b.getVolume();
    return v;
}

void classSmallBoxTest(){
    smallBox box1(3.00, 4.00, 5.00, 2, 6.00);
    box1.setsmallLength(1.00);
    box1.setbreadth(2.00);
    box1.setheight(3.00);

    double volume = ::getBoxVolume(box1); // global function getBoxVolume()
    cout << "volume = " << volume << endl;
    cout << "box1.getptr() = " << box1.getptr() << endl; // child class can call the parent class non-private member function
    cout << "box1.Box::getlength() = " << box1.Box::getlength() << endl; // can use :: to access the parent member, 
}                                                                        // when the parent class has the same name members to the child






/*=======================C++ inherit========================*/
class tiny: virtual public Box{
    private:
        double tinyy;
    public:
        tiny(double l, double b, double h, int len): Box(l, b, h, len){}
        ~tiny(){
            cout << R"((delete the tiny object! ))" << endl;
        }

};


class tinyBox : public smallBox, public tiny{ // multiple inherit, unrecommend
    private:
        double tinybreath;
        double tinyheight;
        double tinylength;

    public:
        tinyBox(double l, double b, double h, int len, 
                double sb, double tb, double th, double tl):
        Box(l, b, h, len),
        smallBox(l, b, h, len, sb), 
        tiny(l, b, h, len), 
        tinybreath(tb), tinyheight(th), tinylength(tl)
        {
            cout << "The object is be created!" << endl;
        }
        ~tinyBox(){
            cout << R"((delete the tinyBox object! ))" << endl;
        }

};


void inheritTest(){
    tinyBox tb(3.00, 4.00, 5.00, 2, 6.00, 0.1, 0.2, 0.3);
    cout << "tb.getlength() = " << tb.getlength() << endl; //这个getlength()是Box的，因为smallBox虚继承于Box

}



/*=======================C++ operator and function overloading========================*/
class OverLD{
    private:
        int old;
        int *len;
    public:
        void setold(int old){ this->old = old; }
        void setlen(int len){ *(this->len) = len; }
        void print(int a){ cout << "a = " << a << endl; }
        void print(double d){ cout << "d = " << d << endl; } // function overloading
        int getlen() const { return *len; }
        int getold() const { return old; }
        OverLD(){ this->len = new int; } // non-parameter constructor
                                         // since the class has pointer member,
                                         // need to open up memory space
        explicit OverLD(int a, int len): old(a)      
        {
            this->len = new int;
            *(this->len) = len;

            cout << "call the constructor" << endl;

        }
        virtual ~OverLD(){
            delete len;
            len = nullptr;
            cout << R"((delete the OverLD object! ))" << endl;
        }
        OverLD(const OverLD& o){
            old = o.old;
            len = new int;
            *len = *(o.len);
            cout << "call the copy constructor" << endl;
        }

        OverLD(OverLD && o) noexcept : old(o.old), len(o.len){ // move constructor
            try{                                               // 移动构造函数通常被声明为noexcept，
                o.len = nullptr;                               // 表示它不会抛出异常。这是因为移动构造函数可能会修改传入的对象
            }catch(const exception& e){                        // 如果抛出异常，可能会导致资源泄漏。
                cerr << "Exception: " << e.what() << endl;     // noexcept关键字告诉编译器，这个函数不会抛出异常，异常会直接传递给调用者
                try{                                           // 所以这个函数里面写的try-catch块，不会捕获异常，这里我只是演示一下try-catch的用法
                    delete len;
                    delete len;
                }catch(const exception& e){ // len可能会释放失败
                    cerr << "Exception: " << e.what() << endl;
                }
                len = nullptr;
                throw; // 处理完异常后，重新抛出异常
            }
                                             
            cout << "call the move constructor" << endl;       
        }

        OverLD operator+(const OverLD& o){ // overloading operator as the member function
            OverLD overld;
            overld.old = this->old + o.old;
            *(overld.len) = *(this->len) + *(o.len);
            return overld;
        }
        friend OverLD operator+(OverLD& o, OverLD& ol); // declare friend function
        friend OverLD operator+(OverLD& o, int num); // declare friend function
        int aaa;


};


OverLD operator+(OverLD& o, OverLD& ol){ // overloading operator as the non-member function
    OverLD overld;
    overld.setold(o.getold() + ol.getold());
    overld.setlen(o.getlen() + ol.getlen());
    
    return overld;
}

OverLD operator+(OverLD& o, int num){ // operator overloading can overload
    OverLD overld(o);
    overld.setold(overld.getold() + num);
    overld.setlen(overld.getlen() + num);

    return overld;

}



void overloadingTest(){
    OverLD o1 = OverLD(1,2);
    OverLD o2 = OverLD(3,4);

    OverLD o3 = o1 + o2;
    OverLD o4 = o1 + 4;

    cout << "o3.getlen() = " << o3.getlen() << endl; // 6
    cout << "o4.getold() = " << o4.getold() << endl; // 5
}






/*=======================C++ polymorphisms========================*/
class Shape{
    protected:
        double width;
        double height;
        int *ptr;
    
    public:
        virtual double area() = 0;
        // In C++, once you have a pure virtual member function, 
        // your class becomes an abstract class and you cannot create any objects from it.

        void setwidth(double w){ width = w; }
        void setheight(double h){ height = h; }
        double getheight() const { return height; }
        double getwidth() const { return width; }
        int getlen() const { return *ptr; }
        void setlen(int len){ *(ptr) = len; }
        explicit Shape(): width(), height(), ptr(new int){}
        explicit Shape(double w, double h, int len): width(w), height(h){
            ptr = new int;
            *ptr = len;
        }
        Shape(): width(), height(), ptr(new int){}
        Shape(double w, double h, int len): width(w), height(h), ptr(new int(len)){}
        Shape(const Shape& s){  // 拷贝构造函数可以直接用私有成员和保护成员
            ptr = new int;
            *ptr = *(s.ptr);
            width = s.width;
            height = s.height;
        }
        virtual ~Shape(){ // if base class and it's derived class has dynamic memory allocating, 
                          // the base class destructor function is must to be virtual
            delete ptr;
            ptr = nullptr;
            cout << R"((delete the Shape object! ))" << endl;
        }
        
};


class Rectangle : public Shape{
    public:
        explicit Rectangle(): Shape(){}
        explicit Rectangle(double w, double h, int len): Shape(w,h,len){}
        Rectangle(const Rectangle& s){ // 拷贝构造函数不能用explicit修饰
            ptr = new int;             // 拷贝构造函数也可以用初始化列表
            *ptr = *(s.ptr);           // 用了explicit修饰，编译器将不能自动调用拷贝构造函数
            width = s.width;
            height = s.height;
        }
        virtual ~Rectangle(){
            delete ptr;
            ptr = nullptr;
            cout << R"((delete the Rectangle object! ))" << endl;
        }

        Rectangle operator+(const Rectangle& s){
            Rectangle sss;
            sss.width = this->width + s.width;
            sss.height = this->height + s.height;
            *(sss.ptr) = *(this->ptr) + *(s.ptr);

            return sss;
        }
        // virtual overloading, and it's not pure
        double area(){
            return width * height;
        }
};


class Triangle : public Shape{
    public:
        explicit Triangle(): Shape(){}
        explicit Triangle(double w, double h, int len): Shape(w,h,len){}
        Triangle(const Triangle& s){
            ptr = new int;
            *ptr = *(s.ptr);
            width = s.width;
            height = s.height;
        }
        virtual ~Triangle(){
            delete ptr;
            ptr = nullptr;
            cout << R"((delete the Triangle object! ))" << endl;
        }
        Triangle operator+(const Triangle& s){
            Triangle sss;
            sss.width = this->width + s.width;
            sss.height = this->height + s.height;
            *(sss.ptr) = *(this->ptr) + *(s.ptr);

            return sss;
        }
        // virtual overloading, and it's not pure
        double area(){
            return (width * height) / 2;
        }
};


class finalClass final : public Shape { // final class can't be inherit
    public:
        double area() final{
            cout << "this class can't be inherit \n" 
            "and the area() can't be reloading no longer" << endl;
            return 0;
        }
};



void polymorphismsTest(){
    Shape *shape;
    Rectangle ra(5,5,1);
    Triangle ta(6,6,2);

    cout << "ra.getheight() = " << ra.getheight() << endl;
    cout << "ta.getheight() = " << ta.getheight() << endl;

    cout << "ra.area() = " << ra.area() << endl;
    cout << "ta.area() = " << ta.area() << endl;

    shape = &ra;  // virtual function is be used in the situation that using the parent pointer point to derived class
    cout << "shape(ra)->area() = " << shape->area() << endl;
    shape = &ta;
    cout << "shape(ta)->area() = " << shape->area() << endl;

    finalClass fc;
    fc.area();

}



int main(){
/*=======================classBoxTest========================*/
    cout << "<===========classBoxTest===========>" << endl;
    void classBoxTest();
    classBoxTest();
    
    cout << endl;
    void classSmallBoxTest();
    classSmallBoxTest();


/*=======================friend function and friend class========================*/
    cout << "<===========friend function and friend class===========>" << endl; 
    void friendofBoxTest();
    friendofBoxTest();


/*=======================pointer of the class========================*/
    cout << "<===========pointer of the class===========>" << endl; 
    void PtrBoxTest();
    PtrBoxTest();

    cout << Box::objectcount << endl;


/*=======================static member variables========================*/
    cout << "<===========static member variables===========>" << endl;
    void staticMemberTest();
    staticMemberTest();


/*=======================C++ inherit========================*/
    cout << "<===========C++ inherit===========>" << endl;
    void inheritTest();
    inheritTest();


/*=======================C++ operator and function overloading========================*/
    cout << "<===========C++ operator and function overloading===========>" << endl;
    void overloadingTest();
    overloadingTest();


/*=======================C++ polymorphisms========================*/
    cout << "<===========C++ polymorphisms===========>" << endl;
    void polymorphismsTest();
    polymorphismsTest();



    return 0;
}