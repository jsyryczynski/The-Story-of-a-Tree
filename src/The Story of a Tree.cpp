#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'storyOfATree' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER k
 *  4. 2D_INTEGER_ARRAY guesses
 */

int gcd(int a, int b){
	if (b > a) return gcd(b,a);
	if(b==0) return a;
	return gcd(b, a%b);
}

pair<int, int> reduceFraction(int x, int y){
	int d = gcd(x, y);

	x = x / d;
	y = y / d;

	return pair<int, int>(x, y);
}

string storyOfATree(int n, vector<vector<int>> edges, int k, vector<vector<int>> guesses) {
	cout << "start" << endl;
    vector<vector<int>> adjacencyList(n, vector<int>());
    for (int idx = 0; idx < n - 1; ++idx) {
    	adjacencyList[idx].reserve(n);
    }

    for (int idx = 0; idx < n - 1; ++idx) {
        int fromIdx = edges[idx][0] - 1;
        int toIdx = edges[idx][1] - 1;
        adjacencyList[fromIdx].push_back(toIdx);
        adjacencyList[toIdx].push_back(fromIdx);
    }

    vector<int> parents(n, -1);
    list<int> dfsStack;
    parents[0] = 0;
    dfsStack.push_back(0);

    while(!dfsStack.empty()) {
        int currentIdx = dfsStack.back();
        dfsStack.pop_back();

        for(int idx = 0; idx < adjacencyList[currentIdx].size(); ++idx) {
        	int nIdx = adjacencyList[currentIdx][idx];
            if (parents[nIdx] < 0) {
                parents[nIdx] = currentIdx;
                dfsStack.push_back(nIdx);
            }
        }
    }
    parents[0] = -1;

    int wins = 0;
    for (int rootIdx = 0; rootIdx < n; ++rootIdx) {
        int correctGuesses = 0;
        for (int guessIdx = 0; guessIdx < guesses.size(); ++guessIdx) {
            if (parents[guesses[guessIdx][1] - 1] == guesses[guessIdx][0] - 1)
                correctGuesses++;
        };
        if (correctGuesses >= k) ++wins;

        if (rootIdx == n - 1) break;

        int currentIdx = rootIdx + 1;
        int nextIdx = parents[currentIdx];
        int nextParent = parents[nextIdx];

        parents[currentIdx] = -1;

        while (nextIdx != rootIdx) {
            parents[nextIdx] = currentIdx;
            currentIdx = nextIdx;
            nextIdx = nextParent;
            nextParent = parents[nextIdx];
        }
        parents[rootIdx] = currentIdx;
    }


    if (wins == 0){
        return "0/1";
    }
    else{
    	pair<int, int> res = reduceFraction(wins, n);
        ostringstream os;
        os << res.first << "/" << res.second;
        return os.str();
    }
}

int main()
{
    ofstream fout("output.txt");

    string q_temp;
    ifstream ifs("input.txt");
    getline(ifs, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string n_temp;
        getline(ifs, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        vector<vector<int>> edges(n - 1);

        for (int i = 0; i < n - 1; i++) {
            edges[i].resize(2);

            string edges_row_temp_temp;
            getline(ifs, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string first_multiple_input_temp;
        getline(ifs, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int g = stoi(first_multiple_input[0]);

        int k = stoi(first_multiple_input[1]);

        vector<vector<int>> guesses(g);

        for (int i = 0; i < g; i++) {
            guesses[i].resize(2);

            string guesses_row_temp_temp;
            getline(ifs, guesses_row_temp_temp);

            vector<string> guesses_row_temp = split(rtrim(guesses_row_temp_temp));
            for (int j = 0; j < 2; j++) {
                int guesses_row_item = stoi(guesses_row_temp[j]);

                guesses[i][j] = guesses_row_item;
            }
        }

        string result = storyOfATree(n, edges, k, guesses);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
