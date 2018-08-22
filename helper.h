/*********************************************************************
 * helper.h - helper file with functions that are reused throughout
 * Dinh Che | dbac496 | Last modified 2018.07.31
 * Author: codeninja55
 *********************************************************************/

#ifndef HELPER_H
#define HELPER_H

extern char * get_current_time();
extern void fatal(char *message);
extern void * ec_malloc(unsigned int size);

#endif // HELPER_H