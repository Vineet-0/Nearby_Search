#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

using namespace std;

enum class State { THINKING, HUNGRY, EATING };

class DiningPhilosophers {
public:
    explicit DiningPhilosophers(int n) : n_philosophers(n), states(n, State::THINKING), cv(n), chopsticks(n) {}

    void philosopher(int id) {
        while (true) {
            think(id);
            pickup_chopsticks(id);
            eat(id);
            release_chopsticks(id);
        }
    }

private:
    void think(int id) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
        cout << "Philosopher " << id << " is thinking." << endl;
    }

    void pickup_chopsticks(int id) {
        unique_lock<mutex> lock(chopsticks_mutex);
        states[id] = State::HUNGRY;
        cout << "Philosopher " << id << " is hungry." << endl;

        while (!can_eat(id)) {
            cv[id].wait(lock);
        }

        states[id] = State::EATING;
    }

    void eat(int id) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
        cout << "Philosopher " << id << " is eating." << endl;
    }

    void release_chopsticks(int id) {
        unique_lock<mutex> lock(chopsticks_mutex);
        states[id] = State::THINKING;
        cout << "Philosopher " << id << " is thinking." << endl;

        int left = (id - 1 + n_philosophers) % n_philosophers;
        int right = (id + 1) % n_philosophers;

        cv[left].notify_one();
        cv[right].notify_one();
    }

    bool can_eat(int id) {
        int left = (id - 1 + n_philosophers) % n_philosophers;
        int right = (id + 1) % n_philosophers;

        return states[left] != State::EATING && states[right] != State::EATING;
    }

    int n_philosophers;
    vector<State> states;
    vector<condition_variable> cv;
    mutex chopsticks_mutex;
    vector<bool> chopsticks;
};

int main() {
    srand(time(nullptr));

    int n_philosophers = 5;
    DiningPhilosophers dining_philosophers(n_philosophers);

    vector<thread> philosophers(n_philosophers);
    for (int i = 0; i < n_philosophers; ++i) {
        philosophers[i] = thread(&DiningPhilosophers::philosopher, &dining_philosophers, i);
    }

    for (int i = 0; i < n_philosophers; ++i) {
        philosophers[i].join();
    }

    return 0;
}
