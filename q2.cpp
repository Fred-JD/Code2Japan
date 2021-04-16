// December 2020
// by Seak Jian De

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int chose_walk_station_no_print(const int station[], int start, int end, int M);
int chose_walk_station(const int station[], int start, int end, int M)
{
    int time_walk = abs(end - start);
    int ref = (time_walk/2); // Reference for distance before and after got station or not
    int station_in = -1, station_out = -1;
    bool bol_station = false;

    // Check do any station between this point
    for (int i = 0; i < M; i++) {
        if (station[i] <= start + ref && station[i] >= start - ref) {
            if (station_in > 0) {
                if (abs(station_in - start) > abs(station[i] - start))
                    station_in = station[i];
            }
            else{
                station_in = station[i];
            }
        }
    }

    if (station_in != -1)
        ref += abs(station_in - start);

    for (int i = 0; i < M; i++) {
        if (station[i] <= end + ref && station[i] >= end - ref && station_in != station[i]) {
            if (station_out > 0) {
                if (abs(station_out - end) > abs(station[i] - end))
                    station_out = station[i];
            }
            else{
                station_out = station[i];
            }
        }
    }

    if (station_out >= 0 && station_in == -1)
    {
        ref += abs(station_out - end);
        for (int i = 0; i < M; i++) {
            if (station[i] <= start + ref && station[i] >= start - ref && station_out != station[i]) {
                if (station_in > 0) {
                    if (abs(station_in - start) > abs(station[i] - start))
                        station_in = station[i];
                }
                else{
                    station_in = station[i];
                }
            }
        }
    }

    // Check weather using station is consume time less
    if (station_in >= 0 && station_out >= 0) {
        bol_station = true;
    }

    int time_walk2 = abs(station_in - start) + abs(station_out - end);;

    if (bol_station) {
        if (time_walk > time_walk2) {
            time_walk = time_walk2;
            printf("From [%d] walk to station %d comeout at %d walk to [%d] need %d sec.\n",
                    start, station_in, station_out, end, time_walk);
        }
        else {
            printf("From [%d] walk to [%d] need %d sec.\n", start, end, time_walk);
        }
    }
    else {
        printf("From [%d] walk to [%d] need %d sec.\n", start, end, time_walk);
    }

    return time_walk;
} 

int time_all_store(const int station[], const vector<int> store, const int& school, const int& M)
{
    int start = 0;
    int total_time = 0;

    // Go through all the store from starting point
    for (int i = 0; i < store.size(); i++) {
        total_time += chose_walk_station(station, start, store[i], M);
        start = store[i];
        total_time += 1;

        printf("Total time : %d.\n", total_time);
    }

    // From the last store go to school
    total_time += chose_walk_station(station, start, school, M);
    printf("Total time : %d.\n", total_time);

    return total_time;
}

void eliminate_store(vector<int> *store, int station[], int school, int M)
{
    int max[2] = {0, 0};
    int start = 0;

    vector<int> copy_store;

    // // Find the time from home to 1st store
    // max[1] = chose_walk_station_no_print(station, start, store->at(0), M) + 
    //         chose_walk_station_no_print(station, store->at(0), school, M);

    // // Find the maximux time need to travel
    // for (int i = 0; i < store->size() - 1; i++) {
    //     int num = chose_walk_station_no_print(station, store->at(i), store->at(i+1), M) + 
    //                 chose_walk_station_no_print(station, store->at(i), school, M);
        
    //     if (num > max[1]) {
    //         max[1] = num;
    //         max[0] = i + 1; 
    //     }
    // }

    // Copy vector
    int num;
    for (int i = 0; i < store->size(); i++) {
        copy_store.clear();
        for (auto x : *store) {
            copy_store.push_back(x);
        }
        copy_store.erase(copy_store.begin() + i);
        cout << "Eleminate element " << i << endl;
        num = time_all_store(station, copy_store, school, M);
        
        if (i == 0) {
            max[1] = num;
        }

        if (num < max[1]) {
            max[0] = i;
            max[1] = num;
        }
    }

    store->erase(store->begin() + max[0]);

    cout << "\nUpdate store.\n";
    for (auto x : *store) {
        cout << x << " ";
    }
    cout << "\n\n";
}

int main()
{
    // N - Number of store
    // M - Number of teleportation
    // S - Cordinate of school 
    // T - Time in sec
    int N, M, S, T;
    int current_coordinate = 0;

    cout << "Input Value\n";
    cin >> N >> M >> S >> T;

    vector<int> cordinate_store;
    int cordinate_station[M];

    // Read the cordinate for store and station
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        cordinate_store.push_back(temp);
    }
    for (int i = 0; i < M; i++) {
        cin >> cordinate_station[i];
    }

    cout << endl;
    cout << "Number of store = " << N << endl;
    int total_time = time_all_store(cordinate_station, cordinate_store, S, M);

    while(total_time > T) {
        --N;
        eliminate_store(&cordinate_store, cordinate_station, S, M);
        cout << "Number of store = " << N << endl;
        total_time = time_all_store(cordinate_station, cordinate_store, S, M);
    }

    cout << "\n============================================================================\n";
    cout << "Final output = store :" << N << " time:" << total_time << endl;
}


int chose_walk_station_no_print(const int station[], int start, int end, int M)
{
    int time_walk = abs(end - start);
    int ref = (time_walk/2); // Reference for distance before and after got station or not
    int station_in = -1, station_out = -1;
    bool bol_station = false;

    // Check do any station between this point
    for (int i = 0; i < M; i++) {
        if (station[i] <= start + ref && station[i] >= start - ref) {
            if (station_in > 0) {
                if (abs(station_in - start) > abs(station[i] - start))
                    station_in = station[i];
            }
            else{
                station_in = station[i];
            }
        }
        else if (station[i] <= end + ref && station[i] >= end - ref) {
            if (station_out > 0) {
                if (abs(station_out - end) > abs(station[i] - end))
                    station_out = station[i];
            }
            else{
                station_out = station[i];
            }
        }
    }

    // Check weather using station is consume time less
    if (station_in >= 0 && station_out >= 0) {
        bol_station = true;
    }

    if (bol_station) {
        time_walk = abs(station_in - start) + abs(station_out - end);
    }

    return time_walk;
} 