#pragma once

#include <vector>

#include "Consts.h"

struct GridNode
{
	int next; // Stores either the next node in the grid cell or the next free node if this node has been removed.
	int element; // Stores the index to the element.
};

class ObjectGrid
{
public:
	ObjectGrid(int width, int height, int cellWidth, int cellHeight); // Creates an object grid with width and height and individual cell width and height

	void Insert(const int ltrb[4], int element); // Inserts an element to the grid. 'ltrb' is left, top, right, bottom in pixel coordinates
	void Erase(const int ltrb[4], int element); // Removes an element from the grid. 'ltrb' is left, top, right, bottom in pixel coordinates

	int GetSize() const; // Gets grid size
	int GetCellIndex(int px, int py) const; // Gets the cell index for the specified point in pixel coordinates.
	const GridNode* GetFirstNode(int cell) const; // Returns the first node at the specified cell index.
	const GridNode* GetNextNode(const GridNode* node) const; // Returns the next node in the same cell to the one specified.

private:
	void InsertNode(int& cell, int element); // Inserts a node with the specified element to the specified cell.
	void EraseNode(int& cell, int element); // Removes the node with the specified element from the specified cell.

	std::vector<int>				mCells;
	std::vector<GridNode>			mNodes;

	int								mGridWidth;
	int								mGridHeight;
	int								mCellWidth;
	int								mCellHeight;

	int								mFreeList; // Stores an index to the first free (unused) node.
};
