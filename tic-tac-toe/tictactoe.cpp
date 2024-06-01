#include <iostream>
using namespace std;

class TicTacToe
{
    private:
        char board[3][3];
        char current_player;

    public:
        TicTacToe();
        void displayBoard();
        bool makeMove(int row, int col);
        char checkWin(char win);
        char getCurrentPlayer();
};
// Default Constructor
TicTacToe::TicTacToe()
{
    current_player = 'X';
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            board[i][j] = ' ';
        }
    }
}
// Display board displays the board whenever called
void TicTacToe::displayBoard()
{
    cout << "Current Board:" << endl;
    cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---------" << endl;
    cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---------" << endl;
    cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << endl << endl;
}
// Make move takes the parameters of rows and columns from the user and carries out the appropriate move
bool TicTacToe::makeMove(int row, int col)
{
    if(board[row][col]!=' '||row>=3 || col >=3 || row < 0 || col < 0)
    {
        return false;
    }
    board[row][col] = current_player;
    return true;
}
// Checks for the winc conditions and returns the winner (or indicates whether it is a draw)
char TicTacToe::checkWin(char win)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return current_player;
        }
        else if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return current_player;
        }
    }
    if(board[0][0]==win&&board[1][1]==win&&board[2][2]==win||
       board[2][0]==win&&board[1][1]==win&&board[0][2]==win)
    {
            return current_player;
    }

    bool draw = true;
    for(int i=-0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j] == ' ')
            {
                draw = false;
                break;
            }
        }
    }
    if(draw == true)
    {
        displayBoard();
        return 'D';
    }  

    current_player = (current_player == 'X') ? 'O' : 'X';
    return ' ';
}
// Returns the player who currently has the turn
char TicTacToe::getCurrentPlayer()
{
    return current_player;
}
// main function
int main()
{
    TicTacToe game;
    bool active =true;
    cout << "Welcome to TicTacToe!" << endl;
    while(active == true)
    {
        int row, column;
        game.displayBoard();
        bool flag = true;

        cout << "Player " << game.getCurrentPlayer() << ", enter row (0-2) and column (0-2):" << endl;
        cin >> row >> column;

        if(game.makeMove(row,column)==false)
        {
            cout << "Invalid move!" << endl;
        }
        char wincheck = game.checkWin(game.getCurrentPlayer());
        if(wincheck==game.getCurrentPlayer())
        {
            game.displayBoard();
            cout << "Player "<< game.getCurrentPlayer() << " wins the game!" << endl;
            break;
        }
        if(wincheck=='D')
        {
            cout << "It is a draw" << endl;
            break;
        }
    }
}
