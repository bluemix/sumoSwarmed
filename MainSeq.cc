/*****************************************************************
 *
 * First version of PSO for Mallba v1.0
 * José Manuel Garcia Nieto 28/11/2007
 * File : Pso.cpp STANDARD CONTINUOUS PSO
 * Definition of the PSO skeleton for Mallba
 * For the problem instance: traffic light
 *
 *****************************************************************
 ** ****************************/

#include <ctime>
#include <sstream>
#include <iostream>

#include "PSO.hh"
#include "PSOstructures.hh"
#include "PSO.req.cc"
#include "PSO.pro.cc"

int main (int argc, char** argv)
{
	using skeleton PSO;



	int n_total_phases, n_tl_logic, n_vehicles, sim_time;
	ifstream is ( argv[3] ); /* info file */
	char buffer[MAX_BUFFER];
	char path[MAX_BUFFER];
	char instance[MAX_BUFFER];

	system("clear");

    is.getline(buffer,MAX_BUFFER,'\n');
    sscanf(buffer,"%d %s %s %d %d %d",&n_tl_logic,&path,&instance,&n_total_phases,&n_vehicles,&sim_time);
	
	cout << "buffer: " << buffer << endl;
    cout << "Simulation time: " << sim_time << endl;
    cout << "n_tl_logic: " << n_tl_logic << ", n_total_phases: " << n_total_phases << ", n_vehicles: " <<  n_vehicles  <<endl;
	cout << "path: "<< path << ", instance: " << instance << endl;

	if(argc < 6) show_message(1);


	ifstream funo ( argv[1] );
	if (!funo) show_message(11);
       

	ifstream fpro ( argv[2] );
	if (!fpro) show_message(12);

	SetUpParams cfg;
    ifstream f1(argv[1]);
    //funo >> cfg;
    f1 >> cfg;
    cout << cfg << endl;


    cfg.particle_size(n_total_phases);
	Problem pbm(n_total_phases,n_tl_logic,sim_time,n_vehicles,path,instance);
	fpro >> pbm;
	
	Solver_Seq solver(pbm,cfg);
	
	solver.run(); /* number of evaluations */
	

	if (solver.pid()==0)
	{
		solver.show_state();
		cout << "Solution: " << solver.global_best_solution() << endl;
		cout << "Fitness: " << solver.global_best_cost() << endl;
		cout << "|- Final Fitness: " << solver.global_best_cost() << endl;
		cout << "\n\n :( ---------------------- THE END --------------- :) ";
		cout << endl;
		solver.global_best_solution().best_to_xml(argv[4]);
		ofstream fexit(argv[5]);
		if(!fexit) show_message(13);
		fexit << solver.userstatistics();

	}
	return(0);
}
