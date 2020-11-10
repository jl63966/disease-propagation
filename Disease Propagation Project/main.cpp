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
        
        int n = inputs[0][0]; //pop. size
        int d = inputs[1][0]; //disease duration
        float r = inputs[2][0]; //transfer prob.
        int i = inputs[3][0]; //daily interactions
        srand((unsigned)time(NULL));
        
        vector<int> sickVector = propagator(n,d,r,i);
        int disease_lifespan = sickVector.size();
        unsigned long dl = (unsigned long) disease_lifespan;
        ArrayFactory factory;
        TypedArray<int> sickArray = factory.createArray<int>({1,dl});
        int index = 0;
        for (int i : sickVector) {
            sickArray[index] = i;
            index++;
        }
        
        outputs[0] = sickArray;
    }
};

