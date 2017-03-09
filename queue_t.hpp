#include <queue>
#include <semaphore.h>

#ifndef QUEUE_T_HPP
#define QUEUE_T_HPP

class queue_t
{
  std::queue<char> q;
  int buffer_state;
  sem_t sem_modify;
  sem_t sem_full;
  sem_t sem_empty;
  sem_t reader_a;
  sem_t reader_b;
  sem_t cout_mutex;
public:
  queue_t();
  ~queue_t();
  void push(char element);
  void pop(char reader_id);
  void read_element(char reader_id);
};

#endif
