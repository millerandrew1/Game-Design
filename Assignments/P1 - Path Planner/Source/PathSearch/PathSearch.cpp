#include "PathSearch.h"
namespace ufl_cap4053
{
	namespace searches
	{

		PathSearch::PathSearch() : open(isGreaterThan2) {


		}




		PathSearch::~PathSearch()
		{




			for (auto iter = visited.begin(); iter != visited.end(); iter++) {
				delete iter->second;
			}
			visited.clear();


			while (!open.empty()) {
				PlannerHelp* curr = open.front();
				open.pop();

			}

			_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

		}


		DLLEXPORT void PathSearch::load(TileMap* _tileMap)
		{

			tile_map = _tileMap;
			int width = tile_map->getRowCount();
			int col = tile_map->getColumnCount();
			graph.resize(col, vector<Tile*>(width));
			vertexGraph.resize(col, vector<SearchSpace*>(width));
			for (int i = 0; i < col; i++) {
				for (int j = 0; j < width; j++) {
					graph[i][j] = tile_map->getTile(j, i);
				}
			}
			for (int i = 0; i < col; i++) {
				for (int j = 0; j < width; j++) {
					SearchSpace* curr = new SearchSpace;
					curr->vertex = graph[i][j];
					curr->x_cor = curr->vertex->getXCoordinate();
					curr->y_cor = curr->vertex->getYCoordinate();
					vertexGraph[i][j] = curr;
					for (int c = i - 1; c <= i + 1; c++) {
						for (int r = j - 1; r <= j + 1; r++) {
							if ((0 <= r) && (0 <= c) && (r < width) && (c < col) && !(r == j && c == i)) {
								if (((j % 2 == 0 && (c == i + 1 && (r == j - 1 || r == j + 1))) || (j % 2 == 1 && (c == i - 1 && (r == j - 1 || r == j + 1))))) {
									continue;
								}
								Edge* edge = new Edge;
								edge->endpoint = graph[c][r];
								edge->weight = graph[c][r]->getWeight();
								curr->edges.push_back(edge);

							}
						}
					}
				}

			}
		}
		DLLEXPORT void PathSearch::initialize(int startRow, int startCol, int goalRow, int goalCol)
		{
			
			//Tile* start = tile_map->getTile(startRow, startCol);
			SearchSpace* searchStart = vertexGraph[startCol][startRow];
			Tile* start = searchStart->vertex;
			start->setFill(4278255360);
			//Tile* end = tile_map->getTile(goalRow, goalCol);
			SearchSpace* searchEnd = vertexGraph[goalCol][goalRow];
			Tile* end = searchEnd->vertex;
			end->setMarker(4286513152);
			endNow = end;
			startHere = start;
			PlannerHelp* search = new PlannerHelp();
			search->vertex = start;
			open.push(search);
			visited[start] = open.front();
			startX = searchStart->x_cor;
			startY = searchStart->y_cor;
			
			endX = searchEnd->x_cor;
			endY = searchEnd->y_cor;


			double huristic = (sqrt(pow((endY - startY), 2) + pow(endX - startX, 2)))*1.2;
			hureist = huristic;

			visited[start]->heuristicCost = huristic;
			open.front()->givenCost = 0;
			open.front()->heuristicCost = huristic;
			open.front()->finalCost = huristic;
			done = false;
			
			
			
		}
		DLLEXPORT void PathSearch::update(long timeslice)
		{
			
			bool time = true;
			auto now_time = chrono::high_resolution_clock::now();
			if (timeslice < 0) {
				time = false;
			}
			
			while (time) {
				if (timeslice == 0) {
					time = false;
				}
				else {
					auto end_time = chrono::high_resolution_clock::now();
					auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - now_time);
					auto diff = duration.count();
					auto num = (timeslice - diff);
					if (num < 0) {
						time = false;
					}
					
				}
				PlannerHelp* curr;
				curr = open.front();
				open.pop();
				curr->vertex->setFill(4294951115);
				Tile* now = curr->vertex;
			//	cout << "HUR: " << curr->heuristicCost << endl;
				//cout << "Dist: " << curr->givenCost << endl;
 				//cout << "Final: " <<curr->finalCost << endl;
				
				if (now == endNow) {
					
					PlannerHelp* temp = curr;
					while (temp->vertex != startHere) {
						temp->vertex->addLineTo(temp->parent->vertex, 251658495);
						sol.push_back(temp->vertex);
						temp = temp->parent;
					}
					sol.push_back(temp->vertex);
					done = true;
					cout << "Final Cost: " << curr->finalCost << endl;
					
					cout << "Solution Size: " << sol.size() << endl;
					return;
				}
				int row = tile_map->getRowCount();
				int col = tile_map->getColumnCount();
				int tile_row = now->getRow();
				int tile_col = now->getColumn();
				int count = 0;

				double newX = curr->vertex->getXCoordinate();
				double newY = curr->vertex->getYCoordinate();
				
				SearchSpace* currS = vertexGraph[tile_col][tile_row];
				for (int i = 0; i < currS->edges.size(); i++) {
					Tile* next = currS->edges[i]->endpoint;
					double x = next->getXCoordinate();
					double y = next->getYCoordinate();
					double disStart = sqrt(pow((y - newY), 2) + pow(x - newX, 2));
					double tempGivenCost = curr->givenCost + currS->edges[i]->weight * disStart;
					if (currS->edges[i]->weight != 0) {
						if (visited[next] == NULL) {
							PlannerHelp* nextList = new PlannerHelp();
							nextList->vertex = next;
							nextList->vertex->setFill(4278255360);
							nextList->parent = curr;
							nextList->givenCost = tempGivenCost;
							x = nextList->vertex->getXCoordinate();
							y = nextList->vertex->getYCoordinate();
							nextList->heuristicCost = (sqrt(pow((y - endY), 2) + pow(x - endX, 2))) * 1.2;
							nextList->vertex->addLineTo(nextList->parent->vertex, 4278190335);
							nextList->finalCost = nextList->givenCost + ((nextList->heuristicCost));

							visited[next] = nextList;
							open.push(nextList);
						}
						else {
							if (tempGivenCost < visited[next]->givenCost) {
								PlannerHelp* nextNode = visited[next];
								open.remove(nextNode);
								nextNode->givenCost = tempGivenCost;
								nextNode->parent = curr;
								nextNode->finalCost = nextNode->givenCost + nextNode->heuristicCost;
								open.push(nextNode);
							}

						}
					}
				}
				/*
				for (int i = tile_col - 1; i <= tile_col + 1; i++) {
					for (int j = tile_row - 1; j <= tile_row + 1; j++) {
						if ((0 <= j) && (0 <= i) && (j < row) && (i < col) && !(i == tile_col && j == tile_row)) {
							if ((tile_row % 2 == 0 && (i == tile_col + 1 && (j == tile_row - 1 || j == tile_row + 1))) || (tile_row % 2 == 1 && (i == tile_col - 1 && (j == tile_row - 1 || j == tile_row + 1)))) {
								continue;
							}
							Tile* next = graph[i][j];
							double x = next->getXCoordinate();
							double y = next->getYCoordinate();
							double disStart = sqrt(pow((y - newY), 2) + pow(x - newX, 2));
							double tempGivenCost = curr->givenCost + next->getWeight() * disStart;
							
							count++;
							if (next->getWeight() != 0) {
								if (visited[next] == NULL) {
									PlannerHelp* nextList = new PlannerHelp();
									nextList->vertex = next;
									nextList->vertex->setFill(4278255360);
									nextList->parent = curr;
									nextList->givenCost = tempGivenCost;
									x = nextList->vertex->getXCoordinate();
									y = nextList->vertex->getYCoordinate();
									nextList->heuristicCost = (sqrt(pow((y - endY), 2) + pow(x-endX, 2)))*1.2;
									nextList->vertex->addLineTo(nextList->parent->vertex, 4278190335);
									nextList->finalCost = nextList->givenCost + ((nextList->heuristicCost));
									
									visited[next] = nextList;
									open.push(nextList);
								}
								else {
									if (tempGivenCost < visited[next]->givenCost) {
										PlannerHelp* nextNode = visited[next];
										open.remove(nextNode);
										nextNode->givenCost = tempGivenCost;
										nextNode->parent = curr;
										nextNode->finalCost = nextNode->givenCost + nextNode->heuristicCost;
										open.push(nextNode);
									}

								}
							}
						}
					}
				}
			*/
				if (timeslice == 0) {
					break;
				}
				
			}
		}
		DLLEXPORT void PathSearch::shutdown()
		{
			sol.clear();

			for (auto iter = visited.begin(); iter != visited.end(); iter++) {
				delete iter->second;
			}
			visited.clear();
		

			//visited.clear();
			while (!open.empty()) {
				PlannerHelp* curr = open.front();
				open.pop();
				
			}
			
		
		}
		DLLEXPORT void PathSearch::unload()
		{
			
			if (tile_map != NULL) {
				for (int i = 0; i < vertexGraph.size(); i++) {
					for (int j = 0; j < vertexGraph[0].size(); j++) {

						while (!(vertexGraph[i][j]->edges.empty())) {
							Edge* edge = vertexGraph[i][j]->edges.back();
							vertexGraph[i][j]->edges.pop_back();
							delete edge;
						}
						vertexGraph[i][j]->edges.clear();
						SearchSpace* node = vertexGraph[i][j];
						delete node;
					}
				}

			
				graph.clear();
				vertexGraph.clear();
			}
			
		}
		DLLEXPORT bool PathSearch::isDone() const
		{
			return done;
		}
		DLLEXPORT vector<Tile const*> const PathSearch::getSolution() const
		{
			
			return sol;
		}

		//bool (*)(T const&, T const&)
		bool isGreaterThan2(PlannerHelp* const& lhs, PlannerHelp* const& rhs)
		{
			return (lhs->finalCost > rhs->finalCost);
		}

		

		

	
		PlannerHelp::PlannerHelp()
		{
			
			vertex = nullptr;
			parent = nullptr;
		}
	
		
		SearchSpace::SearchSpace()
		{

		}

		Edge::Edge()
		{

		}

		// CLASS DEFINITION GOES HERE
	}
}  // close namespace ufl_cap4053::searches
