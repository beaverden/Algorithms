//INPUT - a vector containing pairs <weight, price> of every item
//		- the maximum allowed weight
//OUTPUT - a vector containing the indexes of the items included in the knapsack

const int maxN = 500;
const int maxW = 500;
int res[maxN][maxW], n, w, a, b;
vector <int> knapsack(vector <pair <int, int> > items, int w) {
    for (int i = 0; i < items.size(); i++) {
        if (i == 0) {
			//If it's the 0'th item (meaning first), we simply include it
			//where we can so we don't have any problems with i-1 being negative
            for (int j = items[i].first; j < items.size(); j++)
                res[i][j] = items[i].second;
            continue;
        }
        for (int j = 0; j<=w; j++) {
            int weight = items[i].first,
                price = items[i].second;
            res[i][j] = res[i-1][j]; //Starting position - not included
            if (j >= weight) {
                res[i][j] = max(res[i][j], res[i-1][j-weight] + price);
				//If the resulting profit is bigger - item is included
            }
        }
    }
    vector <int> result;
    int currentN = items.size() - 1,
        currentW = w;
    while (res[currentN][currentW] != 0) {
        if (res[currentN][currentW] == res[currentN - 1][currentW]) {
            currentN--; //Item with idnex currentN is not included in the solution
                        //lowering the index
        } else {
            currentW -= items[currentN].first;  //Item included, lowering the currentW
            result.push_back(currentN);     	//Adding the item to result vector
            currentN--;
        }
    }
    return result;
}