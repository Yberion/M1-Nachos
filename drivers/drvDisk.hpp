/*! \file drvDisk.hpp 
 \brief Data structures to export a synchronous interface to the raw
 disk device.

 Copyright (c) 1992-1993 The Regents of the University of California.
 All rights reserved.  See copyright.hpp for copyright notice and limitation
 of liability and disclaimer of warranty provisions.
 */

#include "kernel/copyright.hpp"

#ifndef SYNCHDISK_H
#define SYNCHDISK_H

#include "machine/disk.hpp"
#include "kernel/synch.hpp"

class Semaphore;
class Lock;

/*! \brief Defines a "synchronous" disk abstraction.
 //
 // As with other I/O devices, the raw physical disk is an asynchronous
 // device -- requests to read or write portions of the disk (sectors)
 // return immediately, and an interrupt occurs later to signal that the
 // operation completed.  (Also, the physical characteristics of the
 // disk device assume that only one operation can be requested at a
 // time).
 //
 // This class provides the abstraction that for any individual thread
 // making a request, it waits around until the operation finishes before
 // returning.
 */
class DriverDisk
{
public:
    //! Constructor. Initializes the disk driver by initializing the raw Disk.
    DriverDisk(const char *sem_name, const char *lock_name, Disk *theDisk);

    //! Destructor. De-allocate the driver data
    ~DriverDisk();

    //! Read a disk sector, returning only once the data is actually read.
    void ReadSector(int sectorNumber, char *data);

    //! write a disk sector, returning only once the data is actually written.
    void WriteSector(int sectorNumber, char *data);

    //! Called by the disk device interrupt handler, to signal that the current disk operation is complete.
    void RequestDone();

private:
    Semaphore *semaphore; //!< To synchronize requesting thread with the interrupt handler
    Lock *lock; //!< Mutual exclusion on the disk device
    Disk *disk; //!< The disk
};

void DiskRequestDone();
void DiskSwapRequestDone();

#endif // SYNCHDISK_H
