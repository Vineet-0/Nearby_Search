#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <random>

using namespace std;

class SharedResource {
public:
    void read(int reader_id) {
        shared_lock<shared_mutex> lock(rw_mutex);
        cout << "Reader " << reader_id << " reads the value: " << value << endl;
    }

    void write(int writer_id, int new_value) {
        unique_lock<shared_mutex> lock(rw_mutex);
        value = new_value;
        cout << "Writer " << writer_id << " writes the value: " << value << endl;
    }

private:
    int value = 0;
    shared_mutex rw_mutex;
};

void reader_thread(SharedResource &resource, int reader_id) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
        resource.read(reader_id);
    }
}

void writer_thread(SharedResource &resource, int writer_id) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
        resource.write(writer_id, rand() % 100);
    }
}

int main() {
    srand(time(nullptr));

    const int num_readers = 5;
    const int num_writers = 2;

    SharedResource resource;

    vector<thread> readers(num_readers);
    vector<thread> writers(num_writers);

    for (int i = 0; i < num_readers; ++i) {
        readers[i] = thread(reader_thread, ref(resource), i + 1);
    }

    for (int i = 0; i < num_writers; ++i) {
        writers[i] = thread(writer_thread, ref(resource), i + 1);
    }

    for (int i = 0; i < num_readers; ++i) {
        readers[i].join();
    }

    for (int i = 0; i < num_writers; ++i) {
        writers[i].join();
    }

    return 0;
}
