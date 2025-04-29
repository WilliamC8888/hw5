#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool fillSchedule(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsWorked,
    size_t currentDay,
    size_t currentSlot
    );
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    if (avail.size() == 0 || avail[0].size() == 0) {
        return false;
    }

    //clear sched
    sched.clear();
    sched.resize(avail.size());

    //vector tracking shifts worked
    vector<size_t> shiftsWorked(avail[0].size(), 0);

    return fillSchedule(avail, dailyNeed, maxShifts, sched, shiftsWorked, 0, 0);

}

bool fillSchedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsWorked, size_t currentDay, size_t currentSlot){
    
    if (currentDay == avail.size()) {
            return true;
    }

        //if enough workers booked continue next day
    if (sched[currentDay].size() == dailyNeed) {
        return fillSchedule(avail, dailyNeed, maxShifts, sched, shiftsWorked, currentDay + 1, 0);
    }


    for (Worker_T worker = 0; worker < avail[0].size(); worker++){

        //loops through worker checks if available
        if (avail[currentDay][worker]){
            if (shiftsWorked[worker] < maxShifts){
                
                bool alreadyScheduledToday = false;
                for (size_t i = 0; i < sched[currentDay].size(); i++){
                    if (sched[currentDay][i] == worker){
                        alreadyScheduledToday = true;
                        break;
                    }
                }

                if (!alreadyScheduledToday) {
                    sched[currentDay].push_back(worker);
                    shiftsWorked[worker]++;
                    //try to fill next spot
                    if (fillSchedule(avail, dailyNeed, maxShifts, sched, shiftsWorked, currentDay, currentSlot + 1)) {
                        return true;
                    }
                    //backtrack if doesnt work
                    sched[currentDay].pop_back();
                    shiftsWorked[worker]--;
                    }
                }
            }
        }
        return false;
}

