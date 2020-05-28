#include <iostream>
#include <string>

using namespace std;

int main()
{
	char GameBoard[3][3] = { {'-','-','-'},{ '-','-','-' },{ '-','-','-' } };
	char Stamp, playerPlacement;
	int Player = 1;
	int currentPlayer;
	int rowCounter = 0; 
	int columnCounter = 0;
	bool playerWin = false;
	 
	cout << "The map is as follows:\n" << "1 2 3\n4 5 6\n7 8 9\n\n";

TurnPrep:

	//Prepares Game for repective player's turn
	Player = Player + 1;
	currentPlayer = Player % 2;

	if (currentPlayer == 1)
	{
		Stamp = 'O';
	}
	else
	{
		Stamp = 'X';
	}
	goto PrintGameBoard;

PrintGameBoard:
	cout << "Player " << currentPlayer + 1 << "'s turn: \n";
	cout << GameBoard[0][0] << " " << GameBoard[0][1] << " " << GameBoard[0][2] << " \n" << GameBoard[1][0] << " " << GameBoard[1][1] << " " << GameBoard[1][2] << " \n" << GameBoard[2][0] << " " << GameBoard[2][1] << " " << GameBoard[2][2] << " \n";
	if (playerWin)
	{
		goto EndGame;
	}
	cout << "Player " << currentPlayer + 1 << " (" << Stamp << ")" << " choose desired location 1 - 9 to take your turn: \n";
	goto PlayerTurn;

PlayerTurn:

	cin >> playerPlacement;
	
	switch (playerPlacement)
	{
		case '1':
			if (GameBoard[0][0] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[0][0] = Stamp;
			break;
		case '2':
			if (GameBoard[0][1] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[0][1] = Stamp;
			break;
		case '3':
			if (GameBoard[0][2] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[0][2] = Stamp;
			break;
		case '4':
			if (GameBoard[1][0] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[1][0] = Stamp;
			break;
		case '5':
			if (GameBoard[1][1] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[1][1] = Stamp;
			break;
		case '6':
			if (GameBoard[1][2] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[1][2] = Stamp;
			break;
		case '7':
			if (GameBoard[2][0] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[2][0] = Stamp;
			break;
		case '8':
			if (GameBoard[2][1] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[2][1] = Stamp;
			break;
		case '9':
			if (GameBoard[2][2] != '-')
			{
				cout << " The other player has already played a move there, please enter another location:\n";
				goto PlayerTurn;
			}
			GameBoard[2][2] = Stamp;
			break;
		default:
			cout << "Invalid input please enter a numeric value 1-9\n";
			cin.clear();
			cin.ignore(100, '\n'); //ensures you do not smash your face on the keyboard and press enter
			playerPlacement = (char) 0;
			goto PrintGameBoard;
	}
	goto CheckGameBoard;


CheckGameBoard:
	
    //Horizontal checks
	if (GameBoard[columnCounter][rowCounter] == Stamp && rowCounter < 3)
	{

		if (rowCounter == 2)
		{
			cout << "Player " << currentPlayer + 1 << " wins!\n";
			playerWin = true;
			goto PrintGameBoard;
		}
		rowCounter++;
		goto CheckGameBoard;
	}
	else if(GameBoard[columnCounter][rowCounter] != Stamp && columnCounter < 3)
	{
		columnCounter++;
		rowCounter = 0;
		goto CheckGameBoard;
	}

		columnCounter = 0;
		rowCounter = 0;

ColumnCheck:

		if (GameBoard[columnCounter][rowCounter] == Stamp && columnCounter < 3)
		{

			if (columnCounter == 2)
			{
				cout << "Player " << currentPlayer + 1 << " wins!\n";
				playerWin = true;
				goto PrintGameBoard;
			}

			columnCounter++;
			goto ColumnCheck;
		}
		else if (GameBoard[columnCounter][rowCounter] != Stamp && rowCounter < 3)
		{
			rowCounter++;
			columnCounter = 0;
			goto ColumnCheck;
		}

		columnCounter = 0;
		rowCounter = 0;

DiagonalCheck:

		if (GameBoard[columnCounter][rowCounter] == Stamp && columnCounter < 3)
		{

			if (columnCounter == 2 && rowCounter == 2)
			{
				cout << "Player " << currentPlayer + 1 << " wins!\n";
				playerWin = true;
				goto PrintGameBoard;
			}

			rowCounter++;
			columnCounter++;

			goto DiagonalCheck;
		}

		columnCounter = 0;
		rowCounter = 2;

ReverseDiagonalCheck:

		if (GameBoard[columnCounter][rowCounter] == Stamp && rowCounter >= 0)
		{

			if (columnCounter == 2 && rowCounter == 0)
			{
				cout << "Player " << currentPlayer + 1 << " wins!\n";
				playerWin = true;
				goto PrintGameBoard;
			}

			rowCounter--;
			columnCounter++;

			goto ReverseDiagonalCheck;
		}

		columnCounter = 0;
		rowCounter = 0;

		if (GameBoard[0][0] != '-' && GameBoard[0][1] != '-' && GameBoard[0][2] != '-' && GameBoard[1][0] != '-' && GameBoard[1][1] != '-' && GameBoard[1][2] != '-' && GameBoard[2][0] != '-' && GameBoard[2][1] != '-' && GameBoard[2][2] != '-')
		{
			cout << "\nRound ended in a tie!\n";
			goto EndGame;
		}

	goto TurnPrep;

EndGame:
	cout << "Press any key to exit";
	int holdOpen;
	cin >> holdOpen;
}