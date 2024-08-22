//Operator Overloading

#include<iostream>

//using namespace std;

class Complex
{
public:
    int a,b;
    void input(std::string s)
    {
        int v1=0;
        int i=0;
        while(s[i]!='+')
        {
            v1=v1*10+s[i]-'0';
            i++;
        }
        while(s[i]==' ' || s[i]=='+'||s[i]=='i')
        {
            i++;
        }
        int v2=0;
        while(i<s.length())
        {
            v2=v2*10+s[i]-'0';
            i++;
        }
        a=v1;
        b=v2;
    }
};

//Overload operators + and << for the class complex
//+ should add two complex numbers as (a+ib) + (c+id) = (a+c) + i(b+d)
//<< should print a complex number in the format "a+ib"

Complex operator+(Complex const &lsh, Complex const &rhs){
  Complex temp;
  int a = lsh.a + rhs.a;
  int b = lsh.b + rhs.b;

  temp.a = a;
  temp.b = b;

  return temp;
}

std::ostream& operator<<(std::ostream &lhs, Complex const &rhs){
  lhs << rhs.a << "+i" << rhs.b;
  return lhs;
}

int main()
{
    Complex x,y;
    std::string s1,s2;
    std::cin>>s1;
    std::cin>>s2;
    x.input(s1);
    y.input(s2);
    Complex z=x+y;
    std::cout<<z<<std::endl;
}
