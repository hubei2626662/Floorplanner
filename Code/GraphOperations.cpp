#include "GraphOperations.hpp"

void GraphOperations::performDFS()
{
	int time = 0;
	topologicalSort.clear();
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		//std::cout << "Empty Graph Found";
		return;
	}
	else {
		//INIT Vertices
		for (auto it : data) {
			it.second->init();
		}
		//Start DFS
		for (auto it : data) {
			if (!it.second->getIsVisited()) {
				time = DFSVisit(*it.second, time);
			}
		}
	}
}

int GraphOperations::DFSVisit(Vertex &u, int time)
{
	time = time + 1;
	u.setVisitTime(time);
	u.setIsVisited(true);
	unordered_map<std::string, Edge*> edgeList = u.getEdgeList();
	if (!edgeList.empty()) {
		for (auto e : edgeList) {
			if (e.second->getDestination()->getIsVisited() == false) {
				e.second->getDestination()->setPrevious(&u);
				DFSVisit(*e.second->getDestination(), time);
			}
		}
	}
	time = time + 1;
	u.setFinishTime(time);
	topologicalSort.push_back(&u);
	return time;
}

double GraphOperations::getLongestPath()
{
	addSource();
	addSink();
	double distance = 0;
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		//std::cout << "Empty Graph Found";
		return 0.0;
	}
	else {
		performDFS();
		for (auto it : data) {
			it.second->init();
		}
		for (int i = topologicalSort.size()-1; i >= 0;i--) {
			std::unordered_map<std::string, Edge*> edgeList = topologicalSort.at(i)->getEdgeList();
			for (auto e : edgeList) {
				if (e.second->getDestination()->getDistance() < topologicalSort.at(i)->getDistance() + e.second->getWeight()) {
					distance = topologicalSort.at(i)->getDistance() + e.second->getWeight();
					e.second->getDestination()->setDistance(distance);
				}
			}
		}
	}
	distance = data.find("super_sink")->second->getDistance();
	return distance;
}
GraphOperations::GraphOperations()
{
	cout << "Constructed";
	this->g = new Graph();
}
GraphOperations::GraphOperations(Graph* g)
{
	this->g = g;
}

Vertex& GraphOperations::addSource()
{
	Vertex *source = new Vertex(*new Node("super_source"));
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		//std::cout << "Empty Graph Found";
	}
	else {
		g->addVertex(*source);
		for (auto it : data) {
			g->addEdge(*source, *it.second,0);
		}
	}
	return *source;
}
Vertex& GraphOperations::addSink()
{
	Vertex *sink = new Vertex(*new Node("super_sink"));
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		//std::cout << "Empty Graph Found";
	}
	else {
		g->addVertex(*sink);
		for (auto it : data) {
			g->addEdge(*it.second,*sink);
		}
	}
	return *sink;
}

void GraphOperations::printGraph() {
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		//std::cout << "Empty Graph Found";
	}
	else {
		for (auto v : data) {
			std::cout << v.second->getData().getId()  << "\t\t" << v.second->getDistance() << endl;
		}
	}
}

Graph* GraphOperations::getGraph() {
	return this->g;
}

void GraphOperations::setGraph(Graph * g)
{
	this->g = g;
}
void GraphOperations::removeSource() {
	for (auto d : g->getVertices())
		g->removeEdge(*g->findVertex("super_source"), *d.second);
	g->getVertices().erase(g->getVertices().find("super_source"));
}
void GraphOperations::removeSink() {
	for (auto d : g->getVertices())
		g->removeEdge(*g->findVertex("super_sink"), *d.second);
	g->getVertices().erase(g->getVertices().find("super_sink"));
}

vector<Vertex*> GraphOperations::getTopologicalSort()
{
	return this->topologicalSort;
}
void GraphOperations::processCordsH() {
	double distance = 0;
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		//std::cout << "Empty Graph Found";
		return;
	}
	else {
		performDFS();
		for (auto it : data) {
			it.second->init();
		}
		for (int i = topologicalSort.size() - 1; i >= 0; i--) {
			std::unordered_map<std::string, Edge*> edgeList = topologicalSort.at(i)->getEdgeList();
			for (auto e : edgeList) {
				if (e.second->getDestination()->getDistance() < topologicalSort.at(i)->getDistance() + e.second->getWeight()) {
					distance = topologicalSort.at(i)->getDistance() + e.second->getWeight();
					e.second->getDestination()->setDistance(distance);
					e.second->getDestination()->getData().setLLCord(std::pair<double,double>(distance,e.second->getDestination()->getData().getLLCord().second));
					e.second->getDestination()->getData().setURCord(std::pair<double, double>(distance+ e.second->getDestination()->getData().getOptimumSize().getWidth(), e.second->getDestination()->getData().getURCord().second));
					//e.second->getDestination()->
				}
			}
		}
	}
}
void GraphOperations::processCordsV() {
	double distance = 0;
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		//std::cout << "Empty Graph Found";
		return;
	}
	else {
		performDFS();
		for (auto it : data) {
			it.second->init();
		}
		for (int i = topologicalSort.size() - 1; i >= 0; i--) {
			std::unordered_map<std::string, Edge*> edgeList = topologicalSort.at(i)->getEdgeList();
			for (auto e : edgeList) {
				if (e.second->getDestination()->getDistance() < topologicalSort.at(i)->getDistance() + e.second->getWeight()) {
					distance = topologicalSort.at(i)->getDistance() + e.second->getWeight();
					e.second->getDestination()->setDistance(distance);
					e.second->getDestination()->getData().setLLCord(std::pair<double, double>(e.second->getDestination()->getData().getLLCord().first,distance));
					e.second->getDestination()->getData().setURCord(std::pair<double, double>(e.second->getDestination()->getData().getURCord().first, distance+ e.second->getDestination()->getData().getOptimumSize().getLength()));
				}
			}
		}
	}
}