#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> my_function()
{
    // Возвращаем три значения разных типов данных.
    return std::make_tuple(42, 3.14159, "Hello world");
}

int main() {
   std::tuple<int, double, std::string> result = my_function();
    int i = std::get<0>(result);          
    double d = std::get<1>(result);       
    std::string s = std::get<2>(result);  
    //вариант распаковки
    std::tuple<int, char> t1(10, 'x');
    auto t2 = std::make_tuple("test", 3.1, 14, 'y');
    int myint; char mychar;
    std::tie(myint, mychar) = t1;                            // unpack elements
    std::cout << myint << " " << mychar << '\n';
    std::tie(std::ignore, std::ignore, myint, mychar) = t2;  // unpack (with ignore)
    std::cout << myint << " " << mychar << '\n';
    std::get<2>(t2) = 100;
    myint = std::get<2>(t2);
    std::cout << myint << '\n';

    return 1;
}