CC=/usr/local/bin/gcc
CXX=/usr/local/bin/g++
OBJS=main.o Auxiliaries.o graphCalculatorParser.o Exception.o GraphFactory.o GraphCalculator.o
SWIG_OBJS=graph.o Auxiliaries.o Exception.o GraphFactory.o
EXEC=gcalc
COMP_FLAGS=-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG
# SWIG_FLAGS=-std=c++11 -Wall -Werror -fPIC -pedantic-errors -DNDEBUG


$(EXEC): $(OBJS)
	$(CXX) -std=c++11 $(COMP_FLAGS) $(OBJS) -o $@

libgraph.a: $(SWIG_OBJS)
	ar -rs $@ $^
 
Auxiliaries.o: Auxiliaries.cpp Auxiliaries.h Exception.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

main.o: main.cpp graphCalculatorParser.h GraphCalculator.h GraphFactory.h Exception.h Auxiliaries.h
	$(CXX) -c $(COMP_FLAGS) $*.cpp

graphCalculatorParser.o: graphCalculatorParser.cpp graphCalculatorParser.h GraphCalculator.h GraphFactory.h Exception.h Auxiliaries.h
	$(CXX) -c $(COMP_FLAGS) $*.cpp

Exception.o: Exception.cpp Exception.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

GraphFactory.o: GraphFactory.cpp GraphFactory.h Auxiliaries.h Exception.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

GraphCalculator.o: GraphCalculator.cpp GraphCalculator.h GraphFactory.h Auxiliaries.h Exception.h
	$(CXX) -c $(COMP_FLAGS) $*.cpp

graph.o: graph.cpp graph.h GraphFactory.h Auxiliaries.h Exception.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

clean :
	rm -f $(OBJS) $(EXEC) libgraph.a _graph.so graph.py graph_wrap.c graph_wrap.cpp graph.o

tar :
	zip -r gcalc.zip ./