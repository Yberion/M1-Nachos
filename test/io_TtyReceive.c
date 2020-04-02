/* io_TtyReceive.c
 *	Test Emission-R�ception
 *
//  Copyright (c) 1999-2000 INSA de Rennes.
//  All rights reserved.  
//  See copyright_insa.h for copyright notice and limitation 
//  of liability and disclaimer of warranty provisions.
 */

#include "userlib/syscall.h"
#include "userlib/libnachos.h"

#define TailMes 255

// Tache de consommation
int main(void)
{
    const int NbMess = 5;
    int i = 0;
    char message[TailMes];
    int res;

    n_printf("Debut de la reception des messages\n");

    // Initialisation de la liaison serie
    for (i = 0; i < NbMess; i++)
    {    
        res = TtyReceive(message, sizeof(message));
        
        n_printf("Reception du message : %s\n", message);

        n_printf("[taille:%d]\n", res);
    }

    Halt();

    return 0;
}
