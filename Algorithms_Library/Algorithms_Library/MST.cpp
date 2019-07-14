#include "MST.hpp"

using namespace Algorithms_MST;

////////////////////////////////////////////////////
////////////////////////////////////////////////////
/*
	_MST_Element CLASS METHOD'S BODIES
*/
////////////////////////////////////////////////////
////////////////////////////////////////////////////


MST::_MST_Element::_MST_Element() :
	_Connections_size(0),
	Verticle(0),
	Cost(0),
	Edge(0)
{
	this->Connections = new int[this->_Connections_size];
	for (size_t i = 0; i < this->_Connections_size; ++i)
	{
		Connections[i] = 0;
	}
}

MST::_MST_Element::_MST_Element(const int Verticle, const int Cost, const int Edge) :
	_Connections_size(0),
	Verticle(Verticle),
	Cost(Cost),
	Edge(Edge)
{
	this->Connections = new int[this->_Connections_size];
	for (size_t i = 0; i < this->_Connections_size; ++i)
	{
		Connections[i] = 0;
	}
}

MST::_MST_Element::_MST_Element(const _MST_Element& Object) :
	_Connections_size(Object._Connections_size),
	Verticle(Object.Verticle),
	Cost(Object.Cost),
	Edge(Object.Edge)
{
	this->Connections = new int[this->_Connections_size];
	for (size_t i = 0; i < this->_Connections_size; ++i)
	{
		Connections[i] = 0;
	}
}

void MST::_MST_Element::set_connections_size(const size_t & _Connections_size)
{
	if (this->_Connections_size != 0)
	{
		delete[] this->Connections;
	}
	this->_Connections_size = _Connections_size;
	this->Connections = new int[this->_Connections_size];
	for (size_t i = 0; i < this->_Connections_size; ++i)
	{
		Connections[i] = 0;
	}
}

void MST::_MST_Element::set_connection(const int value, const size_t counter)
{
	this->Connections[counter] = value;
}

void MST::_MST_Element::set_way(const int destination, const int way_lenght)
{
	this->Connections[(destination - 1)] = way_lenght;
}

void MST::_MST_Element::set_verticle(const int verticle)
{
	this->Verticle = verticle;
}

void MST::_MST_Element::set_cost(const int cost)
{
	this->Cost = cost;
}

void MST::_MST_Element::set_edge(const int edge)
{
	this->Edge = edge;
}

MST::_MST_Element & MST::_MST_Element::operator=(const _MST_Element& Object)
{
	if (this != _STD addressof(Object))
	{
		this->Verticle = Object.Verticle;
		this->Cost = Object.Cost;
		this->Edge = Object.Edge;
		this->_Connections_size = Object._Connections_size;
		delete[] this->Connections;
		this->Connections = new int[this->_Connections_size];
		for (size_t i = 0; i < this->_Connections_size; ++i)
		{
			this->Connections[i] = 0;
		}
	}
	return *this;
}

constexpr int MST::_MST_Element::get_verticle() const
{
	return this->Verticle;
}

constexpr int MST::_MST_Element::get_cost() const
{
	return this->Cost;
}

constexpr int MST::_MST_Element::get_edge() const
{
	return this->Edge;
}

constexpr size_t MST::_MST_Element::get_connections_size() const
{
	return this->_Connections_size;
}

constexpr int & MST::_MST_Element::get_connections_array(const size_t counter) const
{
	return this->Connections[counter];
}

MST::_MST_Element::~_MST_Element()
{
	delete[] this->Connections;
	_Connections_size = 0;
	Edge = 0;
	Cost = 0;
	Verticle = 0;
}


////////////////////////////////////////////////////
////////////////////////////////////////////////////
/*
	MST CLASS METHOD'S BODIES
*/
////////////////////////////////////////////////////
////////////////////////////////////////////////////


MST::MST() :
	_Graph_lenght(0),
	_Q_lenght(0),
	_Q_counter(0),
	_Prims_Matrix_lenght(0)
{
	this->Graph = new _MST_Element[this->_Graph_lenght];
	this->Q = new int[this->_Q_lenght];
	this->Prims_Matrix = new _MST_Element[this->_Prims_Matrix_lenght];
}

