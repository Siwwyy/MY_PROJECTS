/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *					I hope that alghoritm will make right work
 *							Greetings for everyone!
 *						Hash_Table organized array by Key
*/
#pragma once
#ifndef _ALGORITHMS_LIBRARY_MST_HPP_
#define _ALGORITHMS_LIBRARY_MST_HPP_

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

namespace Algorithms_MST
{
	using std::cerr;
	using std::endl;
	using std::cout;


	class MST
	{
	private:

		class _MST_Element
		{
		private:
			//////////////////////////////////////////////////////////////////////////////
			/*
				ZMIENNE PRIVATE
			*/
			int Verticle;
			int Cost;
			int Edge;
			//////////////////////////////////
			int* Connections;
			size_t _Connections_size;
			//////////////////////////////////////////////////////////////////////////////
		public:
			//////////////////////////////////////////////////////////////////////////////
			/*
				KONSTRUKTORY PUBLIC
			*/
			_MST_Element();
			_MST_Element(const int Verticle, const int Cost, const int Edge);
			_MST_Element(const _MST_Element & Object);
			//////////////////////////////////////////////////////////////////////////////
			/*
				FUNKCJE PUBLIC
			*/

			//////////////////////////////////////////////////////////////////////////////
			/*
				SETTERY PUBLIC
			*/
			void set_connections_size(const size_t & _Connections_size);
			void set_connection(const int value, const size_t counter);
			void set_way(const int destination, const int way_lenght);
			void set_verticle(const int verticle);
			void set_cost(const int cost);
			void set_edge(const int edge);
			//////////////////////////////////////////////////////////////////////////////
			/*
				OPERATORY PUBLIC
			*/
			//JEDNOARGUMENTOWE
			_MST_Element & operator=(const _MST_Element & Object);
			//DWUARGUMENTOWE
			//////////////////////////////////////////////////////////////////////////////
			/*
				GETTERY PUBLIC
			*/
			constexpr int get_verticle() const;
			constexpr int get_cost() const;
			constexpr int get_edge() const;
			constexpr size_t get_connections_size() const;
			constexpr int & get_connections_array(const size_t counter) const;
			//////////////////////////////////////////////////////////////////////////////
			/*
				DESTRUKTOR
			*/
			virtual ~_MST_Element();
		};

		//////////////////////////////////////////////////////////////////////////////
		/*
			ZMIENNE PRIVATE
		*/
		/////////////////////////////////////////////////////////////////////////
		_MST_Element * Graph;
		size_t _Graph_lenght;
		/////////////////////////////////////////////////////////////////////////
		_MST_Element * Prims_Matrix;
		size_t _Prims_Matrix_lenght;
		/////////////////////////////////////////////////////////////////////////
		int * Q;
		size_t _Q_lenght;
		int _Q_counter;
		/////////////////////////////////////////////////////////////////////////
		std::vector<_MST_Element> F;
		//////////////////////////////////////////////////////////////////////////////
		std::vector<std::pair<std::pair<int, int>, int>> Destinations;
		//////////////////////////////////////////////////////////////////////////////
		/*
			FUNKCJE PRIVATE
		*/
		void find_way(const int from, const int to, const int way_lenght);
		//////////////////////////////////////////////////////////////////////////////
	public:
		//////////////////////////////////////////////////////////////////////////////
		/*
			KONSTRUKTORY PUBLIC
		*/
		MST();
		MST(const size_t _Graph_lenght);
		MST(const MST & Object);
		//////////////////////////////////////////////////////////////////////////////
		/*
			FUNKCJE PUBLIC
		*/
		void push(const int value, const int destination, const int way_lenght);
		void push_directions(const int from, const int to, const int way_lenght);
		void minimal_spanning_tree_creator(const int the_beginning);
		void get_results();
		//////////////////////////////////////////////////////////////////////////////
		/*
			SETTERY PUBLIC
		*/

		//////////////////////////////////////////////////////////////////////////////
		/*
			GETTERY PUBLIC
		*/
		//////////////////////////////////////////////////////////////////////////////

		/*
			OPERATORY PUBLIC
		*/
		//JEDNOARGUMENTOWE
		MST& operator=(const MST& Object);
		//DWUARGUMENTOWE
		//////////////////////////////////////////////////////////////////////////////
		/*
			DESTRUKTOR
		*/
		virtual ~MST();
	};

}

#endif /* _ALGORITHMS_LIBRARY_MST_HPP_ */