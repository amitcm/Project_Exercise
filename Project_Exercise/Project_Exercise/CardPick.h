#include <vector>
using namespace std;

vector<int> create(int n);
// Returns sum of elements with indexes a..b, inclusive
int query(const vector<int> &tree, int a, int b);
// Increases value of k-th element by inc.
void increase(vector<int> &tree, int k, int inc);