MST::MST(const size_t _Graph_lenght) :
	_Graph_lenght(_Graph_lenght),
	_Q_lenght(_Graph_lenght),
	_Q_counter(0),
	_Prims_Matrix_lenght(_Graph_lenght)
{
	this->Graph = new _MST_Element[this->_Graph_lenght];
	this->Q = new int[this->_Q_lenght];
	this->Prims_Matrix = new _MST_Element[this->_Prims_Matrix_lenght];
	for (size_t i = 0; i < this->_Graph_lenght; ++i)
	{
		this->Graph[i].set_connections_size(this->_Graph_lenght);
		this->Q[i] = static_cast<int>((i + 1));
		this->Prims_Matrix[i].set_verticle(static_cast<int>((i + 1)));
		this->Prims_Matrix[i].set_cost(0);
		this->Prims_Matrix[i].set_edge(0);
	}
}

MST::MST(const MST& Object) :
	_Graph_lenght(Object._Graph_lenght),
	_Prims_Matrix_lenght(Object._Prims_Matrix_lenght),
	_Q_lenght(Object._Q_lenght),
	_Q_counter(Object._Q_counter)
{
	this->Graph = new _MST_Element[this->_Graph_lenght];
	this->Q = new int[this->_Q_lenght];
	this->Prims_Matrix = new _MST_Element[this->_Prims_Matrix_lenght];
	for (size_t i = 0; i < this->_Graph_lenght; ++i)
	{
		this->Graph[i].set_connections_size(this->_Graph_lenght);
		this->Q[i] = static_cast<__int32>((i + 1));
		this->Prims_Matrix[i].set_verticle(static_cast<int>((i + 1)));
		this->Prims_Matrix[i].set_cost(0);
		this->Prims_Matrix[i].set_edge(0);
	}
}

void MST::push(const int value, const int destination, const int way_lenght)
{
	this->Graph[(value - 1)].set_way(destination, way_lenght);
}

void MST::push_directions(const int from, const int to, const int way_lenght)
{
	Destinations.emplace_back(std::make_pair(std::make_pair(from, to), way_lenght));
}

