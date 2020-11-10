//
//  disease_propagation.cpp
//  Disease Propagation Project
//
//  Created by Jordan Landel on 11/3/20.
//

#include "disease_propagation.hpp"

vector<int> propagator(int population_size, int disease_duration, float transfer_probability, int interactions) {
    Population austin(population_size,disease_duration,transfer_probability,interactions);
    vector<int> sick_counter;
    int step = 0;
    for ( ; ; step++){
        if (step == 0){
            austin.patient_zero();
            continue;
        }
        sick_counter.push_back(austin.count_infected());
        if (austin.count_infected() == 0){
            break;
        }
        austin.update();
    }
    cout << "Disease ran its course after " << step << " days" << endl;
    austin.population_health();
    return sick_counter;
}
