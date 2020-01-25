/*! \file msgerror.cpp
 // \brief Data structure to store the last syscall error message.
 //
 //  Copyright (c) 1999-2000 INSA de Rennes.
 //  All rights reserved.
 //  See copyright_insa.hpp for copyright notice and limitation
 //  of liability and disclaimer of warranty provisions.
 */

#include "drivers/drvConsole.hpp"
#include "kernel/msgerror.hpp"

//-----------------------------------------------------------------
// SyscallError::SyscallError
/*!      Constructor. Initialize the data structures
 */
//-----------------------------------------------------------------
SyscallError::SyscallError()
{
    lastError = NO_ERROR;
    errorAbout = NULL;

    msgs[NO_ERROR] = "no error %s \n";
    msgs[INC_ERROR] = "incorrect error type %s \n";

    msgs[OPENFILE_ERROR] = "unable to open file %s \n";
    msgs[EXEC_FILE_FORMAT_ERROR] = "file %s is not a valid executable file (not in ELF format)\n";
    msgs[OUT_OF_MEMORY] = "out of memory %s\n";

    msgs[OUT_OF_DISK] = "out of disk space %s\n";
    msgs[ALREADY_IN_DIRECTORY] = "file or directory %s already exists\n";
    msgs[INEXIST_FILE_ERROR] = "file %s does not exist or is a directory\n";
    msgs[INEXIST_DIRECTORY_ERROR] = "directory %s does not exist or is a file\n";
    msgs[NOSPACE_IN_DIRECTORY] = "maximum number of entries in directory %s reached\n";
    msgs[NOT_A_FILE] = "%s is not a file\n";
    msgs[NOT_A_DIRECTORY] = "%s is not a directory\n";
    msgs[DIRECTORY_NOT_EMPTY] = "directory %s is not empty\n";
    msgs[INVALID_COUNTER] = "negative semaphore counter\n";

    msgs[INVALID_SEMAPHORE_ID] = "invalid semaphore identifier %s\n";
    msgs[INVALID_LOCK_ID] = "invalid lock identifier %s\n";
    msgs[INVALID_CONDITION_ID] = "invalid condition identifier %s\n";
    msgs[INVALID_FILE_ID] = "invalid file identifier %s\n";
    msgs[INVALID_THREAD_ID] = "invalid thread identifier %s\n";

    msgs[NO_ACIA] = "no ACIA driver installed %s\n";
}

//-----------------------------------------------------------------
// SyscallError::~SyscallError
/*!      Destructor. De-allocate the structures
 */
//-----------------------------------------------------------------
SyscallError::~SyscallError()
{
    if (errorAbout != NULL)
        delete[] errorAbout;
}

//-----------------------------------------------------------------
// SyscallError::SetMsg
/*!      Set the current error message defined by its index and
 //       the related context string.
 //
 //       \param about is the context string
 //       \param num is the number associated with the error msg
 */
//-----------------------------------------------------------------
void SyscallError::SetMsg(const char *about, int num)
{

    // Delete old "about" string
    if (errorAbout != NULL)
        delete errorAbout;

    // Allocate a new one if the argument is not NULL
    if (about != NULL)
    {
        int size = strlen(about) + 1;
        errorAbout = new char[size];
        strcpy(errorAbout, about);
    }
    else
        errorAbout = NULL;

    // Remember the error code of the last system call
    if ((num < 0) || (num >= NUMMSGERROR))
        lastError = INC_ERROR;
    if (msgs[num] == NULL)
        lastError = INC_ERROR;
    else
        lastError = num;
}

//-----------------------------------------------------------------
// SyscallError::GetFormat
/*! Get the error message corresponding to a given error number
 //
 // \param num error number
 // \return error message
 //
 */
//-----------------------------------------------------------------
const char* SyscallError::GetFormat(int num)
{
    if ((num < 0) || (num >= NUMMSGERROR))
        num = INC_ERROR;
    if (msgs[num] == NULL)
        num = INC_ERROR;
    return msgs[num];
}

//-----------------------------------------------------------------
// SyscallError::PrintLastMsg
/*! Print the message of the last Nachos error
 //
 //  \param cons console on which the message should be printed
 //  \param ch heading string to be printed before the Nachos
 //         error message
 */
//-----------------------------------------------------------------
void SyscallError::PrintLastMsg(DriverConsole *cons, const char *ch)
{
    int size = strlen(msgs[lastError]) + strlen(errorAbout) + 1;
    char *msg = new char[size];
    sprintf(msg, msgs[lastError], errorAbout);

    cons->PutString(ch, strlen(ch));
    cons->PutString(" : ", 3);
    cons->PutString(msg, strlen(msg));
}
