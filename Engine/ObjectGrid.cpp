#include "ObjectGrid.h"

ObjectGrid::ObjectGrid(int width, int height, int cellWidth, int cellHeight) :
	mGridWidth(DivideCeil(width, cellWidth)), mGridHeight(DivideCeil(height, cellHeight)),
	mCellWidth(cellWidth), mCellHeight(cellHeight), mFreeList(-1)
{
	mCells.resize(mGridWidth * mGridHeight, -1);
}

int ObjectGrid::GetSize() const
{
	return static_cast<int>(mCells.size());
}

int ObjectGrid::GetCellIndex(int px, int py) const
{
	const int cell_x = px / mCellWidth;
	const int cell_y = py / mCellHeight;
	return cell_y * mGridWidth + cell_x;
}

void ObjectGrid::Insert(const int ltrb[4], int element)
{
	const int x1 = ltrb[0] / mCellWidth;
	const int y1 = ltrb[1] / mCellHeight;
	const int x2 = ltrb[2] / mCellWidth;
	const int y2 = ltrb[3] / mCellHeight;

	if (!(x1 >= 0 && x2 < mGridWidth && y1 >= 0 && y2 <= mGridHeight))
		return;

	// For each grid cell that overlaps, Insert the element.
	for (int y = y1; y <= y2; ++y)
	{
		int* cellRow = &mCells[0] + y * mGridWidth;
		for (int x = x1; x <= x2; ++x)
			InsertNode(cellRow[x], element);
	}
}

void ObjectGrid::InsertNode(int& cell, int element)
{
	// See if we can pop a free node from the list.
	int nodeIndex = mFreeList;
	if (nodeIndex != -1)
		mFreeList = mNodes[mFreeList].next;
	else
	{
		// If the free list was empty, add a new node.
		mNodes.push_back(GridNode());
		nodeIndex = (int)mNodes.size() - 1;
	}

	// Set the node element to the one specified.
	mNodes[nodeIndex].element = element;

	// Push the node to the cell list.
	mNodes[nodeIndex].next = cell;
	cell = nodeIndex;
}

void ObjectGrid::Erase(const int ltrb[4], int element)
{
	const int x1 = ltrb[0] / mCellWidth;
	const int y1 = ltrb[1] / mCellHeight;
	const int x2 = ltrb[2] / mCellWidth;
	const int y2 = ltrb[3] / mCellHeight;

	if (!(x1 >= 0 && x2 < mGridWidth && y1 >= 0 && y2 <= mGridHeight))
		return;

	// For each grid cell that overlaps, remove the element.
	for (int y = y1; y <= y2; ++y)
	{
		int* cellRow = &mCells[0] + y * mGridWidth;
		for (int x = x1; x <= x2; ++x)
			EraseNode(cellRow[x], element);
	}
}

void ObjectGrid::EraseNode(int& cell, int element)
{
	// Walk the links until we find the node associated with the element
	int* linkPtr = &cell;
	while (mNodes[*linkPtr].element != element)
	{
		linkPtr = &mNodes[*linkPtr].next;

		if (*linkPtr != -1) // Found element. Exit cell
			return;
	}

	// Capture the index of the next node in the cell.
	const int next_node = mNodes[*linkPtr].next;

	// Push the node to the free list.
	mNodes[*linkPtr].next = mFreeList;
	mFreeList = *linkPtr;

	mNodes[*linkPtr].element = -1; // Set element to -1 so we know it's removed

	// Remove the node from the cell.
	*linkPtr = next_node;
}

const GridNode* ObjectGrid::GetFirstNode(int cell) const
{
	// Make sure we're accessing the grid in bounds.
	if (!(cell >= 0 && cell < GetSize()))
		return nullptr;

	// Return the first node in the cell of null if empty.
	const int nodeIndex = mCells[cell];
	return nodeIndex != -1 ? &mNodes[nodeIndex] : 0;
}

const GridNode* ObjectGrid::GetNextNode(const GridNode* node) const
{
	// Return the next node in the cell of null if empty.
	return node->next != -1 ? &mNodes[node->next] : 0;
}
