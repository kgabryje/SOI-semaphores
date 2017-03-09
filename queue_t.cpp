#include "queue_t.hpp"
#include <iostream>

queue_t::queue_t() {
  sem_init(&sem_full,0,9);
  sem_init(&sem_empty,0,0);
  sem_init(&sem_modify,0,1);
  sem_init(&reader_a,0,1);
  sem_init(&reader_b,0,1);
  sem_init(&cout_mutex,0,1);
}

queue_t::~queue_t() {
  sem_destroy(&sem_full);
  sem_destroy(&sem_empty);
  sem_destroy(&sem_modify);
  sem_destroy(&reader_a);
  sem_destroy(&reader_b);
  sem_destroy(&cout_mutex);
}

void queue_t::push(char element) {
  sem_wait(&sem_full);
  sem_wait(&sem_modify);

  q.push(element);

  sem_wait(&cout_mutex);
  sem_getvalue(&sem_empty,&buffer_state);
  std::cout << "Pushed element: " << element << std::endl;
  std::cout << "Buffer state: " << buffer_state << std::endl;
  sem_post(&cout_mutex);

  sem_post(&sem_modify);
  sem_post(&sem_empty);
}

void queue_t::read_element(char reader_id) {
  //tu zjebane
  sem_wait(&sem_empty);
  sem_post(&sem_empty);
  if (reader_id == 'a')
    sem_wait(&reader_a);
  else if (reader_id == 'b')
    sem_wait(&reader_b);

  sem_wait(&cout_mutex);
  std::cout << "Reader: " << reader_id << " read element: " << q.back() << std::endl;
  sem_post(&cout_mutex);

  if (reader_id == 'a')
    sem_post(&reader_a);
  else if (reader_id == 'b')
    sem_post(&reader_b);
//i tu zjebane
  pop(reader_id);
}

void queue_t::pop(char reader_id) {
  sem_wait(&sem_empty);
  sem_wait(&sem_modify);
  if (reader_id == 'a')
    sem_wait(&reader_b);
  else if (reader_id == 'b')
    sem_wait(&reader_a);

  sem_wait(&cout_mutex);
  sem_getvalue(&sem_empty,&buffer_state);
  std::cout << "Reader: " << reader_id << " popped element: " << q.back() << std::endl;
  std::cout << "Buffer state: " << buffer_state << std::endl;
  sem_post(&cout_mutex);

  q.pop();

  if (reader_id == 'a')
    sem_post(&reader_b);
  else if (reader_id == 'b')
    sem_post(&reader_a);
  sem_post(&sem_modify);
  sem_post(&sem_full);
}
