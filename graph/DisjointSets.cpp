// Disjoint Set Data Structure
// Author: Emil Stefanov
// Date: 03/28/06
// Implementaton is as described in http://en.wikipedia.org/wiki/Disjoint-set_data_structure

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <cassert>
#include <cstddef>

#include "DisjointSets.h"
//Modified for minisat by Sam Bayless

DisjointSets::DisjointSets()
{
	m_numElements = 0;
	m_numSets = 0;
}

DisjointSets::DisjointSets(int count)
{
	m_numElements = 0;
	m_numSets = 0;
	AddElements(count);
}

DisjointSets::DisjointSets(const DisjointSets & s)
{
	this->m_numElements = s.m_numElements;
	this->m_numSets = s.m_numSets;

	s.m_nodes.copyTo(m_nodes);
}

DisjointSets::~DisjointSets()
{

}

// Note: some internal data is modified for optimization even though this method is consant.
int DisjointSets::FindSet(int elementId)
{
	assert(elementId < m_numElements);
	// Find the root element that represents the set which `elementId` belongs to
	int curnodeID= elementId;

	//Node * curNode  = &m_nodes[elementId];
	while(m_nodes[curnodeID].parent != -1)
		curnodeID =m_nodes[curnodeID].parent;
	int rootID = curnodeID;

	// Walk to the root, updating the parents of `elementId`. Make those elements the direct
	// children of `root`. This optimizes the tree for future FindSet invokations.
	curnodeID =elementId;
	while(curnodeID != rootID)
	{
		int nextID = m_nodes[curnodeID].parent;
		m_nodes[curnodeID].parent = rootID;
		curnodeID = nextID;
	}

	return m_nodes[rootID].index;
}

void DisjointSets::Union(int setId1, int setId2)
{
	assert(setId1 < m_numElements);
	assert(setId2 < m_numElements);

	if(setId1 == setId2)
		return; // already unioned

	Node& set1 = m_nodes[setId1];
	Node& set2 = m_nodes[setId2];

	// Determine which node representing a set has a higher rank. The node with the higher rank is
	// likely to have a bigger subtree so in order to better balance the tree representing the
	// union, the node with the higher rank is made the parent of the one with the lower rank and
	// not the other way around.
	if(set1.rank > set2.rank)
		set2.parent = setId1;
	else if(set1.rank < set2.rank)
		set1.parent = setId2;
	else // set1->rank == set2->rank
	{
		set2.parent = setId1;
		++set1.rank; // update rank
	}

	// Since two sets have fused into one, there is now one less set so update the set count.
	--m_numSets;
}

void DisjointSets::AddElements(int numToAdd)
{
	assert(numToAdd >= 0);

	// insert and initialize the specified number of element nodes to the end of the `m_nodes` array
	//m_nodes.insert(m_nodes.end(), numToAdd, (Node*)NULL);

	for(int i = m_numElements; i < m_numElements + numToAdd; ++i)
	{
		m_nodes.push();
		assert(i==m_nodes.size()-1);
		//m_nodes[i] = new Node();
		m_nodes[i].parent = -1;
		m_nodes[i].index = i;
		m_nodes[i].rank = 0;
	}

	// update element and set counts
	m_numElements += numToAdd;
	m_numSets += numToAdd;
}

int DisjointSets::NumElements() const
{
	return m_numElements;
}

int DisjointSets::NumSets() const
{
	return m_numSets;
}