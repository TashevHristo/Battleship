#include <iostream>
#include <cstdlib>
#include <Windows.h>

const int SHIP_COUNT = 10;
const int COORDINATES_SIZE = 2;

struct ShipCoordinates {
	int id;
	int start[COORDINATES_SIZE];
	int end[COORDINATES_SIZE];
	int length;
	bool isHorizontal;
};


void FillShips(int id, ShipCoordinates* ships, char** board) {
	int startX = ships[id].start[0];
	int startY = ships[id].start[1];
	int endX = ships[id].end[0];
	int endY = ships[id].end[1];
	if (ships[id].isHorizontal == 1) {
		for (size_t i = startY; i < endY + 1; i++)
		{
			board[startX][i] = '#';
		}
	}
	else {
		for (size_t i = startX; i < endX + 1; i++)
		{
			board[i][startY] = '#';
		}
	}
}
void PrintBoard(char** player, char** computer) {
	for (size_t i = 0; i < 11; i++)
	{
		if (i == 0) {
			std::cout << "   ";
			for (size_t j = 0; j < 10; j++)
			{
				std::cout << j << "  ";
			}
			std::cout << '|';
			for (size_t j = 0; j < 10; j++)
			{
				std::cout << "  " << j;
			}
			std::cout << std::endl;
			continue;
		}
		for (size_t j = 0; j < 22; j++)
		{
			if (j == 0) {
				std::cout << i - 1;
				continue;
			}
			else if (1 <= j && j < 11) {
				std::cout << "  " << player[i - 1][j - 1];
			}
			else if (j == 11) {
				std::cout << "  " << '|';
			}
			else {
				std::cout << "  " << computer[i - 1][j - 12];
			}
			
		}
		std::cout << std::endl;
	}
}
bool isHorizontal(int first[COORDINATES_SIZE], int second[COORDINATES_SIZE]) {
	if (first[0] == second[0]) return true;
	return false;
}
bool isVertical(int first[COORDINATES_SIZE], int second[COORDINATES_SIZE]) {
	if (first[1] == second[1]) return true;
	return false;
}
bool isValidShip(int first[COORDINATES_SIZE], int second[COORDINATES_SIZE], int length, char** board) {
	for (size_t i = 0; i < 2; i++)
	{
		if (first[i] < 0 || first[i] > 10 || second[i] < 0 || second[i] > 10)  return false;
	}
	if((!isHorizontal(first, second) && !isVertical(first, second)) || 0 > length || length > 4) return false;
	if (isHorizontal(first, second)) {
		for (int i = first[1] - 1; i < second[1] + 2; i++)
		{
			for (int j = first[0] - 1; j < second[0] + 2; j++) {
				if (j < 0 || j > 9) {
					continue;
				}
				if (board[j][i] == '#') return false;
			}
		}
	}
	else {
		for (int i = first[0] - 1; i < second[0] + 2; i++)
		{
			if (board[i][first[1]] == '#') return false;
		}
	}
	return true;
}
void ReadCoordinatesFromConsole(int first[COORDINATES_SIZE], int second[COORDINATES_SIZE]) {
	for (size_t i = 0; i < COORDINATES_SIZE; i++)
	{
		std::cin >> first[i];
	}

	for (size_t i = 0; i < COORDINATES_SIZE; i++)
	{
		std::cin >> second[i];
	}
}
void ReadCoordinates(int first[COORDINATES_SIZE], int second[COORDINATES_SIZE], int* start, int* end) {
	for (size_t i = 0; i < COORDINATES_SIZE; i++)
	{
		start[i] = first[i];
		end[i] = second[i];
	}
}
void UpdateShipCount(int length, int &one, int &two, int &three, int&four) {
	switch (length) {
	case 0:
		one--;
		break;
	case 1:
		two--;
		break;
	case 2:
		three--;
		break;
	case 3:
		four--;
		break;
	default:
		break;
	}
}
void ClearAndPrint(char** player, char** computer) {
	system("cls");
	PrintBoard(player, computer);
}
void EnterPlayerShips(ShipCoordinates* ships, char** player, char** computer) {
	int oneSquare = 4;
	int twoSquare = 3;
	int threeSquare = 2;
	int fourSquare = 1;
	int shipLenght = 0;
	int firstCoordinates[COORDINATES_SIZE];
	int secondCoordinates[COORDINATES_SIZE];

	for (int i = 0; i < sizeof(ships); i++) {
		std::cout << "One square count: " << oneSquare << " Two square count: " << twoSquare <<
			" Three square count: " << threeSquare << " Four square count: " << fourSquare << std::endl;

		ReadCoordinatesFromConsole(firstCoordinates, secondCoordinates);
		shipLenght = (secondCoordinates[0] - firstCoordinates[0]) + (secondCoordinates[1] - firstCoordinates[1]);
		if (!isValidShip(firstCoordinates, secondCoordinates, shipLenght, player)) {
			system("cls");
			PrintBoard(player, computer);
			std::cout << "Please Enter Valid Coordinates!" << std::endl;
			continue;
		}
		ships[i].id = i + 1;
		ReadCoordinates(firstCoordinates, secondCoordinates, ships[i].start, ships[i].end);
		ships[i].length = shipLenght;
		ships[i].isHorizontal = isHorizontal(firstCoordinates, secondCoordinates);
		UpdateShipCount(shipLenght, oneSquare, twoSquare, threeSquare, fourSquare);
		FillShips(i, ships, player);
		ClearAndPrint(player, computer);
	}
}
void EnterComputerShips(ShipCoordinates* ships, char** palyer, char** computer) {
	
}
void FillBoard(char** board) {
	for (size_t i = 0; i < 10; i++)
	{
		board[i] = new char[9];
		for (size_t j = 0; j < 10; j++)
		{
			board[i][j] = '~';
		}
	}
}

int main()
{
	//int** playerShips = new int*[SHIP_COUNT];
	//int* computerShips = new int[SHIP_COUNT] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	ShipCoordinates* playerShips = new ShipCoordinates[SHIP_COUNT];
	ShipCoordinates PlayerShips;
	ShipCoordinates ComputerShips;
	char** PlayerBoard = new char*[9];
	char** ComputerBoard = new char*[9];
	FillBoard(PlayerBoard);
	FillBoard(ComputerBoard);
	PrintBoard(PlayerBoard, ComputerBoard);
	EnterPlayerShips(playerShips, PlayerBoard, ComputerBoard);
}
