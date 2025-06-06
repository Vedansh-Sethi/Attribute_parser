#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// -----------------------------
// Attribute Class
// Represents a key-value pair in a tag like key="value"
// -----------------------------
class attribute {
private:
    string name;
    string value;

public:
    // Constructor
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

// -----------------------------
// Tag Class
// Represents a tag with a full path and its attributes
// -----------------------------
class tag {
private:
    string path;
    vector<attribute> attributes;

public:
    // Constructor
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

// -----------------------------
// Parse Function
// Tokenizes a line into meaningful words
// (Splits on <, >, =, ", and space)
// -----------------------------
vector<string> parse(string HRML) {
    vector<string> output;
    string word = "";

    for (int i = 0; i < HRML.size(); i++) {
        if (HRML[i] == '<' || HRML[i] == '>' || HRML[i] == '=' || HRML[i] == '\"' || HRML[i] == ' ') {
            if (word != "") {
                output.push_back(word);
                word = "";
            }
        } else {
            word += HRML[i];
        }
    }

    if (word != "") {
        output.push_back(word);
    }

    return output;
}

// -----------------------------
// Main Program
// Handles:
// - Input of HRML lines and queries
// - Manual XML parsing using class-based structure
// - Query resolution
// -----------------------------
int main() {
    int n, q;
    cin >> n >> q;
    cin.ignore();  // Consume the newline character

    vector<string> HRML_lines;
    vector<vector<string>> HRML_parsed;
    vector<tag> supertag;  // Stores all tags with full paths

    // -----------------------------
    // Step 1: Read HRML lines
    // -----------------------------
    for (int i = 0; i < n; i++) {
        string current_line;
        getline(cin, current_line);
        HRML_lines.push_back(current_line);
    }

    // -----------------------------
    // Step 2: Parse all HRML lines
    // -----------------------------
    for (int i = 0; i < HRML_lines.size(); i++) {
        vector<string> parsed_line = parse(HRML_lines[i]);
        HRML_parsed.push_back(parsed_line);
    }

    // -----------------------------
    // Step 3: Build tag hierarchy
    // -----------------------------
    vector<string> path;
    for (const vector<string>& current_line : HRML_parsed) {
        vector<attribute> atts_i;

        if (current_line[0][0] == '/') {
            // Closing tag — move up one level in hierarchy
            path.pop_back();
        } else {
            // Opening tag — move deeper
            path.push_back(current_line[0]);

            // Collect attributes from the line
            for (int i = 1; i + 1 < current_line.size(); i += 2) {
                attribute att(current_line[i], current_line[i + 1]);
                atts_i.push_back(att);
            }

            // Build full path for the current tag
            string current_path = "";
            for (int i = 0; i < path.size() - 1; i++) {
                current_path += path[i] + ".";
            }
            current_path += path[path.size() - 1];

            // Create tag object and store
            tag current_tag(current_path, atts_i);
            supertag.push_back(current_tag);
        }
    }

    // -----------------------------
    // Step 4: Read queries
    // -----------------------------
    vector<string> queries;
    for (int i = 0; i < q; i++) {
        string qin;
        getline(cin, qin);
        queries.push_back(qin);
    }

    // -----------------------------
    // Step 5: Process queries
    // -----------------------------
    for (const string& query : queries) {
        int tilde = query.find('~');
        string query_path = query.substr(0, tilde);
        string query_name = query.substr(tilde + 1);

        string req_value = "";

        // Look for the tag with matching path
        for (int i = 0; i < supertag.size(); i++) {
            if (query_path == supertag[i].get_path()) {
                // Look for the attribute inside the tag
                for (int j = 0; j < supertag[i].get_attributes().size(); j++) {
                    if (query_name == supertag[i].get_attributes()[j].get_name()) {
                        req_value = supertag[i].get_attributes()[j].get_value();
                        break;
                    }
                }
            }
        }

        // Output result
        if (req_value != "") {
            cout << req_value << "\n";
        } else {
            cout << "Not Found!\n";
        }
    }

    return 0;
}
