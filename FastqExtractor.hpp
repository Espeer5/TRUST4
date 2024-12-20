/*******************************************************************************
*                                                                              *
*  FASTQEXTRACTOR.HPP                                                          *
*                                                                              *
*  This file is used to expose the main method of fastq_extractor (renamed     *
*  fastq_extractor_main) as a library function. This allows another cpp        *
*  client program to call fastq_extractor_main as a function. and pass         *
*  arguments to it.                                                            *
*                                                                              *
*  Revision History:                                                           *
*      12/20/2024  Edward Speer  Initial Revision                              *
*                                                                              *
*******************************************************************************/

#pragma once

extern int fastq_extractor_main( int argc, char *argv[] );
