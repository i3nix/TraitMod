#pragma once
#include <vector>
#include <list>

#include "TM_Location.h"

namespace TMLib
{
	//ID and distance
	typedef std::pair<int, int> TM_Road;

	/*
		A map is a graph, where each verticle is a location, and each edge is a road
	*/
	class TM_Map
	{
	public:
															TM_Map();
															~TM_Map();	
		void												AddLocation(const char* loc);
		void												AddRoad(const char* loc1, const char* loc2, const int dist);

		const int											GetDistance(const char* loc1, const char* loc2) const;
		const std::shared_ptr<TM_Location>					GetLocation(const char* loc) const;
		//Dijkstra's algorithm using a heap
		std::list<std::shared_ptr<TM_Location> >			FindPath(const char* loc1, const char* loc2);
		static TM_Map&										GetMap();

		static void											Init();
	private:
		std::vector<std::shared_ptr<TM_Location> >			mLocations;
		//Each element of a vector is a list of all neighbors for a single location and distances between them. 
		std::vector<std::list<TM_Road> >					mAdjacencyList;

		const int											GetLocationID(const char* loc) const;

		static TM_Map										mMap;
	};

	bool FindPathComparator(const TM_Road &a, const TM_Road &b);
};
