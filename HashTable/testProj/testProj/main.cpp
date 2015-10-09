#include <iostream>
#include <cmath>
#include <algorithm>
#define part partitionByMiddle(arr, startOfPartition, endOfPartition - 1, compInt)

using namespace std;

struct cords {
    int X;
    int Y;
};

float angle(cords a, cords b);
bool compCords (int &x0, int &y0, cords &firstCords, cords &secondCords);
bool compInt (int &x0, int &y0, int &a, int &b) {
    return a < b;
}

template <typename T>
void quickSort(T *arr, int l, int r, int x0, int y0, bool comp(int &x0, int &y0, T &a, T &b));

const char *inputFilePath = "/Users/Security/Coding/MIPT C++/MIPT C++/inputSem4.txt";
const char *outputFilePath = "/Users/Security/Coding/MIPT C++/MIPT C++/outputSem4.txt";

int main() {
    cout << "Test project started working \n";
    //! ========Files=======
    //    FILE *input, *output;
    //    input = fopen(inputFilePath, "r");
    //    output = fopen(outputFilePath, "w");
    //! =========EOF========
    int n, fooX, fooY;
    //fscanf(input, "%d", &n);
    scanf("%d", &n);
    cords minCords;
    cords * allCords = (cords *) malloc (sizeof(cords) * n);
    scanf("%d%d", &fooX, &fooY);
    //fscanf(input, "%d%d", &fooX, &fooY);
    allCords[0].X = fooX;
    allCords[0].Y = fooY;
    minCords.X = fooX;
    minCords.Y = fooY;
    
    for (int i = 1 ; i <  n ; ++ i ) {
        //fscanf(input, "%d%d", &fooX, &fooY);
        scanf("%d%d", &fooX, &fooY);
        allCords[i].X = fooX;
        allCords[i].Y = fooY;
        if ((fooX < minCords.X) || ((fooX == minCords.X) && (fooY < minCords.Y)))
        {
            minCords = {fooX, fooY};
        }
    }
    quickSort(allCords, 0, n - 1, minCords.X, minCords.Y, compCords);
    printf ("%d %d\n", minCords.X, minCords.Y);
    for (int i = 0 ; i < n - 1 ; ++ i ) {
        printf ("%d %d\n", allCords[i].X, allCords[i].Y);
    }
    return 0;
}

template <typename T>
void quickSort(T *arr, int l, int r, int x0, int y0, bool comp(int &x0, int &y0, T &a, T &b)) {
    int i = l, j = r;
    T pivot = arr[(l >>1) + (r >>1)];
    while (i <= j) {
        while (comp(x0, y0, arr[i], pivot))
            i++;
        while (comp(x0, y0, pivot, arr[j]))
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    };
    
    if (l < j)
        quickSort(arr, l, j, x0, y0, comp);
    if (i < r)
        quickSort(arr, i, r, x0, y0, comp);
    
}

bool compCords (int &x0, int &y0, cords &firstCords, cords &secondCords) {
    //TODO: avoid dividing by zero
    cords min = {x0, y0};
    float angle1 = angle(min, firstCords);
    float angle2 = angle(min, secondCords);
    if (angle1 == angle2) return (firstCords.X -x0) * (firstCords.X - x0) + (firstCords.Y - y0) * (firstCords.Y - y0) > (secondCords.X - x0) * (secondCords.X - x0) + (secondCords.Y - y0) * (secondCords.Y - y0);
    return angle1 < angle2;
    //    if ((firstCords.Y == y0) && (secondCords.Y == y0)) return firstCords.X < secondCords.X;
    //    if ((firstCords.Y == y0) || (secondCords.Y == y0)) return firstCords.Y > secondCords.Y;
    //    if (((firstCords.X - x0) / (firstCords.Y - y0)) != ((secondCords.X - x0) / (secondCords.Y - y0)))
    //    return (firstCords.X - x0) / (firstCords.Y - y0) < (secondCords.X - x0) / (secondCords.Y - y0);
    //    else return firstCords.X < secondCords.X;
}

float angle(cords a, cords b) {
    
    float angle;
    if (a.X == b.X) {
        if (a.Y < b.Y) angle = 0;
        else angle = M_PI;
    }
    else
        if (a.Y == b.Y) {
            if (a.X < b.X) angle = M_PI_2;
            else angle = - M_PI_2;
        }
    
        else angle = atan ((b.X - a.X) / (b.Y - a.Y) );
    return angle;
}
