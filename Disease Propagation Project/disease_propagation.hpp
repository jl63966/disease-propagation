//
//  disease_propagation.hpp
//  Disease Propagation Project
//
//  Created by Jordan Landel on 11/3/20.
//

#ifndef disease_propagation_hpp
#define disease_propagation_hpp

#include <stdio.h>

#include <iostream>
#include <vector>
#include <string>
#include <random>
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::to_string;
//***************************************************************
class Person {
private:
    int status = 0;
public:
    Person(){};
    int health(){
        return status;
    }
    string status_string(){
        string status_str;
        if (status>0){
            status_str = "sick (" + to_string(status) + " days to go)";
        }
        else if (status==0){
            status_str = "susceptible";
        }
        else if (status==-1){
            status_str = "recovered";
        }
        else if (status==-2){
            status_str = "vaccinated";
        }
        return status_str;
    }
    
    void infect(int n){
        if (status == 0){
            status = n;
        }
    }
    
    void update(){
        if (status>1){
            status-=1;
        }
        else if (status == 1){
            status-=2;
        }
    }
    
    bool is_stable(){
        bool stable = false;
        if (status==-1){
            stable = true;
        }
        return stable;
    }
};
//***************************************************************
class Population{
private:
    int num_of_people = 1;
    int num_of_susceptible = 0;
    int num_of_sick = 0;
    int num_of_recovered = 0;
    int num_of_vaccinated = 0;
    int disease_duration = 5;
    int daily_interactions = 6;
    float r = 0;
    vector<Person> populace;
public:
    Population(){}
    Population(int npeople, int infection_time){
        num_of_people = npeople;
        disease_duration = infection_time;
        for (int i=0; i<npeople; i++){
            Person citizen;
            populace.push_back(citizen);
        }
    }
    
    void population_health(){
        num_of_susceptible = 0;
        num_of_sick = 0;
        num_of_recovered = 0;
        num_of_vaccinated = 0;
        for (Person human : populace){
            if (human.health() > 0){
                num_of_sick++;
            }
            else if (human.health() == 0){
                num_of_susceptible++;
            }
            else if (human.health() == -1){
                num_of_recovered++;
            }
            else if (human.health() == -2){
                num_of_vaccinated++;
            }
        }
        cout << "Population Health Stats (pop. = " << num_of_people << ")\n ";
        cout << "Susceptible: " << num_of_susceptible << "\n ";
        cout << "Sick: " << num_of_sick << "\n ";
        cout << "Recovered: " << num_of_recovered << "\n ";
        cout << "Vaccinated: " << num_of_vaccinated << "\n";
    }
    
    void patient_zero(){
        srand((unsigned)time(NULL));
        int first_infection = (rand()%num_of_people);
        populace.at(first_infection).infect(disease_duration);
    }
    
    int count_infected(){
        int num_sick = 0;
        for (Person human : populace){
            if (human.health() > 0){
                num_sick++;
            }
        }
        return num_sick;
    }
    
    void susc_interactions(Person &human, int human_number){
        vector<int> people_they_meet;
        while (people_they_meet.size() < daily_interactions){
            int stranger_number = rand()%num_of_people;
            if (stranger_number == human_number){continue;}
            bool repeat = false;
            for (auto i : people_they_meet){
                if (i == stranger_number){
                    repeat = true;
                }
            }
            if (repeat){continue;}
            people_they_meet.push_back(stranger_number);
        }
        for (int i : people_they_meet){
            Person stranger = populace.at(i);
            int stranger_health = stranger.health();
            if (stranger_health <= 0) {continue;}
            else {
                float bad_luck = (float) rand()/(float)RAND_MAX;
                if (bad_luck <= r){
                    human.infect(disease_duration+1);
                }
            }
        }
    }
    
    void sick_interactions(Person human, int human_number){
        vector<int> people_they_meet;
        while (people_they_meet.size() < daily_interactions){
            int stranger_number = rand()%num_of_people;
            if (stranger_number == human_number){continue;}
            bool repeat = false;
            for (auto i : people_they_meet){
                if (i == stranger_number){
                    repeat = true;
                    break;
                }
            }
            if (repeat){continue;}
            people_they_meet.push_back(stranger_number);
        }
        for (int i : people_they_meet){
            Person &stranger = populace.at(i);
            int stranger_health = stranger.health();
            if (stranger_health != 0) {continue;}
            else {
                float bad_luck = (float) rand()/(float)RAND_MAX;
                if (bad_luck <= r){
                    stranger.infect(disease_duration+1);
                }
            }
        }
    }
    
    void update(){
        srand((unsigned)time(NULL));
        for (int i=0; i<num_of_people; i++){
            Person person_i = populace.at(i);
            int person_i_health = person_i.health();
            if (person_i_health < 0) {continue;}
            else if (person_i_health == 0) {
                susc_interactions(person_i, i);
                continue;
            }
            else {
                sick_interactions(person_i, i);
            }
        }
        for (Person &citizen : populace){
            citizen.update();
        }
    }
    
    void transfer_probability(float probability){
        r = probability;
    }
};
//***************************************************************

vector<int> propagator(int population_size, int disease_duration, float transfer_probability);

#endif /* disease_propagation_hpp */
