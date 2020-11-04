//
//  disease_propagation.cpp
//  Disease Propagation Project
//
//  Created by Jordan Landel on 11/3/20.
//

#include "disease_propagation.hpp"

vector<int> propagator(int population_size, int disease_duration, float transfer_probability) {
    Population austin(population_size,disease_duration);
    austin.transfer_probability(transfer_probability);
    vector<int> sick_counter;
    int step2 = 0;
    for ( ; ; step2++){
        if (step2 == 0){
            austin.patient_zero();
            continue;
        }
        cout << "** Day " << step2 << " **" << endl << " ";
        cout << " " << austin.count_infected() << " sick" << endl;
        sick_counter.push_back(austin.count_infected());
        if (austin.count_infected() == 0){
            break;
        }
        austin.update();
    }
    cout << "Disease ran its course after " << step2 << " days" << endl;
    austin.population_health();
    return sick_counter;
}
