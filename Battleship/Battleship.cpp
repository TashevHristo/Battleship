#include <iostream>
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


void FillShips(int id, ShipCoordinates* ships, char** bord) {
	int startX = ships[id].start[0];
	int startY = ships[id].start[1];
	int endX = ships[id].end[0];
	int endY = ships[id].end[1];
	if (ships[id].isHorizontal == 1) {
		for (size_t i = startY; i < endY + 1; i++)
		{
			bord[startX][i] = '#';
		}
	}
	else {
		for (size_t i = startX; i < endX + 1; i++)
		{
			bord[i][startY] = '#';
		}
	}
}
void PrintBord(char** bord) {
	for (size_t i = 0; i < 10; i++)
	{
		/*if (i == 0) {
			for (size_t j = 0; j < 11; j++)
			{
				std::cout << "  " << j;
			}
			std::cout << std::endl;
			continue;
		}*/
		for (size_t j = 0; j < 10; j++)
		{
			/*if (j == 0) {
				std::cout << i - 1;
			}*/
			std::cout << "  " << bord[i][j];
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
bool isValidShip(int first[COORDINATES_SIZE], int second[COORDINATES_SIZE], int length) {
	for (size_t i = 0; i < 2; i++)
	{
		if (first[i] < 0 || first[i] > 10 || second[i] < 0 || second[i] > 10)  return false;
	}
	if((isHorizontal(first, second) || isVertical(first, second)) && 0 >= length && length > 4) return true;
	return false;
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
void EnterPlayerShips(ShipCoordinates* ships, char** bord) {
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
		if (!isValidShip(firstCoordinates, secondCoordinates, shipLenght)) {
			system("cls");
			PrintBord(bord);
			std::cout << "Please Enter Valid Coordinates!" << std::endl;
			continue;
		}
		ships[i].id = i + 1;
		ReadCoordinates(firstCoordinates, secondCoordinates, ships[i].start, ships[i].end);
		ships[i].length = shipLenght;
		ships[i].isHorizontal = isHorizontal(firstCoordinates, secondCoordinates);
		switch (shipLenght) {
			case 0:
				oneSquare--;
				break;
			case 1:
				twoSquare--;
				break;
			case 2:
				threeSquare--;
				break;
			case 3:
				fourSquare--;
				break;
			default:
				break;
		}
		system("cls");
		FillShips(i, ships, bord);
		PrintBord(bord);
	}
}
void FillBord(char** bord) {
	for (size_t i = 0; i < 10; i++)
	{
		bord[i] = new char[9];
		for (size_t j = 0; j < 10; j++)
		{
			bord[i][j] = '~';
		}
	}
}

int main()
{
	//int* playerShips = new int[SHIP_COUNT] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int* computerShips = new int[SHIP_COUNT] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	ShipCoordinates* playerShips = new ShipCoordinates[SHIP_COUNT];
	ShipCoordinates PlayerShips;
	char** bord = new char*[9];
	FillBord(bord);
	PrintBord(bord);
	EnterPlayerShips(playerShips, bord);
}
