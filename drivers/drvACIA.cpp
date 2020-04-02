/*! \file drvACIA.cpp
 //  \brief Routines of the ACIA device driver
 //
 //      The ACIA is an asynchronous device (requests return
 //      immediately, and an interrupt happens later on).
 //      This is a layer on top of the ACIA.
 //      Two working modes are to be implemented in assignment 2:
 //      a Busy Waiting mode and an Interrupt mode. The Busy Waiting
 //      mode implements a synchronous IO whereas IOs are asynchronous
 //      IOs are implemented in the Interrupt mode (see the Nachos
 //      roadmap for further details).
 //
 //  Copyright (c) 1999-2000 INSA de Rennes.
 //  All rights reserved.
 //  See copyright_insa.hpp for copyright notice and limitation
 //  of liability and disclaimer of warranty provisions.
 //
 */

/* Includes */

#include "kernel/system.hpp"         // for the ACIA object
#include "kernel/synch.hpp"
#include "machine/ACIA.hpp"
#include "drivers/drvACIA.hpp"

//-------------------------------------------------------------------------
// DriverACIA::DriverACIA()
/*! Constructor.
 Initialize the ACIA driver. In the ACIA Interrupt mode,
 initialize the reception index and semaphores and allow
 reception and emission interrupts.
 In the ACIA Busy Waiting mode, simply initialize the ACIA
 working mode and create the semaphores.
 */
//-------------------------------------------------------------------------
DriverACIA::DriverACIA()
{
    DEBUG('d', "Creating ACIA driver\n");

    switch (g_cfg->ACIA)
    {
        case ACIA_BUSY_WAITING:
        {
            g_machine->acia->SetWorkingMode(BUSY_WAITING);
            break;
        }
        case ACIA_INTERRUPT:
        {
            g_machine->acia->SetWorkingMode(SEND_INTERRUPT | REC_INTERRUPT);
            break;
        }
        default:
            DEBUG('d', "Error: wrong ACIA mode (need ACIA_BUSY_WAITING, ACIA_INTERRUPT, ...)\n");
            break;
    }

    send_buffer[BUFFER_SIZE] = { 0 };
    receive_buffer[BUFFER_SIZE] = { 0 };

    semaphore_send = new Semaphore("send_semaphore driver ACIA", 1);
    semaphore_receive = new Semaphore("receive_semaphore driver ACIA", 0);

    lock_send = new Lock("lock_send driver ACIA");
    lock_receive = new Lock("lock_receive driver ACIA");

    index_send = 0;
    index_receive = 0;
}

//-------------------------------------------------------------------------
// DriverACIA::TtySend(char* buff)
/*! Routine to send a message through the ACIA (Busy Waiting or Interrupt mode)
 */
//-------------------------------------------------------------------------
int DriverACIA::TtySend(char *buffer)
{
    DEBUG('d', "Using TtySend(char *buffer) with the message: %s\n", buffer);

    int i = -1;

    do
    {
        while(g_machine->acia->GetOutputStateReg() == EMPTY)
        {
            ++i;

            lock_send->Acquire();
            g_machine->acia->PutChar(buffer[i]);
            lock_send->Release();
        }
    } while (buffer[i] != '\0');

    DEBUG('d', "Using TtySend(char *buffer) sent %d chars\n", i);

    return i;
}

//-------------------------------------------------------------------------
// DriverACIA::TtyReceive(char* buff, int length)
/*! Routine to receive a message through the ACIA
 // (Busy Waiting and Interrupt mode).
 */
//-------------------------------------------------------------------------
int DriverACIA::TtyReceive(char *buffer, int length)
{
    DEBUG('d', "Using TtyReceive(char *buffer, int length) with the message: %s length %d\n", buffer, length);

    bool fin = false;

    int i = 0;

    while (!fin)
    {
        while (g_machine->acia->GetInputStateReg() == FULL)
        {
            lock_receive->Acquire();
            buffer[i] = g_machine->acia->GetChar();
            lock_receive->Release();

            ++i;

            if (buffer[i - 1] == '\0' || i >= length)
            {
                fin = true;
            }
        }
    }

    // We have a buffer of length + 1 so we can always append the null character
    buffer[i] = '\0';

    DEBUG('d', "Using TtyReceive(char *buffer, int length) sent %d chars inside the buffer that can contains up to %d chars\n", i, length);

    return i;
}

//-------------------------------------------------------------------------
// DriverACIA::InterruptSend()
/*! Emission interrupt handler.
 Used in the ACIA Interrupt mode only.
 Detects when it's the end of the message (if so, releases the send_sema semaphore), else sends the next character according to index ind_send.
 */
//-------------------------------------------------------------------------
void DriverACIA::InterruptSend()
{
    printf("**** Warning: send interrupt handler not implemented yet\n");
    exit(-1);
}

//-------------------------------------------------------------------------
// DriverACIA::Interrupt_receive()
/*! Reception interrupt handler.
 Used in the ACIA Interrupt mode only. Reveices a character through the ACIA.
 Releases the receive_sema semaphore and disables reception
 interrupts when the last character of the message is received
 (character '\0').
 */
//-------------------------------------------------------------------------
void DriverACIA::InterruptReceive()
{
    printf("**** Warning: receive interrupt handler not implemented yet\n");
    exit(-1);
}
