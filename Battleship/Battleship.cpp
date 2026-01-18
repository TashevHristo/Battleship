#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>

const int SHIP_COUNT = 10;
const int COORDINATES_SIZE = 2;
const int CALM_WATERS = 10;
const int ROUGH_SEAS = 12;
const int STORM_OF_STEEL = 15;
int sizeOfBoard = 0;

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
	for (size_t i = 0; i < sizeOfBoard + 1; i++)
	{
		if (i == 0) {
			std::cout << "   ";
			for (size_t j = 0; j < sizeOfBoard; j++)
			{
				if (j >= 9) {
					std::cout << j << " ";
				}
				else {
					std::cout << j << "  ";
				}
			}
			std::cout << " " << '|' << "  ";
			for (size_t j = 0; j < sizeOfBoard; j++)
			{
				if (j >= 9) {
					std::cout << j << " ";
				}
				else {
					std::cout << j << "  ";
				}
			}
			std::cout << std::endl;
			continue;
		}
		for (size_t j = 0; j < sizeOfBoard * 2 + 2; j++)
		{
			if (j == 0) {
				std::cout << i - 1;
				continue;
			}
			else if (1 <= j && j < sizeOfBoard + 1) {
				if (j == 1 && i - 1 > 9) {
					std::cout << " " << player[i - 1][j - 1];
				}
				else {
					std::cout << "  " << player[i - 1][j - 1];
				}
			}
			else if (j == sizeOfBoard + 1) {
				std::cout << "  " << '|';
			}
			else {
				if (j - (sizeOfBoard + 2) < 10) {
					std::cout << "  " << computer[i - 1][j - (sizeOfBoard + 2)];
				}
				else {
					std::cout << "  " << computer[i - 1][j - (sizeOfBoard + 2)];
				}
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
bool CheckShipCount(int length, int one, int two, int three, int four) {
	int currentCount = 0;
	switch (length) {
	case 0:
		currentCount = one;
		break;
	case 1:
		currentCount = two;
		break;
	case 2:
		currentCount = three;
		break;
	case 3:
		currentCount = four;
		break;
	default:
		break;
	}
	if (currentCount - 1 < 0) {
		return false;
	}
	return true;
}
bool isValidShip(int first[COORDINATES_SIZE], int second[COORDINATES_SIZE], int length, char** board) {
	for (size_t i = 0; i < 2; i++)
	{
		if (first[i] < 0 || first[i] > sizeOfBoard || second[i] < 0 || second[i] > sizeOfBoard || first[i] > second[i])
			return false;
	}
	if ((!isHorizontal(first, second) && !isVertical(first, second)) || 0 > length || length > 3) return false;
	for (int i = first[1] - 1; i < second[1] + 2; i++)
	{
		for (int j = first[0] - 1; j < second[0] + 2; j++) {
			if (j < 0 || j > sizeOfBoard - 1) {
				continue;
			}
			if (board[j][i] == '#') return false;
		}
	}
	return true;
}
void ReadCoordinatesFromConsole(int first[COORDINATES_SIZE], int second[COORDINATES_SIZE]) {
	std::cout << "Enter start coordinates: ";
	for (size_t i = 0; i < COORDINATES_SIZE; i++)
	{
		std::cin >> first[i];
	}

	std::cout << "Enter end coordinates: ";
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
void UpdateShipCount(int length, int& one, int& two, int& three, int& four) {
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

	for (int i = 0; i <= sizeOfBoard - 1; i++) {
		std::cout << "One square count: " << oneSquare << " Two square count: " << twoSquare <<
			" Three square count: " << threeSquare << " Four square count: " << fourSquare << std::endl;		
		ReadCoordinatesFromConsole(firstCoordinates, secondCoordinates);
		shipLenght = (secondCoordinates[0] - firstCoordinates[0]) + (secondCoordinates[1] - firstCoordinates[1]);
		if (!isValidShip(firstCoordinates, secondCoordinates, shipLenght, player) || !CheckShipCount(
			shipLenght, oneSquare, twoSquare, threeSquare, fourSquare)) {
			system("cls");
			PrintBoard(player, computer);
			std::cout << "Please Enter Valid Coordinates!" << std::endl;
			i--;
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
void AutoEnterShips(ShipCoordinates* ships, char** board, char** player) {
	int firstCoordinates[COORDINATES_SIZE];
	int secondCoordinates[COORDINATES_SIZE];
	int oneSquare = 4;
	int twoSquare = 3;
	int threeSquare = 2;
	int fourSquare = 1;
	int shipLenght = 0;
	int direction = 0;
	for (int i = 0; i < SHIP_COUNT; i++) {
		direction = rand() % 2;
		firstCoordinates[0] = rand() % sizeOfBoard;
		if (direction == 0) {
			firstCoordinates[1] = rand() % sizeOfBoard;
			secondCoordinates[0] = firstCoordinates[0];
			secondCoordinates[1] = rand() % sizeOfBoard;
		}
		else {
			firstCoordinates[1] = rand() % sizeOfBoard;
			secondCoordinates[0] = rand() % sizeOfBoard;
			secondCoordinates[1] = firstCoordinates[1];
		}
		shipLenght = (secondCoordinates[0] - firstCoordinates[0]) + (secondCoordinates[1] - firstCoordinates[1]);
		if (!isValidShip(firstCoordinates, secondCoordinates, shipLenght, board) || !CheckShipCount(
			shipLenght, oneSquare, twoSquare, threeSquare, fourSquare)) {
			i--;
			continue;
		}
		ships[i].id = i + 1;
		ReadCoordinates(firstCoordinates, secondCoordinates, ships[i].start, ships[i].end);
		ships[i].length = shipLenght;
		ships[i].isHorizontal = isHorizontal(firstCoordinates, secondCoordinates);
		UpdateShipCount(shipLenght, oneSquare, twoSquare, threeSquare, fourSquare);
		FillShips(i, ships, board);
	}
}
void FillBoard(char** board) {
	for (size_t i = 0; i < sizeOfBoard; i++)
	{
		board[i] = new char[sizeOfBoard - 1];
		for (size_t j = 0; j < sizeOfBoard; j++)
		{
			board[i][j] = '~';
		}
	}
}
bool isValidHit(int x, int y, char** board) {
	if (x < 0 || x > sizeOfBoard - 1 || y < 0 || y > sizeOfBoard - 1) return false;
	if (board[x][y] == 'o' || board[x][y] == 'x') return false;
	return true;
}
bool isShipAlive(ShipCoordinates* ships, int x, int y) {
	for (size_t i = 0; i < SHIP_COUNT; i++)
	{
		if (ships[i].start[0] == x && ships[i].start[1] <= y && y <= ships[i].end[1] && ships[i].length >= 0) {
			ships[i].length--;
			if (ships[i].length == -1) {
				return false;
			}
			break;
		}
		else if (ships[i].start[1] == y && ships[i].start[0] <= x && x <= ships[i].end[0] && ships[i].length >= 0) {
			ships[i].length--;
			if (ships[i].length == -1) {
				return false;
			}
			break;
		}
	}
	return true;
}
void WriteBoard(std::ostream& file, char** board) {

	for (size_t i = 0; i < sizeOfBoard; i++)
	{
		for (size_t j = 0; j < sizeOfBoard; j++)
		{
			file << board[i][j];
		}
		file << std::endl;
	}
}
void SaveToFile(ShipCoordinates* player, ShipCoordinates* computer, int alivePlayerShips, int aliveComputerShips,
	char** PlayerBoard, char** ComputerBoard, char** ComputerShowBoard) {
	std::ofstream file("SavedGame.txt");
	if (!file.is_open()) return;
	file << sizeOfBoard << std::endl;
	file << alivePlayerShips << std::endl;
	for (size_t i = 0; i < SHIP_COUNT; i++)
	{
		file << player[i].id << std::endl << player[i].start[0] << std::endl << player[i].start[1] << std::endl << player[i].end[0] <<
			std::endl << player[i].end[1] << std::endl << player[i].length << std::endl << player[i].isHorizontal << std::endl;
	}
	file << aliveComputerShips << std::endl;
	for (size_t i = 0; i < SHIP_COUNT; i++)
	{
		file << computer[i].id << std::endl << computer[i].start[0] << std::endl << computer[i].start[1] << std::endl << computer[i].end[0] <<
			std::endl << computer[i].end[1] << std::endl << computer[i].length << std::endl << computer[i].isHorizontal << std::endl;
	}
	WriteBoard(file, PlayerBoard);
	WriteBoard(file, ComputerBoard);
	WriteBoard(file, ComputerShowBoard);
	file.close();
}
void PlayerToShoot(ShipCoordinates* ships, char** board, int& aliveShips, char** player, char** computer, int alivePlayerShips,
	ShipCoordinates* playerShips, bool& saved) {
	int x;
	int y;
	std::cout << "Your turn! Please enter coordinates to hit: ";
	std::cin >> x >> y;
	if (x == -1 && y == -1) {
		SaveToFile(playerShips, ships, alivePlayerShips, aliveShips, player, computer, board);
		saved = true;
		return;
	}
	if (!isValidHit(x, y, board)) {
		std::cout << "Please enter valid coordinates!";
		PlayerToShoot(ships, board, aliveShips, player, computer, alivePlayerShips, playerShips, saved);
	}
	if (computer[x][y] == '#') {
		board[x][y] = 'x';
		computer[x][y] = 'x';
		ClearAndPrint(player, board);
		std::cout << "Hit!" << std::endl;
		if (!isShipAlive(ships, x, y)) {
			ClearAndPrint(player, board);
			std::cout << "Sunk!" << std::endl;
			aliveShips--;
			if (aliveShips <= 0) {
				return;
			}
		}
		PlayerToShoot(ships, board, aliveShips, player, computer, alivePlayerShips, playerShips, saved);
	}
	else if (computer[x][y] == '~') {
		board[x][y] = 'o';
		computer[x][y] = 'o';
		ClearAndPrint(player, board);
		std::cout << "Missed!" << std::endl;
	}

}
void ComputerToShoot(ShipCoordinates* ships, char** board, int& aliveShips, char** computer) {
	int x = rand() % 10;
	int y = rand() % 10;
	/*if (!isValidHit(x, y, board)) {
		std::cout << "Please enter valid coordinates!";
		ComputerToShoot(ships, board, aliveShips, computer);
	}*/
	if (board[x][y] == '#') {
		board[x][y] = 'x';
		ClearAndPrint(board, computer);
		if (!isShipAlive(ships, x, y)) {
			aliveShips--;
			if (aliveShips <= 0) {
				return;
			}
		}
		ComputerToShoot(ships, board, aliveShips, computer);
	}
	else if (board[x][y] == '~') {
		board[x][y] = 'o';
		//ClearAndPrint(board, computer);
	}
}

int main()
{
	srand(time(0));
	ShipCoordinates* playerShips = new ShipCoordinates[SHIP_COUNT];
	ShipCoordinates* computerShips = new ShipCoordinates[SHIP_COUNT];
	int alivePlayerShips = SHIP_COUNT;
	int aliveComputerShips = SHIP_COUNT;
	int isAuto = 0;
	bool isSaved = 0;
	int chooseSize = 0;
	int isNewGame = 0;
	std::cout << "Enter 1 to start a new game" << std::endl;
	std::cout << "Enter 2 to continue the previous one" << std::endl;
	std::cin >> isNewGame;
	char** PlayerBoard = {0};
	char** ComputerBoard = {0};
	char** ComputerShowBoard = {0};


	if (isNewGame == 2) {
		if (!"SavedGame.txt") {
			std::cout << "There is no such file!";
			return 0;
		}
		std::ifstream file("SavedGame.txt");
		if (!file.is_open()) {
			std::cout << "There is problem reading the file!";
			return 0;
		}
		file >> sizeOfBoard;
		PlayerBoard = new char* [sizeOfBoard - 1];
		ComputerBoard = new char* [sizeOfBoard - 1];
		ComputerShowBoard = new char* [sizeOfBoard - 1];
		file >> alivePlayerShips;
		for (size_t i = 0; i < SHIP_COUNT; i++)
		{
			file >> playerShips[i].id;
			file >> playerShips[i].start[0];
			file >> playerShips[i].start[1];
			file >> playerShips[i].end[0];
			file >> playerShips[i].end[1];
			file >> playerShips[i].length;
			file >> playerShips[i].isHorizontal;
		}

		file >> aliveComputerShips;
		for (size_t i = 0; i < SHIP_COUNT; i++)
		{
			file >> computerShips[i].id;
			file >> computerShips[i].start[0];
			file >> computerShips[i].start[1];
			file >> computerShips[i].end[0];
			file >> computerShips[i].end[1];
			file >> computerShips[i].length;
			file >> computerShips[i].isHorizontal;
		}
		for (size_t i = 0; i < sizeOfBoard; i++)
		{
			PlayerBoard[i] = new char[sizeOfBoard - 1];
			for (size_t j = 0; j < sizeOfBoard; j++)
			{
				file >> PlayerBoard[i][j];
			}
		}
		for (size_t i = 0; i < sizeOfBoard; i++)
		{
			ComputerBoard[i] = new char[sizeOfBoard - 1];
			for (size_t j = 0; j < sizeOfBoard; j++)
			{
				file >> ComputerBoard[i][j];
			}
		}
		for (size_t i = 0; i < sizeOfBoard; i++)
		{
			ComputerShowBoard[i] = new char[sizeOfBoard - 1];
			for (size_t j = 0; j < sizeOfBoard; j++)
			{
				file >> ComputerShowBoard[i][j];
			}
		}
		file.close();
		ClearAndPrint(PlayerBoard, ComputerShowBoard);
	}
	else {
		std::cout << "For the desired size, enter the corresponding number:" << std::endl;
		std::cout << "1 - Calm Waters(10X10)" << std::endl;
		std::cout << "2 - Rough Seas(12X12)" << std::endl;
		std::cout << "3 - Storm of Steel(15X15)" << std::endl;
		std::cin >> chooseSize;
		switch (chooseSize) {
		case 1:
			sizeOfBoard = CALM_WATERS;
			break;
		case 2:
			sizeOfBoard = ROUGH_SEAS;
			break;
		case 3:
			sizeOfBoard = STORM_OF_STEEL;
			break;
		default:
			break;
		}
		PlayerBoard = new char* [sizeOfBoard - 1];
		ComputerBoard = new char* [sizeOfBoard - 1];
		ComputerShowBoard = new char* [sizeOfBoard - 1];
		FillBoard(PlayerBoard);
		FillBoard(ComputerBoard);
		FillBoard(ComputerShowBoard);
		std::cout << "Enter 1 if you want to enter ships automatically" << std::endl;
		std::cout << "Enter 2 if you want to enter ships manually" << std::endl;
		std::cin >> isAuto;
		AutoEnterShips(computerShips, ComputerBoard, PlayerBoard);
		switch (isAuto) {
		case 1:
			AutoEnterShips(playerShips, PlayerBoard, ComputerBoard);
			ClearAndPrint(PlayerBoard, ComputerShowBoard);
			break;
		case 2:
			ClearAndPrint(PlayerBoard, ComputerShowBoard);
			EnterPlayerShips(playerShips, PlayerBoard, ComputerShowBoard);
			break;
		default:
			break;
		}
	}
	while (aliveComputerShips > 0 && alivePlayerShips > 0) {
		PlayerToShoot(computerShips, ComputerShowBoard, aliveComputerShips, PlayerBoard, ComputerBoard, alivePlayerShips,
			playerShips, isSaved);
		if (isSaved) break;
		ComputerToShoot(playerShips, PlayerBoard, alivePlayerShips, ComputerBoard);
		ClearAndPrint(PlayerBoard, ComputerShowBoard);
		std::cout << "Missed!" << std::endl;
	}
	if (isSaved) {
		system("cls");
		std::cout << "The Game was saved succesfully. See you next time!";
	}
	else if (aliveComputerShips == 0) {
		system("cls");
		std::cout << "You won!";
	}
	else if (alivePlayerShips == 0) {
		system("cls");
		std::cout << "You lost!";
	}
	
}