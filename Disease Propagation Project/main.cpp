//
//  main.cpp
//  Disease Propagation Project
//
//  Created by Jordan Landel on 10/27/20.
//

#include "mex.hpp"
#include "mexAdapter.hpp"
#include "disease_propagation.hpp"

using namespace matlab::data;
using matlab::mex::ArgumentList;

class MexFunction : public matlab::mex::Function{
public:
    void operator()(ArgumentList outputs, ArgumentList inputs) {
        
        TypedArray<int> intArray = std::move(inputs[0]);
        
        int n = intArray[0];
        int d = intArray[1];
        int r = intArray[2];
        
        outputs[0] = propagator(n,d,r);
    }
};

