/*******************************************************************************
*                                                                              *
*  MAIN.HPP                                                                    *
*                                                                              *
*  This file is used to expose the main method of TRUST4 (renamed to           *
*  trust4_main) as a library function. This allows another cpp client program  *
*  to call trust4_main as a function. and pass arguments to it.                *
*                                                                              *
*  Revision History:                                                           *
*      12/20/2024  Edward Speer  Initial Revision                              *
*                                                                              *
*******************************************************************************/

#pragma once

extern int trust4_main( int argc, char *argv[] );
