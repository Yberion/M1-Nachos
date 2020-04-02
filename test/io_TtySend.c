/* io_TtySend.c
 *	Test Emission-Reception
 *
//  Copyright (c) 1999-2000 INSA de Rennes.
//  All rights reserved.  
//  See copyright_insa.h for copyright notice and limitation 
//  of liability and disclaimer of warranty provisions.
 */

#include "userlib/syscall.h"
#include "userlib/libnachos.h"

// Tache de production
int main(void)
{ 
    const int NbMess = 5;
    char *message[] = { "Ceci est le premier essai",
                        "Le second message est different",
                        "Le trhoisieme comptien des fotes",
                        "Et moi, je suis le quatrieme",
                        "Moi, je suis le dernier, a bientot" };

    int i = 0;
    int res;
        
    n_printf("Debut de l'envoi des messages\n");

    // Initialisation de la liaison s�rie
    for (i = 0; i < NbMess; i++)
    {
        n_printf("Envoi du message %d : %s\n", i, message[i]);

        res = TtySend(message[i]);

        n_printf("Longueur du message %d amis : %d\n", i, res);
    }

    n_printf("Et maintenant je sors\n");

    Halt();

    return 0;
}
