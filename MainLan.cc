/*****************************************************************
 *
 * First version of PSO for Mallva v0.0
 * José Manuel García Nieto 01/12/2006
 * File : Pso.cpp BINARY PSO
 * Definition of the PSO skeleton for Mallba
 * For the problem instance: 
 *
 *****************************************************************
 **  Proyecto Fin de Carrera 2005/2006 ****************************/

#include "PSO.hh"

#include "PSO.pro.cc"
#include "PSO.req.cc"

#include <string>
#include <sstream>
#include <iostream>

int main (int argc, char** argv)
{
	using skeleton PSO;

    int n_total_phases, n_tl_logic, n_vehicles, sim_time;
    ifstream is ( argv[3] ); /* info file */
    char buffer[MAX_BUFFER];
    char instance[MAX_BUFFER];
    char path[MAX_BUFFER];
    char configPath[MAX_BUFFER];
    char dirPath[MAX_BUFFER];

    //system("clear");

    cout << "argv[3]: " << argv[3] << endl;
    is.getline(buffer,MAX_BUFFER,'\n');

    cout << "buffer: " << buffer << endl;
    sscanf(buffer,"%d %s %s %d %d %d",&n_tl_logic,&path,&instance,&n_total_phases,&n_vehicles,&sim_time);

    cout << "buffer: " << buffer << endl;
    cout << "Simulation time: " << sim_time << endl;
    cout << "n_tl_logic: " << n_tl_logic << ", n_total_phases: " << n_total_phases << ", n_vehicles: " <<  n_vehicles  <<endl;
    cout << "path: "<< path << ", instance: " << instance << endl;

    getcwd(dirPath, MAX_BUFFER);
    strcat(dirPath, "/");

    sprintf(configPath, "%s", dirPath);
    strcat(configPath, "Config.cfg");

    cout << "configPath: " << configPath << endl;

	int len;
	int longitud;

	//system("clear");

    /*
    len = strlen(configPath);
	longitud = MAX_BUFFER - len;

    cout << "configPath: " << configPath << endl;

    ifstream f("Config.cfg");
    if(!f) show_message(2); // configuration file error

    f.getline(&(configPath[len]),longitud,'\n');


    ifstream funo(configPath);
	if(!funo)	show_message(2);

    f.getline(&(configPath[len]),longitud,'\n');
    cout << "configPath: " << configPath << endl;
    ifstream fdos(configPath);
    if(!fdos) show_message(9); */
		
    SetUpParams cfg;
    ifstream f1(argv[1]);
    //funo >> cfg;
    f1 >> cfg;
    cfg.particle_size(n_total_phases);
    cout << cfg << endl;


    ifstream f2 ( argv[2] );
    if (!f2) show_message(12);

    //Problem pbm(10,10,10,500,"alameda","malaga");
    Problem pbm(n_total_phases, n_tl_logic, sim_time, n_vehicles, path, instance);
    f2 >> pbm;
    //fdos >> pbm;

	Migration mig(pbm.direction(),cfg.migration_rate());

	Solver_Lan solver(pbm,cfg,mig,argc,argv);
	solver.run();

	if (solver.pid()==0)
	{
		solver.show_state();
		cout << "Solution: " << solver.global_best_solution() << endl << endl;
		cout << "Fitness: " << solver.global_best_solution().fitness();

        /*
		f.getline(&(path[len]),longitud,'\n');
	  	ofstream fexit(path);
	  	if(!fexit) show_message(2);
        fexit << solver.userstatistics();*/

        solver.global_best_solution().best_to_xml(argv[4]);
        ofstream fexit(argv[5]);
        if(!fexit) show_message(13);
        fexit << solver.userstatistics();

		cout << endl << endl << " :( ---------------------- THE END --------------- :) " << endl;
	}
	return(0);
}
/*# MainLan */
