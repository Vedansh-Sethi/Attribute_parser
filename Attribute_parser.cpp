#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class attribute {
    private:
    string name;
    string value;
    public:
    //constructor
    attribute(string name_i, string value_i) {
        name = name_i;
        value = value_i;
    }
    string get_name() {
        return name;
    }
    string get_value() {
        return value;
    }
};

class tag {
    private:
    string path;
    vector<attribute> attributes;
    public:
    //constructor
    tag(string path_i, vector<attribute> attributes_i) {
        path = path_i;
        attributes = attributes_i;
    }
    string get_path() {
        return path;
    }
    vector<attribute> get_attributes() {
        return attributes;
    }
};
vector<string> parse(string HRML) {
    vector<string> output;
    string word = "";
    for (int i = 0; i < HRML.size(); i++) {
        if (HRML[i] == '<' or HRML[i] == '>' or HRML[i] == '=' or HRML[i] == '\"' or HRML[i] == ' ') {
            if(word != "") {
                output.push_back(word);
                word = "";
            }
        }
        else {
            word += HRML[i];
        }
}
        if (word != "") {
            output.push_back(word);
        }
        return output;
}
int main() {
     int n, q;
     cin >> n >> q;
     cin.ignore();
     vector<string> HRML_lines;
     vector<vector<string>> HRML_parsed;
     vector<tag> supertag;
     for (int i = 0; i < n; i++) {
        string current_line;
        getline(cin, current_line);
        HRML_lines.push_back(current_line);
     }
     
     for(int i = 0; i < HRML_lines.size(); i++) {
        vector<string> parsed_line = parse(HRML_lines[i]);
        HRML_parsed.push_back(parsed_line);
     }
     vector<string> path;
     for (const vector<string>& current_line: HRML_parsed) {
        vector<attribute> atts_i;
        if (current_line[0][0] == '/') {
        path.pop_back();
        }
        else {
            path.push_back(current_line[0]);
            for( int i = 1; i + 1 < current_line.size(); i += 2) {
                attribute att(current_line[i], current_line[i+1]);
                atts_i.push_back(att);
            }
        string current_path = "";
        for (int i = 0; i < path.size() - 1; i++) {
            current_path += path[i] + ".";
        }
        current_path += path[path.size() - 1];
        
        tag current_tag(current_path, atts_i);
        supertag.push_back(current_tag);
     }}
     vector<string> queries;
     for (int i = 0; i < q; i++) {
        string qin;
        getline(cin, qin);
        queries.push_back(qin);
     }
     
     for (const string& query: queries) {
        int tilde;
        string query_name = "";
        string query_path = "";
        string req_value = "";
        for (int i = 0; i < query.size(); i++) {
            if (query[i] == '~') {
                tilde = i;
            }
        }
        for (int i = 0; i < tilde; i++) {
            query_path += query[i];
        }
        for (int i = tilde + 1; i < query.size(); i++) {
            query_name += query[i];
        }
        for (int i = 0; i < supertag.size(); i++) {
            if (query_path == supertag[i].get_path()) {
                for (int j = 0; j < supertag[i].get_attributes().size(); j++) {
                    if(query_name == supertag[i].get_attributes()[j].get_name()) {
                        req_value = supertag[i].get_attributes()[j].get_value();
                        break;
                    }
                }
            }
        }
        if (req_value != "") {
            cout << req_value << "\n";
        }
        else {
            cout << "Not Found!\n";
        }
     }
    return 0;
}