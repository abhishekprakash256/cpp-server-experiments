#include <iostream>



int add(int a, int b)
{
    return a + b;
}

int main()
{

    int a = 5 ;
    int b = 10 ;

    int result = add(a, b);
    std::cout << "The sum of " << a << " and " << b << " is: " << result << std::endl;
    return 0;

}

// g++ test_2.cpp -o test_2