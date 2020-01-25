/*! \file  process.hpp
    \brief A process keeps track of the resources used by a running
           Nachos program
  
        The resources considered are the memory (addrspace.hpp), the
        processor (thread.hpp), the open files, the statistics, ...
*/

#ifndef PROCESS_H
#define PROCESS_H

#include "kernel/copyright.hpp"
#include "kernel/synch.hpp"
#include "kernel/addrspace.hpp"
#include "filesys/openfile.hpp"
#include "utility/stats.hpp"

class AddrSpace;
class Thread;
class Semaphore;

/*! \brief Defines the data structures to keep track of the execution
 environment of a user program */
class Process {
public:
  /*!
   * Create an address space, initializing it with the program stored
   * in the file "executable", without any thread in it.
   */
  Process(char *filename, int *err);

  /*! Process destructor */
  ~Process();	

  /*! Pointer on the executable file (may be NULL) */
  OpenFile *exec_file;
  
  AddrSpace * addrspace;              /*!< Pointer to the address space */

  int numThreads;                     /*!< Number of threads attached
                                        to this process */
         
  ProcessStat *stat;                  /*!< Statistics concerning this
                                        process */

  char * getName() {return(name);}    /*!< Returns the process name */

private:
  char *name;
};

#endif // PROCESS_H
