#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <assert.h>

#include "ShaderProgram.h"

class Node
{
public:
	typedef std::unique_ptr< Node > Ptr;

	Node();
	~Node();
	virtual void init(ShaderProgram sp);
	void update(int deltatime);
	virtual void render() = 0;

	void addChild(Ptr child);
	Ptr removeChild(const Node& node);

private:
	std::vector< Ptr > children;
	Node* parent;
	
	
	void initShaders();

	void updateCurrent();
	void updateChildren(int deltatime);

protected:
	ShaderProgram* shader;
};

