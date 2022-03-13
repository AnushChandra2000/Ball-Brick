#include <iostream>
#include <vector>
using namespace std;
void print_matrix(vector<vector<int>>& matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (i == 0 or j == 0 or j == matrix[i].size() - 1) {
				cout << "W ";
			} else if (i == matrix.size() - 1) {
				if (j != matrix[i].size() / 2) {
					cout << "G ";
				} else {
					cout << "O ";
				}
			} else {
				if (matrix[i][j] == 0) {
					cout << " ";
				} else if (matrix[i][j] == -1) {
					cout << "DE";
				} else if (matrix[i][j] == -2) {
					cout << "DS";
				} else {
					cout << matrix[i][j]; 
				}
				cout << " ";
			}
		}
		cout << "\n";
	}
}
/*
move 
Left diagonal -2
right diagonal 2
top 1
bottom -1
*/
int dx[8] = {0, 0, -1, -1, -1, 1, 1, 1};
int dy[8] = {-1, 1, -1, 0, 1, -1, 0, 1};
void fun3(vector<vector<int>>& matrix, int row, int col) {
	if (matrix[row][col] == -1) {
		for (int c_ = 0; c_ < matrix[0].size(); c_++) {
			matrix[row][c_] = 0;
		}
	} else if (matrix[row][col] == -2) {
		matrix[row][col] = 0;
		for (int i = 0; i < 8; i++) {
			int x = row + dx[i];
			int y = col + dy[i];
			if (x > 0 && x < matrix.size() - 1 && y > 0 && y < matrix[0].size() - 1) {
				matrix[x][y] = 0;
			}
		}
	} else {
		matrix[row][col]--;
	}
}
bool fun2(vector<vector<int>>& matrix, int row, int col, int move) {
	if (row == matrix.size() - 1) {
		return col == matrix[0].size() / 2;	
	} else if (row == 0) {
		return fun2(matrix, row + 1, col, -1);
	} else if (col == 0) {
		for (int c = 0; c < matrix[0].size(); c++) {
			if (matrix[row][c]) {
				fun3(matrix, row, c);
				return fun2(matrix, row + 1, c, -1);
			}
		}
		return false;
	} else if (col == matrix[0].size() - 1) {
		for (int c = matrix[0].size() - 1; c >= 0; c--) {
			if (matrix[row][c]) {
				fun3(matrix, row, c);
				return fun2(matrix, row + 1, c, -1);
			}
		}
		return false;
	} else if (matrix[row][col]) {
		fun3(matrix, row, col);
		return fun2(matrix, row + 1, col, -1);
	} else {
		if (move == 1) {
			return fun2(matrix, row - 1, col, move);
		} else if (move == 2) {
			return fun2(matrix, row - 1, col + 1, move);
		} else if (move == -1) {
			return fun2(matrix, row + 1, col, move);
		} else if (move == -2) {
			return fun2(matrix, row - 1, col - 1, move);
		}
	}
	return false;
}
void fun(vector<vector<int>>& matrix, int& ball_count, bool& win, int direction) {
	int row = matrix.size() - 1, col = matrix[0].size() / 2;
	if (direction == 0) {
		ball_count -= !fun2(matrix, row - 1, col, 1);
	} else if (direction == -1) {
		ball_count -= !fun2(matrix, row - 1, col - 1, -2);
	} else if (direction == 1) {
		ball_count -= !fun2(matrix, row - 1, col + 1, 2);
	}
	win = true;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			if (matrix[i][j]) {
				win = false;
			}
		}
	}
}
int main() {
	int N;
	cout << "Enter size of the NxN matrix :";
	cin >> N;
	vector<vector<int>> matrix(N, vector<int>(N));
	char should_continue = 'Y';
	while (should_continue == 'Y') {
		cout << "Enter the brick's position and the brick type :";
		string a, b, c;
		cin >> a >> b >> c;
		int row = stoi(a), col = stoi(b);
		int val = c == "DE" ? -1 : c == "DS" ? -2 : stoi(c);
		matrix[row][col] = val;
		cout << "Do you want to continue(Y or N)?";
		cin >> should_continue;
	}
	cout << "Enter ball Count : ";
	int ball_count;
	cin >> ball_count;
	bool win = false;
	print_matrix(matrix);
	while (ball_count > 0 and !win) {
		//do something here
		string direction;
		cout << "Enter the direction in which the ball need to traverse";
		cin >> direction;
		int direction_value = 0;
		if (direction == "ST") {
			direction_value = 0;
		} else if (direction == "LD") {
			direction_value = -1;
		} else if (direction == "RD") {
			direction_value = 1;
		} else {
			break;
		}
		fun(matrix, ball_count, win, direction_value);
		print_matrix(matrix);
		cout << "Ball count is " << ball_count << "\n";
	}
	cout << (win ? "You win HURRAY..!!" : "You lose") << "\n";
	return 0;
}

