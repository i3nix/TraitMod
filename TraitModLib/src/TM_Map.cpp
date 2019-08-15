#include "TM_Map.h"
#include "TM_Exception.h"
#include <algorithm>

namespace TMLib
{
	TM_Map::TM_Map()
	{	
	}

	TM_Map::~TM_Map()
	{	
	}

	void TM_Map::AddLocation(const char* name)
	{
		mLocations.push_back(std::make_shared<TM_Location>(name));
		mAdjacencyList.push_back(std::list<TM_Road>());
	}

	void TM_Map::AddRoad(const char* loc1, const char* loc2, const int dist)
	{
		mAdjacencyList[GetLocationID(loc1)].push_back(TM_Road(GetLocationID(loc2),dist));
		mAdjacencyList[GetLocationID(loc2)].push_back(TM_Road(GetLocationID(loc1),dist));
	}

	const int TM_Map::GetDistance(const char* loc1, const char* loc2) const
	{
		for(std::list<TM_Road>::const_iterator it = mAdjacencyList[GetLocationID(loc1)].begin(); it != mAdjacencyList[GetLocationID(loc1)].end(); it++)
			if(mLocations[it->first]->GetName() == loc2)
				return it->second;
		return std::numeric_limits<int>::max();
	}

	const int TM_Map::GetLocationID(const char* loc) const
	{
		for(int t = 0; t < mLocations.size(); t++)
			if(mLocations[t]->GetName() == loc)
				return t;
		throw TM_Exception("Location not found","TM_Map","TM_Map::GetLocationID");
	}

	const std::shared_ptr<TM_Location> TM_Map::GetLocation(const char* loc) const
	{
		for(int t = 0; t < mLocations.size(); t++)
			if(mLocations[t]->GetName() == loc)
				return mLocations[t];
		throw TM_Exception("Location not found","TM_Map","TM_Map::GetLocation");
	}

	std::list<std::shared_ptr<TM_Location> > TM_Map::FindPath(const char* loc1, const char* loc2)
	{
		int LocNumber = (int)mLocations.size();
		int SrcLoc = GetLocationID(loc1);
		int DstLoc = GetLocationID(loc2);
		std::vector<TM_Road> Distances(LocNumber, TM_Road(0,std::numeric_limits<int>::max()));
		std::vector<int> Prevs(LocNumber);
		std::vector<bool> Visited(LocNumber,false);
		for(int t = 0; t < LocNumber; t++)
		{
			Distances[t].first = t;
			Prevs[t] = t;
		}
		Distances[SrcLoc].second = 0;
		Prevs[SrcLoc] = -1;

		for(int t = 0; t < LocNumber - 1; t++)
		{
			std::make_heap(Distances.begin() + t, Distances.end(),FindPathComparator);
			int CurLoc = Distances[t].first;
			Visited[CurLoc] = true;
			for(std::list<TM_Road>::iterator it = mAdjacencyList[CurLoc].begin(); it != mAdjacencyList[CurLoc].end(); it++)
			{
				int Index = -1;
				for(int i = 0; i < LocNumber; i++)
					if(Distances[i].first == it->first)
					{
						Index = i;
						break;
					}

				if(Visited[it->first] == false && Distances[t].second + it->second < Distances[Index].second)
				{
					Distances[Index].second = Distances[t].second + it->second;
					Prevs[it->first] = CurLoc;
				}
			}

		}

		std::list<std::shared_ptr<TM_Location> > path;
		do
		{
			path.push_front(mLocations[DstLoc]);
			DstLoc = Prevs[DstLoc];
		}
		while(DstLoc != -1);
		return path;
	}

	bool FindPathComparator(const TM_Road &a, const TM_Road &b)
	{
		return (a.second >= b.second);
	}

	TM_Map& TM_Map::GetMap()
	{
		return mMap;
	}

	void TM_Map::Init()
	{
		for(int t = 0; t < TM_LocationCount; t++)
			mMap.AddLocation(TM_LocationNames[t].c_str());
		for(int t = 0; t < TM_LocationCount - 1; t++)
			for(int i = t + 1; i < TM_LocationCount; i++)
				mMap.AddRoad(TM_LocationNames[t].c_str(), TM_LocationNames[i].c_str(), 10);
	}

	TM_Map TM_Map::mMap = TM_Map();
};
