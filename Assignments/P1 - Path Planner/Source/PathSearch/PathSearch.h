
#include "../platform.h" // This file will make exporting DLL symbols simpler for students.
#include "vector"
#include "../Framework/TileSystem/TileMapUtility.h"
#include <list>
#include <iostream>
#include <map>
#include <cmath>
#include <queue> 
#include <chrono>
#include <crtdbg.h>
#include "../PriorityQueue.h"

using namespace std;


namespace ufl_cap4053
{
	namespace searches
	{

		struct Edge {
			double weight = 0;
			Tile* endpoint = NULL;
		public:
			DLLEXPORT Edge();
		
		};


		struct SearchSpace {
			Tile* vertex = NULL;
			vector<Edge*> edges;
			double x_cor = 0.0;
			double y_cor = 0.0;

			

		public:
			DLLEXPORT SearchSpace();
		};

		struct PlannerHelp {

			Tile* vertex = NULL;
			PlannerHelp* parent = NULL;
			double heuristicCost = 0;
			double givenCost = 0;
			double finalCost = 0;

		public:
			DLLEXPORT PlannerHelp();

		
		};

		class PathSearch
		{
			
			PriorityQueue<PlannerHelp*> open;
			TileMap* tile_map = NULL;
			Tile* endNow = NULL;
			Tile* startHere = NULL;
			bool done = false;
			vector<vector<Tile*>> graph;
			vector<vector<SearchSpace*>> vertexGraph;
			map<Tile*, PlannerHelp*> visited;
			vector<Tile const*> sol;
			double hureist = 0;
			double endX = 0;
			double endY = 0;
			double startX = 0;
			double startY = 0;
		// CLASS DECLARATION GOES HERE
			public:
				DLLEXPORT PathSearch(); // EX: DLLEXPORT required for public methods - see platform.h

				DLLEXPORT ~PathSearch();

				DLLEXPORT void load(TileMap* _tileMap);

				DLLEXPORT void initialize(int startRow, int startCol, int goalRow, int goalCol);

				DLLEXPORT void update(long timeslice);

				DLLEXPORT void shutdown();

				DLLEXPORT void unload();

				DLLEXPORT bool isDone() const;

				DLLEXPORT vector<Tile const*> const getSolution() const;

				
				


		};

		bool isGreaterThan2(PlannerHelp* const& lhs, PlannerHelp* const& rhs);

		
	}
}  // close namespace ufl_cap4053::searches


