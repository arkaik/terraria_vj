#include "Node.h"


Node::Node() 
{
}

Node::~Node()
{
}

void Node::init(ShaderProgram sp)
{
	shader = &sp;
}

void Node::update(int deltatime)
{
	updateCurrent();
	updateChildren(deltatime);
}

void Node::render()
{
}

void Node::addChild(Ptr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

Node::Ptr Node::removeChild(const Node & node)
{
	auto found = std::find_if(children.begin(), children.end(), [&](Ptr& p) -> bool { return p.get() == &node; });

	assert(found != children.end());

	Ptr result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}

void Node::updateCurrent()
{
}

void Node::updateChildren(int deltatime)
{
	for (int i = 0; i < int(children.size()); i++)
	{
		children[i]->update(deltatime);
	}
}
