#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <deque>

using namespace std;

class BoundedBuffer {
public:
    explicit BoundedBuffer(int capacity) : capacity(capacity) {}

    void produce(int item) {
        unique_lock<mutex> lock(buffer_mutex);
        cv_produce.wait(lock, [this]() { return buffer.size() < capacity; });

        buffer.push_back(item);
        cout << "Produced: " << item << ", Buffer size: " << buffer.size() << endl;

        cv_consume.notify_one();
    }

    int consume() {
        unique_lock<mutex> lock(buffer_mutex);
        cv_consume.wait(lock, [this]() { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop_front();
        cout << "Consumed: " << item << ", Buffer size: " << buffer.size() << endl;

        cv_produce.notify_one();

        return item;
    }

private:
    int capacity;
    deque<int> buffer;
    mutex buffer_mutex;
    condition_variable cv_produce;
    condition_variable cv_consume;
};

void producer_thread(BoundedBuffer &buffer, int producer_id) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
        int item = rand() % 100;
        buffer.produce(item);
    }
}

void consumer_thread(BoundedBuffer &buffer, int consumer_id) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
        int item = buffer.consume();
    }
}

int main() {
    srand(time(nullptr));

    int buffer_capacity = 5;
    BoundedBuffer buffer(buffer_capacity);

    int num_producers = 2;
    int num_consumers = 3;

    vector<thread> producers(num_producers);
    vector<thread> consumers(num_consumers);

    for (int i = 0; i < num_producers; ++i) {
        producers[i] = thread(producer_thread, ref(buffer), i + 1);
    }

    for (int i = 0; i < num_consumers; ++i) {
        consumers[i] = thread(consumer_thread, ref(buffer), i + 1);
    }

    for (int i = 0; i < num_producers; ++i) {
        producers[i].join();
    }

    for (int i = 0; i < num_consumers; ++i) {
        consumers[i].join();
    }

    return 0;
}
