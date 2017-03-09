#include "queue_t.hpp"
#include <thread>
#include <semaphore.h>
#include <iostream>
#include <unistd.h>
#include <ctime>

void producer(char id, queue_t &q) {
  srand(time(NULL));
  char element;
  while(true) {
    element = rand() % 25 + 65;
    q.push(element);
    sleep(rand() % 3);
  }
}

void reader(char id, queue_t &q) {
  srand(time(NULL));
  while(true) {
    q.read_element(id);
    sleep(rand() % 3);
  }
}

int main() {
  queue_t q;
  std::thread readerA(reader, 'a', std::ref(q));
  std::thread readerB(reader, 'b', std::ref(q));
  std::thread producerA(producer, 'a', std::ref(q));
  std::thread producerB(producer, 'b', std::ref(q));
  readerA.join();
  readerB.join();
  producerA.join();
  producerB.join();
  return 0;
}
