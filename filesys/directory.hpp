/*! \file  directory.hpp 
 \brief Data structures to manage a UNIX-like directory of file names.

 A directory is a table of pairs: <file name, sector #>,
 giving the name of each file in the directory, and
 where to find its file header (the data structure describing
 where to find the file's data blocks) on disk.

 We assume mutual exclusion is provided by the caller.

 Copyright (c) 1992-1993 The Regents of the University of California.
 All rights reserved.  See copyright.hpp for copyright notice and limitation
 of liability and disclaimer of warranty provisions.
 */

#include "kernel/copyright.hpp"

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "filesys/openfile.hpp"
#define FILENAMEMAXLEN 		80

/*! \brief Defines a directory entry
 //
 //  Each entry gives the name of the file, and where
 // the file's header is to be found on disk.
 // Internal data structures kept public so that Directory operations can
 // access them directly.
 */

class DirectoryEntry
{
public:
    bool inUse; //!< Is this directory entry in use?
    int sector; //!< Location on disk to find the FileHeader for this file
    char name[FILENAMEMAXLEN + 1]; //!< Text name for file, with +1 for the trailing '\0'
};

/*!\brief Defines a UNIX-like "directory". 
 //
 // Each entry in the directory describes a file, and where to find
 // it on disk.
 // The directory data structure can be stored in memory, or on disk.
 // When it is on disk, it is stored as a regular Nachos file.
 // The constructor initializes a directory structure in memory; the
 // FetchFrom/WriteBack operations shuffle the directory information
 // from/to disk.
 */
class Directory
{
public:
    //! Initialize an empty directory with space for "size" files
    Directory(int size);

    //! De-allocate the directory
    ~Directory();

    //! Init directory contents from disk
    void FetchFrom(OpenFile *file);

    //! Write modifications to directory contents back to disk
    void WriteBack(OpenFile *file);

    //! Find the sector number of the FileHeader for file: "name"
    int Find(char *name);

    //! Add a file name into the directory
    int Add(char *name, int newSector);

    //! Remove a file from the directory
    int Remove(char *name);

    //! Print the names of all the files in the directory
    void List(char*, int);

    //! Verbose print of the contents of the directory -- all the file names and their contents.
    void Print();

    //! Tests if a directory is empty.
    bool empty();
private:
    int tableSize; //!< Number of directory entries
    DirectoryEntry *table; //!< Table of pairs: <file name, file header location>

    //! Find the index into the directory table corresponding to "name"
    int FindIndex(char *name);
};

#endif // DIRECTORY_H
