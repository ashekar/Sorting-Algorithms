#include <iostream>
#include <random>
#include "stdbool.h"



int EuclidAlgorithm(int a, int b){
    std::cout << a << " " << b << " \n";
    if(a == 0){
        return b;
    }else if(b == 0){
        return a;
    }
    else{
        if(a > b){
            return EuclidAlgorithm(a%b, b);
        }else{
            return EuclidAlgorithm(a, b%a);
        }
    }

}

int main(){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, 100);
    int a, b;

    for(int i = 0; i < 10; i++){

        a = dist(mt);

        b = dist(mt);

        std::cout << a << " ";
        std::cout << b << " \n";


        std::cout << "Results\n";
        std::cout << EuclidAlgorithm(a, b) << "\n";

    }

    return 0;
}

