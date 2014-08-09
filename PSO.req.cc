/************************************************
***                                           *** 
***  Particle Swarm      Skeleton v1.0        *** 
***  Required classes and methods             ***
***  Developed by: Jose Manuel Garcia-Nieto   ***
***  Date: 25/05/2010                         *** 
************************************************/

#ifndef INC_REQ_PSO
#define INC_REQ_PSO

#include "PSO.hh"
#include <ctime>

skeleton PSO {


    // Problem ---------------------------------------------------------------
    Problem::Problem (const int dim, const int ntl, const int st, const int nv, char * path, char * instance):
        _dimension(dim),
        _n_tl_logic(ntl),
        _tl_logic(ntl),
        _simulation_time(st),
        _n_vehicles(nv),
        _path(path),
        _instance(instance),
        _best_cost(1e-14)
    {
    }

    ostream& operator<< (ostream& os, const Problem& pbm)
    {
        os << endl << "Dimension: " << pbm.dimension() << endl;
        os << " Number of tl_logic's: " << pbm.n_tl_logic() << endl;

        for (int i=0;i<pbm.n_tl_logic();i++){
            os << i << " " << pbm.tl_logic(i).id << " " << pbm.tl_logic(i).n_phases;
            for (int j=0;j<pbm.tl_logic(i).n_phases;j++)
                os << " " << pbm.tl_logic(i).phases[j];
            os << endl;
        }
        os<< endl;
        return os;
    }

    istream& operator>> (istream& is, Problem& pbm)
    {
        char buffer[MAX_BUFFER];
        char *tk;
        int n,cont;

        for (int i=0; i<pbm.n_tl_logic(); i++)
        {
            pbm.tl_logic(i).id = new char[MAX_BUFFER];
            char hola[1000];
            is.getline(buffer,MAX_BUFFER,'\n');
            tk=strtok(buffer," ");
            n=sprintf(pbm.tl_logic(i).id,"%s",tk);
            tk=strtok(NULL," ");
            pbm.tl_logic(i).n_phases=atoi(tk);
            pbm.tl_logic(i).phases = new char*[pbm.tl_logic(i).n_phases];
            cont=0;
            while (cont < pbm.tl_logic(i).n_phases)
            {
                tk=strtok(NULL," ");
                pbm.tl_logic(i).phases[cont] = new char[MAX_BUFFER];
                n=sprintf(pbm.tl_logic(i).phases[cont],"%s",tk);
                cont++;
            }
        }
        return is;
    }

    Problem& Problem::operator=(const Problem& pbm)
    {
        _dimension=pbm.dimension();
        _n_tl_logic=pbm.n_tl_logic();
        int n = 0;

        if (_x!=NULL) free(_x);

        if ((_x = new double[_dimension]) == NULL)
            show_message(7);

        for (int i = 0; i < _dimension; i++)
        {
            _x[i] = pbm.x(i);
        }

        for (int t = 0; t < _n_tl_logic; t++)
        {
            _tl_logic[t].id = new char[MAX_BUFFER];
            n=sprintf(_tl_logic[t].id,"%s",pbm.tl_logic(t).id);
            _tl_logic[t].n_phases = pbm.tl_logic(t).n_phases;
            for (int p = 0; p < _tl_logic[t].n_phases; p++)
            {
                _tl_logic[t].phases[p] = new char[MAX_BUFFER];
                n=sprintf(_tl_logic[t].phases[p],"%s",pbm.tl_logic(t).phases[p]);
            }
        }

        return *this;
    }

    bool Problem::operator== (const Problem& pbm) const
    {
        if (_dimension!=pbm.dimension()) return false;

        bool control = true;
        int i = 0;
        while ((control)&&(i<_dimension)){
            if (_x[i] != pbm.x(i)) control = false;
            i++;
        }
        return control;
    }

    bool Problem::operator!= (const Problem& pbm) const
    {
        return !(*this == pbm);
    }

    Direction Problem::direction() const
    {
        //return maximize;
        return minimize;
    }

    /* dimension = number of phases in all tl_logics*/
    int Problem::dimension() const
    {
        return _dimension;
    }

    int Problem::simulation_time() const
    {
        return _simulation_time;
    }

    int Problem::n_tl_logic() const
    {
        return _n_tl_logic;
    }

    Rarray<logic>& Problem::tl_logic()
    {
        return _tl_logic;
    }

    logic& Problem::tl_logic(int index) const
    {
        return _tl_logic[index];
    }

    void Problem::tl_logic(int index, logic& t) const
    {
        _tl_logic[index]=t;
    }

    double Problem::x(const int i) const
    {
        return _x[i];
    }

    double* Problem::x() const
    {
        return _x;
    }


    char* Problem::path() const
    {
        return _path;
    }


    char* Problem::instance() const
    {
        return _instance;
    }


    int Problem::n_vehicles() const
    {
        return _n_vehicles;
    }

    void Problem::dimension(const int d)
    {
        _dimension=d;
    }

    void Problem::n_tl_logic(const int n)
    {
        _n_tl_logic=n;
    }

    void Problem::simulation_time(const int t)
    {
        _simulation_time=t;
    }
    
    void Problem::x(const int index, const double value)
    {
        _x[index]=value;
    }


    double Problem::best_cost() const
    {
        return _best_cost;
    }
    
    Problem::~Problem()
    {
        delete [] _x;
    }

    // Solution --------------------------------------------------------------
    
    Solution::Solution (const Problem& pbm):
        _pbm(pbm),
        _current(pbm.dimension()),
        _best(pbm.dimension()),
        _velocity(pbm.dimension()),
        _current_fitness(infinity()),
        _best_fitness(infinity())
    {}

    const Problem& Solution::pbm() const
    {
        return _pbm;
    }

    Solution::Solution(const Solution& sol):
        _pbm(sol.pbm())
    {
        *this=sol;
    }

    istream& operator>> (istream& is, Solution& sol)
    {
        for (int i=0;i<sol.pbm().dimension();i++)
            is >> sol._current[i];

        for (int i=0;i<sol.pbm().dimension();i++)
            is >> sol._best[i];


        for (int i=0;i<sol.pbm().dimension();i++)
            is >> sol._velocity[i];

        return is;
    }

    ostream& operator<< (ostream& os, const Solution& sol)
    {

        for (int i=0;i<sol.pbm().dimension();i++)
            os << " " << sol._current[i];
        os << endl;
        /*for (int i=0;i<sol.pbm().dimension();i++)
                    os << " " << sol._best[i];
            os << endl;
            for (int i=0;i<sol.pbm().dimension();i++)
                    os << " " << sol._velocity[i];
            os << endl;*/

        return os;
    }

    NetStream& operator << (NetStream& ns, const Solution& sol)
    {

        ns << sol._current_fitness;
        ns << sol._best_fitness;
        for (int i=0;i<sol._current.size();i++)
            ns << sol._current[i];
        for (int i=0;i<sol._best.size();i++)
            ns << sol._best[i];
        for (int i=0;i<sol._velocity.size();i++)
            ns << sol._velocity[i];
        return ns;
    }


    NetStream& operator >> (NetStream& ns, Solution& sol)
    {
        ns >> sol._current_fitness;
        ns >> sol._best_fitness;
        for (int i=0;i<sol._current.size();i++)
            ns >> sol._current[i];
        for (int i=0;i<sol._best.size();i++)
            ns >> sol._best[i];
        for (int i=0;i<sol._velocity.size();i++)
            ns >> sol._velocity[i];
        return ns;
    }


    Solution& Solution::operator= (const Solution &sol)
    {
        _current_fitness = sol._current_fitness;
        _current = sol._current;
        _best    = sol._best;
        _velocity= sol._velocity;

        return *this;
    }

    bool Solution::operator== (const Solution& sol) const
    {
        if (sol.pbm() != _pbm) return false;
        return true;
    }

    bool Solution::operator!= (const Solution& sol) const
    {
        return !(*this == sol);
    }


    void alarmHandler(int sig){
        system("killall -e ns");
    }


    void Solution::best_to_xml(char * file)
    {
        int cont=0;
        /*Mapping XML additional file with new tlLogic tags*/
        ofstream fs(file);

        fs << "<add>" << endl;

        for (int i=0;i<pbm().n_tl_logic();i++)
        {
            fs << "   <tlLogic id=\"" <<pbm().tl_logic(i).id << "\" type=\"static\" programID=\"1\" offset=\"0\">" << endl;
            for (int j=0;j<pbm().tl_logic(i).n_phases;j++)
            {
                if ((int)current(cont)<5)
                    current(cont)= 5.0;//(double)rand_int(5,60);
                else if ((int)current(cont)>40)
                    current(cont)=40.0;//(double)rand_int(5,60);
                fs << "       <phase duration=\"" << (int)current(cont) << "\" state=\"" << pbm().tl_logic(i).phases[j] << "\"/>" << endl;
                cont++;
            }
            fs << "   </tlLogic>" << endl;
        }
        fs << "</add>" << endl;
        fs.close();
    }

    double Solution::fitness()
    {
        double fitness = 0.0;
        int cont = 0;
        fstream file;

        /*Mapping XML additional file with new tlLogic tags*/
        char xmlfile[200];
        sprintf(xmlfile,"tl2/%s/%d/tlLogic.add.xml",pbm().path(),pbm().n_tl_logic());
        //printf("Solution::fitness, pbm().path(): %s, pbm().n_tl_logitc(): %d", pbm().path(),pbm().n_tl_logic());
        ofstream fs(xmlfile);

        time_t t = time(0);   // get time now
        fs << "<add> <!-- edited at: " << asctime(localtime(&t)) <<" -->" << endl;

        for (int i=0;i<pbm().n_tl_logic();i++)
        {
            fs << "   <tlLogic id=\"" <<pbm().tl_logic(i).id << "\" type=\"static\" programID=\"1\" offset=\"0\">" << endl;
            for (int j=0;j<pbm().tl_logic(i).n_phases;j++)
            {
                if ((int)current(cont)<5)
                    current(cont)= 5.0;
                else if ((int)current(cont)>50)
                    current(cont)=50.0;
                fs << "       <phase duration=\"" << (int)current(cont) << "\" state=\"" << pbm().tl_logic(i).phases[j] << "\"/>" << endl;
                cont++;
            }
            fs << "   </tlLogic>" << endl;
        }
        fs << "</add>" << endl;

        fs.close();

        /********************* RUNNING SUMO SIMULAITON *********************/
        char order[400];


        //char debugOutPath[200];
        //sprintf(debugOutPath,"debug.txt",pbm().path(),pbm().n_tl_logic());
        // ofstream ds(debugOutPath);


        /* CALL THE SUMO SIMULATOR AND SET A NEW TL_LOGIC SOLUTION (PHASE'S DURATION)*/
        /* *
         * Simulation time: 1600
         * n_tl_logic: 2, n_total_phases: 16, n_vehicles: 500
         * path: 2-intersections, instance: 2
         * *
         */

        //# /bin/bash $0=loop.sh $1=c2smalaga.sumo.cfg $2=malaga-alameda/ $3=tl-logic.add.xml $4=output-tripinfos.xml $5./ $6=200 $7=250
        sprintf(order,"bash loop.sh %s.%d.sumo.cfg tl2/%s/%d/ tlLogic.add.xml output-tripinfos.xml ./ %d %d",
                pbm().instance(),pbm().n_vehicles(),pbm().path(),pbm().n_tl_logic(),pbm().n_vehicles(),pbm().simulation_time());

        //cout << "order: " << order << endl;
        //ds << order << endl;
        //ds.close();

        signal(SIGALRM, alarmHandler);
        alarm(600);

        /*
        cout << "starting to execute loop.sh" << endl;
        FILE *sumoComm = popen(order, "r");
        if (!sumoComm) { cout << "returning current_fitness() in executing loop.sh" << endl; _current_fitness = current_fitness(); }

        char bashOutput[1024];
        char *line_p = fgets(bashOutput, sizeof(bashOutput), sumoComm);
        cout << "line_p: " << line_p << endl;
        sscanf(line_p,"%lf",&fitness);
        cout << "fitness: " << fitness << endl;
        pclose(sumoComm);*/

        if(system(order)!=0)
            _current_fitness = current_fitness();
        else{
            file.open("res.txt");
            file >> fitness;
            file.close();
            remove("res.txt");
            _current_fitness = fitness;
        }

        return _current_fitness;
    }

    void Solution::initialization()
    {
        int min = 5;
        int max = 50;//pbm().simulation_time();

        /*dimension=number of phases*/
        for (int i=0;i<pbm().dimension();i++){
            _current[i] = (double)(rand_int(min,max));
            _best[i] = _current[i];
            _velocity[i] = (double)(rand_int(min,max))/2.0;
        }/* end for */
    }

    double Solution::current_fitness()
    {
        return _current_fitness;
    }



    double Solution::best_fitness()
    {
        return _best_fitness;
    }

    void Solution::best_fitness(const double bf)
    {
        _best_fitness=bf;
    }

    char * Solution::to_String() const
    {
        /*char * cad;
            std::ostringstream out;
            out << _current;
            cad = new char[out.str().size()+1];
            strcpy(cad,out.str().c_str());
            return cad;*/
        return (char *)_current.get_first();
    }

    void Solution::to_Solution(char *_string_)
    {
        double *ptr =(double *)_string_;
        for (int i=0;i<_pbm.dimension();i++)
        {
            _current[i]=*ptr;
            ptr++;
        }
    }

    unsigned int Solution::size() const
    {
        return (_pbm.dimension() * sizeof(double));
    }

    double& Solution::current(const int index)
    {
        return _current[index];
    }

    double& Solution::best(const int index)
    {
        return _best[index];
    }

    double& Solution::velocity(const int index)
    {
        return _velocity[index];
    }

    void Solution::current(const int index, const double value)
    {
        _current[index]=value;
    }

    void Solution::best(const int index, const double value)
    {
        _best[index]=value;
    }


    void Solution::velocity(const int index, const double value)
    {
        _velocity[index]=value;
    }

    Rarray<double>& Solution::current()
    {
        return _current;
    }


    Rarray<double>& Solution::best()
    {
        return _best;
    }

    Rarray<double>& Solution::velocity()
    {
        return _velocity;
    }


    Solution::~Solution()
    {}

    


    // UserStatistics -------------------------------------------------------

    UserStatistics::UserStatistics ()
    {}

    ostream& operator<< (ostream& os, const UserStatistics& userstat)
    {
        //os << "\n---------------------------------------------------------------" << endl;
        //os << "                   STATISTICS OF TRIALS                     " << endl;
        //os << "------------------------------------------------------------------" << endl;

        for (int i=0;i< userstat.result_trials.size();i++)
        {
            os << endl
               << userstat.result_trials[i].trial
               << "\t" << userstat.result_trials[i].best_cost_trial
               << "\t\t" << userstat.result_trials[i].worst_cost_trial
               << "\t\t\t" << userstat.result_trials[i].nb_evaluation_best_found_trial
               << "\t\t\t" << userstat.result_trials[i].time_best_found_trial
               << "\t\t" << userstat.result_trials[i].time_spent_trial;
        }
        //os << endl << "------------------------------------------------------------------" << endl;
        return os;
    }

    UserStatistics& UserStatistics::operator= (const UserStatistics& userstats)
    {
        result_trials=userstats.result_trials;
        return (*this);
    }

    void UserStatistics::update(const Solver& solver)
    {
        if (!(solver.pid()==0 && (solver.end_trial()==true)
              && (solver.current_iteration()==solver.setup().nb_evolution_steps())))
            return;

        struct user_stat *new_stat;

        if ((new_stat=(struct user_stat *)malloc(sizeof(struct user_stat)))==NULL)
            show_message(7);
        new_stat->trial                  = solver.current_trial();
        new_stat->nb_evaluation_best_found_trial = solver.iteration_best_found_in_trial();
        new_stat->worst_cost_trial           = solver.worst_cost_trial();
        new_stat->best_cost_trial            = solver.best_cost_trial();
        new_stat->time_best_found_trial      = solver.time_best_found_trial();
        new_stat->time_spent_trial       = solver.time_spent_trial();

        result_trials.append(*new_stat);
    }

    void UserStatistics::clear()
    {
        result_trials.remove();
    }

    UserStatistics::~UserStatistics()
    {
        result_trials.remove();
    }


    // StopCondition_1 -------------------------------------------------------------------------------------

    StopCondition_1::StopCondition_1():StopCondition()
    {}

    bool StopCondition_1::EvaluateCondition(const Problem& pbm,const Solver& solver,const SetUpParams& setup)
    {
        return ((double)solver.best_cost_trial()==pbm.best_cost());
    }

    StopCondition_1::~StopCondition_1()
    {}

    //------------------------------------------------------------------------
    // Specific methods ------------------------------------------------------
    //------------------------------------------------------------------------

    bool terminateQ (const Problem& pbm, const Solver& solver,
                     const SetUpParams& setup)
    {
        StopCondition_1 stop;
        return stop.EvaluateCondition(pbm,solver,setup);
    }
}

#endif