void MST::minimal_spanning_tree_creator(const int the_beginning)
{
	//Clear the Prims Matrix
	F.clear();
	for (size_t i = 0; i < _Prims_Matrix_lenght; ++i)
	{
		Prims_Matrix[i].set_cost(0);
		Prims_Matrix[i].set_edge(0);
		Q[i] = static_cast<int>((i + 1));
	}
	_Q_counter = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	int current_verticle = (the_beginning - 1);	//choose the beginning (by position in array (nr index))
	int the_smallest_cost = 0;
	int the_smallest_cost_position = 0;
	while (_Q_counter < static_cast<int>(_Q_lenght))
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		//Deleting from Q
		Q[(current_verticle)] = 0;
		++_Q_counter;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		//Adding to F (Forest)
		if (Prims_Matrix[(current_verticle)].get_edge() != 0)
		{
			F.emplace_back(_MST_Element(Prims_Matrix[current_verticle].get_verticle(), 0, 0));
			F.emplace_back(_MST_Element(Prims_Matrix[current_verticle].get_verticle(), 0, Prims_Matrix[current_verticle].get_edge()));
		}
		else
		{
			F.emplace_back(_MST_Element(Prims_Matrix[current_verticle].get_verticle(), 0, 0));
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////
		//Setting the Prim's Matrix
		for (size_t j = 0; j < Graph[current_verticle].get_connections_size(); ++j)
		{
			if (Graph[current_verticle].get_connections_array(j) != 0 && Q[j] == Prims_Matrix[j].get_verticle())
			{
				if ((Prims_Matrix[j].get_cost() >= Graph[current_verticle].get_connections_array(j)) || (Prims_Matrix[j].get_cost() == 0))
				{
					Prims_Matrix[j].set_cost(Graph[current_verticle].get_connections_array(j));
					Prims_Matrix[j].set_edge((current_verticle + 1));
				}
			}
			else
			{
				continue;
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////
		//Seeking for the smallest element in Prim's Matrix
		for (size_t i = 0; i < _Prims_Matrix_lenght; ++i)
		{
			if (Prims_Matrix[i].get_cost() <= the_smallest_cost && Q[i] == Prims_Matrix[i].get_verticle())
			{
				the_smallest_cost = Prims_Matrix[i].get_cost();
				the_smallest_cost_position = static_cast<int>(i);
			}
		}
		current_verticle = the_smallest_cost_position;
		the_smallest_cost = 0;
		the_smallest_cost_position = 0;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		//End of Loop
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
}

void MST::get_results()
{
	for (typename std::vector<std::pair<std::pair<int, int>, int>>::const_iterator vec_iterator = Destinations.begin(); vec_iterator != Destinations.end(); ++vec_iterator)
	{
		find_way(vec_iterator->first.first, vec_iterator->first.second, vec_iterator->second);
	}
}

void MST::get_results(std::ostream & out)
{
	for (typename std::vector<std::pair<std::pair<int, int>, int>>::const_iterator vec_iterator = Destinations.begin(); vec_iterator != Destinations.end(); ++vec_iterator)
	{
		out << find_way(vec_iterator->first.first, vec_iterator->first.second, vec_iterator->second) << '\n';
	}
}

constexpr unsigned __int32 MST::find_way(const int from, const int to, const int way_lenght)
{
	if (from == to)
	{
		return 0;
	}
	else
	{
		int* visited = new int[this->_Graph_lenght];
		for (size_t i = 0; i < _Graph_lenght; ++i)
		{
			visited[i] = 0;
		}

		double the_smallest_way = -999999999;
		int current_verticle = (from - 1);
		int destination_verticle = to;
		bool founded_destination = false;
		int from_he = 0;
		int to_he = 0;

		if (from < to)
		{
			from_he = to;
			to_he = from;
		}
		else
		{
			from_he = from;
			to_he = to;
		}

		minimal_spanning_tree_creator(to_he);	//create MST for this case

		current_verticle = Prims_Matrix[(from_he - 1)].get_edge();
		if (the_smallest_way < Prims_Matrix[(from_he - 1)].get_cost())
		{
			the_smallest_way = Prims_Matrix[(from_he - 1)].get_cost();
		}
		visited[(current_verticle)-1] = Prims_Matrix[(from_he - 1)].get_verticle();
		while (founded_destination == false)
		{
			for (int i = _Prims_Matrix_lenght - 1; i >= 0; --i)
			{
				if (Prims_Matrix[i].get_verticle() == (current_verticle))
				{
					visited[(current_verticle)-1] = current_verticle;
					current_verticle = Prims_Matrix[i].get_edge();
					if (the_smallest_way < Prims_Matrix[i].get_cost())
					{
						the_smallest_way = Prims_Matrix[i].get_cost();
					}
					break;
				}
				if ((current_verticle) == Prims_Matrix[(to_he - 1)].get_verticle())
				{
					founded_destination = true;
					break;
				}
			}

		}
		the_smallest_way *= -1;
		the_smallest_way -= 1;
		double result = ceil(static_cast<double>(((static_cast<double>(way_lenght) / (the_smallest_way)))));
		delete[] visited;
		return static_cast<unsigned __int32>(result);
	}
	return static_cast<unsigned __int32>(0);
}

MST& MST::operator=(const MST& Object)
{
	if (this != &Object)
	{
		this->_Graph_lenght = Object._Graph_lenght;
		this->_Q_counter = Object._Q_counter;
		this->_Q_lenght = Object._Q_lenght;
		this->_Prims_Matrix_lenght = Object._Prims_Matrix_lenght;
		delete[] this->Graph;
		delete[] this->Q;
		delete[] this->Prims_Matrix;
		this->F.clear();
		this->Graph = new _MST_Element[this->_Graph_lenght];
		this->Q = new int[this->_Q_lenght];
		this->Prims_Matrix = new _MST_Element[this->_Prims_Matrix_lenght];
		for (size_t i = 0; i < this->_Graph_lenght; ++i)
		{
			this->Graph[i].set_connections_size(this->_Graph_lenght);
			this->Q[i] = static_cast<int>((i + 1));
			this->Prims_Matrix[i].set_verticle(static_cast<int>((i + 1)));
			this->Prims_Matrix[i].set_cost(0);
			this->Prims_Matrix[i].set_edge(0);
		}
	}
	return *this;
}

MST::~MST()
{
	delete[] Graph;
	delete[] Q;
	delete[] Prims_Matrix;
	F.clear();
	_Graph_lenght = 0;
	_Q_counter = 0;
	_Q_lenght = 0;
	_Prims_Matrix_lenght = 0;
}