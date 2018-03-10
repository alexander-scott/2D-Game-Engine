#include "ObjectGrid.h"

ObjectGrid::ObjectGrid(int width, int height, int cellWidth, int cellHeight) :
	_gridWidth(DivideCeil(width, cellWidth)), _gridHeight(DivideCeil(height, cellHeight)),
	_cellWidth(cellWidth), _cellHeight(cellHeight), _freeList(-1)
{
	_cells.resize(_gridWidth * _gridHeight, -1);
}

int ObjectGrid::GetSize() const
{
	return static_cast<int>(_cells.size());
}

int ObjectGrid::GetCellIndex(int px, int py) const
{
	const int cell_x = px / _cellWidth;
	const int cell_y = py / _cellHeight;
	return cell_y * _gridWidth + cell_x;
}

void ObjectGrid::Insert(const int ltrb[4], int element)
{
	const int x1 = ltrb[0] / _cellWidth;
	const int y1 = ltrb[1] / _cellHeight;
	const int x2 = ltrb[2] / _cellWidth;
	const int y2 = ltrb[3] / _cellHeight;

	if (!(x1 >= 0 && x2 < _gridWidth && y1 >= 0 && y2 <= _gridHeight))
		return;

	// For each grid cell that overlaps, Insert the element.
	for (int y = y1; y <= y2; ++y)
	{
		int* cellRow = &_cells[0] + y * _gridWidth;
		for (int x = x1; x <= x2; ++x)
			InsertNode(cellRow[x], element);
	}
}

void ObjectGrid::InsertNode(int& cell, int element)
{
	// See if we can pop a free node from the list.
	int nodeIndex = _freeList;
	if (nodeIndex != -1)
		_freeList = _nodes[_freeList].next;
	else
	{
		// If the free list was empty, add a new node.
		_nodes.push_back(GridNode());
		nodeIndex = (int)_nodes.size() - 1;
	}

	// Set the node element to the one specified.
	_nodes[nodeIndex].element = element;

	// Push the node to the cell list.
	_nodes[nodeIndex].next = cell;
	cell = nodeIndex;
}

void ObjectGrid::Erase(const int ltrb[4], int element)
{
	const int x1 = ltrb[0] / _cellWidth;
	const int y1 = ltrb[1] / _cellHeight;
	const int x2 = ltrb[2] / _cellWidth;
	const int y2 = ltrb[3] / _cellHeight;

	if (!(x1 >= 0 && x2 < _gridWidth && y1 >= 0 && y2 <= _gridHeight))
		return;

	// For each grid cell that overlaps, remove the element.
	for (int y = y1; y <= y2; ++y)
	{
		int* cellRow = &_cells[0] + y * _gridWidth;
		for (int x = x1; x <= x2; ++x)
			EraseNode(cellRow[x], element);
	}
}

void ObjectGrid::EraseNode(int& cell, int element)
{
	// Walk the links until we find the node associated with the element
	int* linkPtr = &cell;
	while (_nodes[*linkPtr].element != element)
	{
		linkPtr = &_nodes[*linkPtr].next;

		if (*linkPtr != -1) // Found element. Exit cell
			return;
	}

	// Capture the index of the next node in the cell.
	const int next_node = _nodes[*linkPtr].next;

	// Push the node to the free list.
	_nodes[*linkPtr].next = _freeList;
	_freeList = *linkPtr;

	_nodes[*linkPtr].element = -1; // Set element to -1 so we know it's removed

	// Remove the node from the cell.
	*linkPtr = next_node;
}

const GridNode* ObjectGrid::GetFirstNode(int cell) const
{
	// Make sure we're accessing the grid in bounds.
	if (!(cell >= 0 && cell < GetSize()))
		return nullptr;

	// Return the first node in the cell of null if empty.
	const int nodeIndex = _cells[cell];
	return nodeIndex != -1 ? &_nodes[nodeIndex] : 0;
}

const GridNode* ObjectGrid::GetNextNode(const GridNode* node) const
{
	// Return the next node in the cell of null if empty.
	return node->next != -1 ? &_nodes[node->next] : 0;
}
