Warsaw University of Technology project for Operating Systems.  
Implementation of readers and writers problem.  
9 elements FIFO buffer, 2 writers, 2 readers, reader can remove element from buffer if the other reader isn't reading it.  

Compilation: g++ -pthread -std=c++11 -o name main.cpp queue\_t.cpp
