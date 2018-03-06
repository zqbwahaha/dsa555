#include "maze.h"
int findPath (Maze& theMaze, const Coord& start, const Coord& end, Coord path[]){
	int found = 0;
	if (theMaze.isWall(start))
		return 0;
	if (start == end)
	{
		theMaze.mark(start);
		*path = start;
		return 1;
	}
	else if (theMaze.isEmpty(start)&&start.x<=99&&start.y<=99)//make sure the range is not out side
	{
		theMaze.mark(start);
		path++;
		found = findPath(theMaze, Coord(start.x - 1, start.y), end, path);
		if (!found)
		{
			found = findPath(theMaze, Coord(start.x + 1, start.y), end, path);
		}
		if (!found)
		{
			found = findPath(theMaze, Coord(start.x, start.y - 1), end, path);
		}
		if (!found)
		{
			found = findPath(theMaze, Coord(start.x, start.y + 1), end, path);
		}
		if (!found)
			theMaze.unMark(start);
		path--;
	}
	if (found)
	{
		found++;
		*path = start;
	}
		return found;
}
/*found = findPath(theMaze, Coord(start.x - 1, start.y), end, path);
if (!found)
found = findPath(theMaze, Coord(start.x + 1, start.y), end, path);
if (!found)
found = findPath(theMaze, Coord(start.x, start.y - 1), end, path);
if (!found)
found = findPath(theMaze, Coord(start.x, start.y + 1), end, path);
return found; */
