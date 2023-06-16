#include <iostream>
#include <vector>

using namespace std;

std::vector<int> heap;

    // Inserting elements into the vector
    heap.push_back(30);
    heap.push_back(10);
    heap.push_back(50);
    heap.push_back(20);

    // Converting the vector into a heap
    std::make_heap(heap.begin(), heap.end());

    while (!heap.empty()) {
        // Accessing and removing the maximum element
        int maxElement = heap.front();
        std::cout << maxElement << " ";

        // Reconstructing the heap after removing the maximum element
        std::pop_heap(heap.begin(), heap.end());
        heap.pop_back();
    }

    return 0;

int main(){

    return 0;
}