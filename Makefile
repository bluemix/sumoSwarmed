include environment

all: MainSeq  MainLan 

clean:
	rm -f  MainLan MainSeq MainWan core.* *.o *% *~ *.out
	
MainSeq: MainSeq.o 
#	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS)  -o $@    
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS)  -o $@

MainLan: MainLan.o
	 $(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@  

#MainWan: MainWan.o 
#	 $(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@  
LAN:
#	$(RUN)  -v  -p4pg pgfileLan MainLan
	$(RUN)  -v  -np 2 MainLan PSO.cfg tl2/2-intersections/2/tlLogic.tmp tl2/2-intersections/2/info.500.twoIntersections.txt tl2/2-intersections/2/tlLogic.500.best-solution.xml results.txt
#WAN:
#	$(RUN)  -v  -p4pg pgfileWan MainWan

SEQ:

	./MainSeq PSO.cfg tl2/2-intersections/2/tlLogic.tmp tl2/2-intersections/2/info.500.twoIntersections.txt tl2/2-intersections/2/tlLogic.500.best-solution.xml  results.txt
