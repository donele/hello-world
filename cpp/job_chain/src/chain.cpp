#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <job_chain.h>
using namespace std;

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

Job parse_line(const string& s) {
    int n = s.size();
    int i = 0;
    int j = 0;
    int x = 0;
    while(j < n && isdigit(s[j])) {
        ++j;
    }
    if(j > i) {
        for(int k = i; k < j; ++k) {
            x *= 10;
            x += s[k] - '0';
        }
    } else {
        return Job(0, 0, 0, false);
    }
    if(s[j] == ',' && isdigit(s[j+1])) {
        i = j + 1;
        j = i;
    } else {
        return Job(0, 0, 0, false);
    }

    int y = 0;
    while(j < n && isdigit(s[j])) {
        ++j;
    }
    if(j > i) {
        for(int k = i; k < j; ++k) {
            y *= 10;
            y += s[k] - '0';
        }
    } else {
        return Job(0, 0, 0, false);
    }
    if(s[j] == ',' && isdigit(s[j+1])) {
        i = j + 1;
        j = i;
    } else {
        return Job(0, 0, 0, false);
    }

    int z = 0;
    while(j < n && isdigit(s[j])) {
        ++j;
    }
    if(j > i && j == n) {
        for(int k = i; k < j; ++k) {
            z *= 10;
            z += s[k] - '0';
        }
    } else {
        return Job(0, 0, 0, false);
    }

    return Job(x, y, z, true);
}

void throw_error() {
    cout << "Malformed";
}

bool process_jobs_unordered_map(const string& filename, bool verbose) {
    unordered_map<int, Chain> chains;
    ifstream ifs(filename);
    string line;
    getline(ifs, line);

    for(; getline(ifs, line);) {
        Job job = parse_line(line);
        if(job.valid) {
            auto it = chains.find(job.id);
            if(it != chains.end()) {
                it->second.add(job.id, job.runtime);
                if(job.next == 0) {
                    auto nh = chains.extract(it);
                    nh.key() = it->second.ids[0];
                    chains.insert(move(nh));
                } else {
                    auto nh = chains.extract(it);
                    nh.key() = job.next;
                    chains.insert(move(nh));
                }
            } else {
                auto ret = chains.insert(make_pair(job.next, Chain()));
                ret.first->second.add(job.id, job.runtime);
            }
        } else {
            throw_error();
            return false;
        }
    }
    if(verbose) {
        for(auto& ch : chains) {
            cout << "-" << endl;
            ch.second.report();
        }
        cout << "-" << endl;
    }
    return true;
}

bool process_jobs_map(const string& filename, bool verbose) {
    map<int, Chain> chains;
    ifstream ifs(filename);
    string line;
    getline(ifs, line);

    for(; getline(ifs, line);) {
        Job job = parse_line(line);
        if(job.valid) {
            auto it = chains.find(job.id);
            if(it != chains.end()) {
                it->second.add(job.id, job.runtime);
                if(job.next == 0) {
                    auto nh = chains.extract(it);
                    nh.key() = it->second.ids[0];
                    chains.insert(move(nh));
                } else {
                    auto nh = chains.extract(it);
                    nh.key() = job.next;
                    chains.insert(move(nh));
                }
            } else {
                auto ret = chains.insert(make_pair(job.next, Chain()));
                ret.first->second.add(job.id, job.runtime);
            }
        } else {
            throw_error();
            return false;
        }
    }
    if(verbose) {
        for(auto& ch : chains) {
            cout << "-" << endl;
            ch.second.report();
        }
        cout << "-" << endl;
    }
    return true;
}

bool process_jobs_vector(const string& filename, bool verbose) {
    vector<Chain> chains;
    vector<int> next_id;
    ifstream ifs(filename);
    string line;
    getline(ifs, line);

    for(; getline(ifs, line);) {
        Job job = parse_line(line);
        if(job.valid) {
            auto it = find(next_id.begin(), next_id.end(), job.id);
            if(it == next_id.end()) {
                Chain ch;
                ch.add(job.id, job.runtime);
                chains.push_back(ch);
                next_id.push_back(job.next);
            } else {
                int ichain = distance(next_id.begin(), it);
                chains[ichain].add(job.id, job.runtime);
                next_id[ichain] = job.next;
            }
        } else {
            throw_error();
            return false;
        }
    }
    if(verbose) {
        for(auto& ch : chains) {
            cout << "-" << endl;
            ch.report();
        }
        cout << "-" << endl;
    }
    return true;
}
