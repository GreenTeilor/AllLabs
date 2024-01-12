#include "Field.h"

bool Field::outBounds(int x, int y)
{
	return (x < 0 || x > m_width - 1) || (y < 0 || y > m_height - 1);
}

Field::Field(int width, int height, int numMines)
{
	generate(width, height, numMines);
}

bool Field::isGameEnded() 
{
	return m_isGameOver;
}

bool Field::isDemined() 
{
	return m_width * m_height - m_numMines == m_cellsRevealed;
}

bool Field::isDeminingStarted()
{
	return m_isDeminingStarted;
}

int Field::generateInt(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(mersenne);
	//static const double fraction = 1.0 / (static_cast<double>(INT_MAX) + 1.0);
	//return static_cast<int>(mersenne() * fraction * (max - min + 1) + min);
}

int Field::calcBombsNear(int x, int y) 
{
	if (outBounds(x, y)) return 0;
	int i = 0;
	for (int offsetX = -1; offsetX <= 1; ++offsetX)
	{
		for (int offsetY = -1; offsetY <= 1; ++offsetY)
		{
			if (outBounds(offsetX + x, offsetY + y)) continue;
			if (m_field[offsetY + y][offsetX + x].getInner() == Type::Types::BOMB)
			{
				++i;
			}
		}
	}
	return i;
}

void Field::countBombsNearEachCell() 
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_field[i][j].getInner() != Type::Types::BOMB)
			{
				int bombsNear = calcBombsNear(j, i);
				if (bombsNear != 0)
				{
					m_field[i][j].setInner(static_cast<Type::Types>(calcBombsNear(j, i)));
				}
			}
		}
	}
}

void Field::moveAwayBomb(int x, int y) 
{
	if (m_field[y][x].getInner() != Type::Types::BOMB) return;

	std::vector<Coordinates> notBombs;
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_field[i][j].getInner() != Type::Types::BOMB)
			{
				notBombs.push_back({ j, i });
			}
		}
	}

	Coordinates randomPlace = { x, y };
	while (randomPlace.x == x && randomPlace.y == y) {
		randomPlace = notBombs.at(generateInt(0, notBombs.size() - 1));
	}

	m_field[randomPlace.y][randomPlace.x].setInner(Type::Types::BOMB);
	m_field[y][x].setInner(Type::Types::EMPTY);
	countBombsNearEachCell(); //SOOOO BAAAAD!!!, ONLY CELLS NEAR SOURCE AND DESTINATION and themselves may change value,
	// so it's a waste of resources to do traversal through all cells
}

void Field::reveal(int x, int y) 
{
	if (!m_isDeminingStarted && m_field[y][x].getInner() == Type::Types::BOMB) {
		//Here logic to move bomb away and preferably to reserve some space near click(currently only move away mine implemented)
		moveAwayBomb(x, y);
		m_isDeminingStarted = true;
		reveal(x, y);
	}
	else {
		m_isDeminingStarted = true;
		if (outBounds(x, y)) return;
		if (m_field[y][x].isOpened()) return;
		if (m_field[y][x].open() && m_field[y][x].getInner() != Type::Types::BOMB) {
			++m_cellsRevealed;
		}
		if (isDemined()) {
			m_isGameOver = true;
		}
		if (calcBombsNear(x, y) != 0) return;
		reveal(x - 1, y - 1);
		reveal(x - 1, y + 1);
		reveal(x + 1, y - 1);
		reveal(x + 1, y + 1);
		reveal(x - 1, y);
		reveal(x + 1, y);
		reveal(x, y - 1);
		reveal(x, y + 1);
	}
}

void Field::revealAll()
{
	m_isGameOver = true;
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			if (m_field[i][j].getType() == Type::Types::FLAG && m_field[i][j].getInner() != Type::Types::BOMB) {
				m_field[i][j].setCover(Type::Types::WRONG_FLAG);
			}
			else {
				m_field[i][j].open();
			}
		}
	}
}

void Field::generate(int width, int height, int numMines) 
{
	m_isDeminingStarted = false;
	m_isGameOver = false;
	this->m_numMines = numMines;
	this->m_cellsRevealed = 0;
	this->m_height = height;
	this->m_width = width;
	m_field.clear();
	m_field.resize(height);
	for (auto& row : m_field) {
		row.clear();
		row.resize(width);
	}
	int i = 0;
	while (i < numMines) {//We don't want mines to overlap, so while loop
		int x = generateInt(0, width - 1);
		int y = generateInt(0, height - 1);
		if (m_field[y][x].getInner() == Type::Types::BOMB) continue;
		m_field[y][x].setInner(Type::Types::BOMB);
		i++;
	}
	this->m_numMines = numMines;
	countBombsNearEachCell();
}

std::vector<Cell>& Field::operator[](const int index)
{
	return m_field[index];
}

int Field::getHeight() const 
{
	return m_height;
}

int Field::getWidth() const
{
	return m_width;
}

int Field::getNumMines() const
{
	return m_numMines;
}