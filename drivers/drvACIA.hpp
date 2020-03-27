/*! \file drvACIA.hpp
 \brief Data structures for the ACIA device driver
 interrupt_send and interrupt_receive are used in the intrrupt mode only.

 The ACIA is an asynchronous device (requests return
 immediately, and an interrupt happens later on).
 This is a layer on top of the ACIA.
 Two working modes are to be implemented in assignment 2:
 a Busy Waiting mode and an Interrupt mode. The Busy Waiting
 mode implements a synchronous IO whereas IOs are asynchronous
 IOs are implemented in the Interrupt mode (see the Nachos
 roadmap for further details).

 Copyright (c) 1999-2000 INSA de Rennes.
 All rights reserved.
 See copyright_insa.hpp for copyright notice and limitation
 of liability and disclaimer of warranty provisions.
 */

#ifndef _ACIA_HDL
#define _ACIA_HDL

/* Includes */

#include "kernel/synch.hpp"	// for the acces to the synchronisation's tools

#define BUFFER_SIZE 256  // size of emission and reception buffers

/*! The class DriverACIA defines the handler of the ACIA. It is the
 system's interface between the user programs and the ACIA (simulated) hardware.*/

/*! \brief Defines an ACIA (Asynchronous Communication Interface Adapter) device driver */
class DriverACIA
{
private:
    char send_buffer[BUFFER_SIZE]; //!< system buffer for emission
    char receive_buffer[BUFFER_SIZE]; //!< system buffer for reception

    Semaphore *semaphore_send; //!< semaphore used to synchronize emission requests
    Semaphore *semaphore_receive; //!< semaphore used to synchronize reception requests

    Lock *lock_send; //!< lock to be sure there is only one thread working in busy waiting mode when sending
    Lock *lock_receive; //!< lock to be sure there is only one thread working in busy waiting mode when receiving

    int index_send; //!< index in the emission buffer
    int index_receive; //!< index in the reception buffer

public:
    //! Constructor. Driver initialization.
    DriverACIA();

    //! Send a message through the ACIA
    int TtySend(char *buffer);

    //! Receive a message using the ACIA
    int TtyReceive(char *buffer, int length);

    //! Emission interrupt handler. Used in the ACIA Interrupt mode only
    void InterruptSend();

    //! Reception interrupt handler. Used in the ACIA Interrupt mode only
    void InterruptReceive();
};
#endif // _ACIA_HDL

