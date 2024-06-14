#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

vector<string> split_comma(const string& s) {
	vector<string> ret;
	int last = -1;
	string::size_type pos = s.find(',');
	while(pos < s.size()) {
		string sub = s.substr(last + 1, pos - last - 1);
		ret.push_back(sub);
		last = pos;
		pos = s.find(',', last + 1);
	}
	string sub = s.substr(last + 1, s.size() - last - 1);
	ret.push_back(sub);
	return ret;
}

bool valid(const vector<string>& v) {
	bool valid_size = v.size() == 3;
	bool non_empty = true;
	for(const string& s : v) {
		if(v.empty()) {
			non_empty = false;
			break;
		}
	}
	bool all_digits = true;
	for(const string& s : v) {
		for(char c : s) {
			if(!isdigit(c)) {
				all_digits = false;
				break;
			}
		}
	}
	return valid_size && non_empty && all_digits;
}

struct Chain {
	int cnt;
	int sum;
	vector<int> ids;
	Chain():cnt(0), sum(0){}
	void add(int id, int runtime) {
		++cnt;
		ids.push_back(id);
		sum += runtime;
	}
	void report() {
		cout << "First id: " << ids[0] << endl;
		cout << "Last id: " << ids[cnt - 1] << endl;
	}
};

void throw_error() {
	cout << "Malformed";
}

bool process_jobs() {
	unordered_map<int, Chain> chains;
	vector<Chain> done;

	ifstream ifs("input.txt");
	string line;
	getline(ifs, line);

	for(; getline(ifs, line);) {
		vector<string> split = split_comma(line);
		if(valid(split)) {
			int id = stoi(split[0]);
			int runtime = stoi(split[1]);
			int next = stoi(split[2]);
			if(chains.count(id)) {
				chains[id].add(id, runtime);
				if(next == 0)
					done.push_back(chains[id]);
				else
					chains[next] = move(chains[id]);
				chains.erase(id);
			} else {
				chains[next].add(id, runtime);
			}
		} else {
			throw_error();
			return false;
		}
	}
	for(auto& ch : done) {
		cout << "-" << endl;
		ch.report();
	}
	cout << "-" << endl;
	return true;
}

int main() {
	process_jobs();
	return 0;
}