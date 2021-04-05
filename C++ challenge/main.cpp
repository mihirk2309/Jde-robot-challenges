#include <bits/stdc++.h>
#include <fstream>
#include<string>

#define M 5
#define N 7 

//#define MAX 5
using namespace std;
 
int coordinate;
vector<int> final_x, final_y;

// Function returns true if the
// move taken is valid else
// it will return false.
int isSafe(int x, int y, char arr[M][N], bool visited[M][N]){
    return (x >= 0 && x < M && y >= 0 && y < N
            && visited[x][y] == false && arr[x][y] == '.');
}

int isAvailable(int x, int y, char arr[M][N], bool visited[M][N]){
    return (isSafe(x+1, y, arr, visited) || isSafe(x-1, y, arr, visited)
        || isSafe(x, y+1, arr, visited) 
        || isSafe(x, y-1, arr, visited));
}

// Function to print all the possible
// paths from (0, 0) to (n-1, n-1).
void printPathUtil(int row, int col, char arr[M][N],
              int n, string& path, vector<string>&
               possiblePaths, bool visited[M][N]){

    if(isSafe(row , col, arr, visited)){

        if(!isAvailable(row, col, arr, visited)){
            possiblePaths.push_back(path);
            final_x.push_back(row);
            final_y.push_back(col); 
            return;
        }

     
        // Mark the cell as visited
        visited[row][col] = true;
     
        // Try for all the 4 directions (down, left,
        // right, up) in the given order to get the
        // paths in lexicographical order
     
        // Check if downward move is valid
        if (isSafe(row + 1, col, arr, visited))
        {
            path.push_back('D');
            printPathUtil(row + 1, col, arr, n,
                     path, possiblePaths, visited);
            path.pop_back();
        }
     
        // Check if the left move is valid
        if (isSafe(row, col - 1, arr, visited))
        {
            path.push_back('L');
            printPathUtil(row, col - 1, arr, n,
                       path, possiblePaths, visited);
            path.pop_back();
        }
     
        // Check if the right move is valid
        if (isSafe(row, col + 1, arr, visited))
        {
            path.push_back('R');
            printPathUtil(row, col + 1, arr, n,
                       path, possiblePaths, visited);
            path.pop_back();
        }
     
         // Check if the upper move is valid
        if (isSafe(row - 1, col, arr, visited))
        {
            path.push_back('U');
            printPathUtil(row - 1, col, arr, n,
                   path, possiblePaths, visited);
            path.pop_back();
        }
     
        // Mark the cell as unvisited for
        // other possible paths
        visited[row][col] = false;

    }
    
}

void replace(int pos, int size, char arr[M][N],
              int n, vector<int> final_x,vector<int> final_y, vector<string>&
               possiblePaths, string new_arr[M][N]){

    int x = final_x[pos];
    int y = final_y[pos];
    string c;

    for(int i = size;i>=0;i--){
        c = to_string(i);
        new_arr[x][y] = c;

        if(possiblePaths[pos][i-1] == 'D'){
            x--;

        }
        else if(possiblePaths[pos][i-1] == 'L'){
            y++;

        }
        else if(possiblePaths[pos][i-1] == 'R'){
            y--;

        }
        else if(possiblePaths[pos][i-1] == 'U'){
            x++;
        }


    }

}


 
// Function to store and print
// all the valid paths
void printPath(char arr[M][N], int n)
{
    // vector to store all the possible paths
    int max_len = 0, pos = 0;
    int size = 0;
    int i = 0,j = 0;


    vector<string> possiblePaths;
    string path;

    string new_arr[M][N];
    for(i = 0;i<M;i++){
        for(j = 0;j<N;j++){
            new_arr[i][j] = arr[i][j];
        }
    }


    //string line;

    bool visited[M][N];
    memset(visited, false, sizeof(visited));
      
    // Call the utility function to
    // find the valid paths
    for(i = 0;i<M;i++){
        for(j = 0;j<N;j++){
            printPathUtil(i, j, arr, n, path,
                possiblePaths, visited);
        }
    }
 
    // Print all possible paths
    for (int i = 0; i < possiblePaths.size(); i++){
        //cout << possiblePaths[i] << "   " << possiblePaths[i].size() << "  ";
        //cout << final_x[i] << final_y[i] << endl;
        if(possiblePaths[i].size() > max_len){
            max_len = possiblePaths[i].size();
            pos = i;
        }

    }

    size = possiblePaths[pos].size();

    replace(pos,size, arr, n, final_x, final_y, possiblePaths, new_arr);

    cout << "Input" << endl ;

    for(i = 0;i<M;i++){
        for(j = 0;j<N;j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "Output" << endl;

    for(i = 0;i<M;i++){
        for(j = 0;j<N;j++){
            cout << new_arr[i][j] << " ";
        }
        cout << endl;
    }

}
 
// Driver code
int main()
{
    
    int i=0,j = 0;
    char arr[M][N];
    
    char ch;
    fstream fin("ip1.txt", fstream::in);
    while (fin >> noskipws >> ch) {
        if(ch != '\n'){
            arr[i][j] = ch;
            j++;
        }
        else if(ch == '\n'){
            //N = j;
            i++;
            j = 0;
        }
    }

    int n = sizeof(arr) / sizeof(arr[0]);
    printPath(arr, n);

    return 0;
}
