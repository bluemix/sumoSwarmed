/************************************************
***                                           *** 
***  Particle Swarm      Skeleton v1.0        *** 
***  Required classes and methods             ***
***  Developed by: Jose Manuel Garcia-Nieto   ***
***  Date: 25/05/2010                         *** 
************************************************/

#ifndef INC_ES_mallba_hh
#define INC_ES_mallba_hh


#include <iostream>
#include <fstream>
#include <math.h>
#include <values.h>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <Mallba/Rlist.h>
#include <Mallba/Rarray.h>
#include <Mallba/Messages.h>
#include <Mallba/mallba.hh>
#include <Mallba/States.hh>
#include <Mallba/random.hh>
#include <Mallba/time.hh>
#include <Mallba/netstream.hh>
#include <assert.h>

using namespace std;

struct particle // index of a particle in the swarm and its fitness
  {
        int index;
        double fitness;
  };
  
struct logic /* saves each tl_logic with ID, Nº OF PHASES, and STATES of PHASES*/
	{
	char * id;
	int n_phases;
	char ** phases;
	};
#endif

