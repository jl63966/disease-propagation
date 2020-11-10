//
//  mexTest.cpp
//  Disease Propagation Project
//
//  Created by Jordan Landel on 11/3/20.
//

#include <stdio.h>
#include "mex.hpp"
#include "mexAdapter.hpp"

using namespace matlab::data;
using matlab::mex::ArgumentList;

class MexFunction : public matlab::mex::Function {
public:
    void operator()(ArgumentList outputs, ArgumentList inputs) {

        // Validate arguments
        checkArguments(outputs, inputs);

        // Implement function
        TypedArray<int> doubleArray = std::move(inputs[0]);
        for (int& elem : doubleArray) {
            elem *= 2;
            std::cout << elem << "\n";
        }

        // Assign outputs
        outputs[0] = doubleArray;
    }

    void checkArguments(ArgumentList outputs, ArgumentList inputs) {
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
        ArrayFactory factory;
        if (inputs[0].getType() != ArrayType::DOUBLE ||
            inputs[0].getType() == ArrayType::COMPLEX_DOUBLE)
        {
            matlabPtr->feval(u"error", 0,
                std::vector<Array>({ factory.createScalar("Input must be double array") }));
        }

        if (outputs.size() > 1) {
            matlabPtr->feval(u"error", 0,
                std::vector<Array>({ factory.createScalar("Only one output is returned") }));
        }
    }
};
