#include <iostream>
#include <tuple>
#include <math.h>
 
static const auto my_pi = 3.14;

//----------- as a function -----------
double myfunc(double r2, double r1)
{
    return M_PI*(r2*r2-r1*r1); 
}
 
//----------- as a lambda with tuple-----------
auto mylambda = [](auto r2, auto r1) 
{ 
    return M_PI*(r2*r2-r1*r1); 
};

auto mylambda2 = [&my_pi](auto r)
{
    std::cout << "LAMBA: "<< r << " and Global Pi Coeff: " << my_pi <<  "\n"; 
    return r; 
};
 
int main()
{
    std::cout << "Ring Area : " <<  std::apply( myfunc, std::make_pair(20., 10.)) << std::endl;
 
    std::cout << "Ring Area : " <<  std::apply( mylambda, std::make_pair(20., 10.)) << std::endl;
    
    
    std::tuple mytuple { 20., 10. };
    std::cout << "Ring Area : " << std::apply( myfunc, mytuple) << std::endl;
    std::cout << "Ring Area : " << std::apply( mylambda, mytuple) << std::endl;
    
    
 
 

    std::apply([&mylambda2](auto &&...args) 
    {
        int sum = 0; 
        sum = (mylambda2(args) + ...);      // sum = (mylambda2(args[0]) + mylambda2(args[1]) + ... + mylambda2(args[n]));
        std::cout << "sum: " << sum << "\n";
    }, mytuple);
 
    return 0;
}