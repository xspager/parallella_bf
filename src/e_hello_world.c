/*
  e_hello_world.c

  Copyright (C) 2012 Adapteva, Inc.
  Contributed by Yaniv Sapir <yaniv@adapteva.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program, see the file COPYING.  If not, see
  <http://www.gnu.org/licenses/>.
*/

// This is the DEVICE side of the Hello World example.
// The host may load this program to any eCore. When
// launched, the program queries the CoreID and prints
// a message identifying itself to the shared external
// memory buffer.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e_lib.h"
#include "bf_vm.h"

int main(void) {
	const char		  ShmName[] = "hello_shm"; 
	char              buf[400] = { 0 };
	e_coreid_t		  coreid;
	e_memseg_t   	  emem;
	unsigned          my_row;
	unsigned          my_col;

	char			program[] = "++++++++++++++++++++++++++++++++++++++++.++++++++++++++++++.+.+.[+.]";
    byte			memory[32] = { 0 };
	char			output[300] = { 0 };


	// Who am I? Query the CoreID from hardware.
	coreid = e_get_coreid();
	e_coords_from_coreid(coreid, &my_row, &my_col);

	if ( E_OK != e_shm_attach(&emem, ShmName) ) {
		return EXIT_FAILURE;
	}

	run(program, memory, output);	

	// // Attach to the shm segment
	snprintf(buf, sizeof(buf), output);

	if ( emem.size >= strlen(buf) + 1 ) {
		// Write the message (including the null terminating
		// character) to shared memory
		e_write((void*)&emem, buf, my_row, my_col, NULL, strlen(buf) + 1);
	} else {
		// Shared memory region is too small for the message
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}
