#include "Connection.hpp"

Connection::Connection() {
	nodeA = nullptr;
	nodeB = nullptr;

	name = ""; 
}

Connection::Connection(Node &nodeA, Node &nodeB) : nodeA(nodeA), nodeB(nodeB) {}


