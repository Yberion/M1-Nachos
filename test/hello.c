/* hello.c
 *	Simple hello world program
 *
//  Copyright (c) 1999-2000 INSA de Rennes.
//  All rights reserved.  
//  See copyright_insa.hpp for copyright notice and limitation 
//  of liability and disclaimer of warranty provisions.
 */

#include "userlib/syscall.hpp"
#include "userlib/libnachos.hpp"

int
main()
{
  n_printf("** ** ** Bonjour le monde ** ** **\n");

  return 0;
}
