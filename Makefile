
exec : bgl1.cpp
	g++  bgl1.cpp -o exec -std=c++14 -lboost_graph

clean :
	rm -f exec *~
