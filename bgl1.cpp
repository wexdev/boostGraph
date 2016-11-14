#include <iostream>
#include <fstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/detail/read_graphviz_new.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace boost;
using namespace std;


/*
  A function to display the graph based on dot format.
*/
void displayGraph(const string& fileName, const auto& graph, const dynamic_properties& dp) {
  string strDotFile = fileName + ".dot";
  ofstream dotfile(strDotFile.c_str());
  write_graphviz_dp(dotfile, graph, dp);  // generates the dot file with nodes properties for the given graph.

  string command = "dot -Tpdf " + strDotFile + " -o " + fileName + ".pdf";
  system(command.c_str());  // generates the pdf file.
  command = "evince " + fileName + ".pdf &";
  system(command.c_str());  // displays the pdf file.
}


/*
  This function generates a Boost Graph from the data read in a dot file.
  The graph can then be modified, then it is displayed.
*/ 
void testReadFromDot() {
  struct Vertex {
    string name, label, shape, fillcolor, style;  // the vertex properties.
  };

  struct Edge {
  };
  
  typedef property<graph_name_t, string> graph_p;
  typedef adjacency_list<vecS, vecS, directedS, Vertex, Edge, graph_p> graph_t;  // definition of a directed graph.
    
  graph_t graph;  // the graph instance.
  
  // Definition of the vertex properties for display with graphviz :
  dynamic_properties dp;
  dp.property("node_id",     get(&Vertex::name,  graph));
  dp.property("label",       get(&Vertex::label, graph));
  dp.property("shape",       get(&Vertex::shape, graph));
  dp.property("fillcolor",   get(&Vertex::fillcolor, graph));
  dp.property("style",       get(&Vertex::style, graph));
    
  boost::ref_property_map<graph_t*, string> gname(get_property(graph, graph_name));
  dp.property("name", gname);

  ifstream dot("inverterGraph.dot");

  if(read_graphviz(dot, graph, dp)) {
    cout << "Graph name : " << get_property(graph, graph_name) << endl;

    // here : correct under/over constraints in the graph.
    
    displayGraph("inverterGraphOutput", graph, dp);
  }
  
}




int main() { 
  testReadFromDot();
  
  return 0;
}
