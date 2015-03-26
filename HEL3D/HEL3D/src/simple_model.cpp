#include "render_object.h"

#include <fstream>
#include <vector>
#include <string>
using namespace std;

inline bool _is_comment_line(const string &line) {
	for (int i = 0; i < line.size(); i++) {
		char c = line[i];
		if (c == ' ' || c == '\t')
			continue;
		else if (c == '#')
			return true;
		else
			return false;
	}
}

static void _load_model_file(const char *path, vector<string> &lines) {
	ifstream file(path);
	string line;
	while (!file.eof()) {
		getline(file, line);
		if (line == "" || _is_comment_line(line)) {
			continue;
		}
		lines.push_back(line);
	}
	file.close();
}

static void _split_line(const string &line, vector<string> &line_tokens) {
	line_tokens.clear();
	bool inword = false;
	string word;
	for (int i = 0; i < line.size(); i++) {
		char c = line[i];
		if (c != ' ' && c != '\t' && c != '\n') {
			inword = true;
			word += c;
		}
		else if (inword) {
			line_tokens.push_back(word);
			word.clear();
			inword = false;
		}
	}
	if (word.size()) {
		line_tokens.push_back(word);
	}
}

void simple_load_model(const char *path, render_object *ro) {
	vector<string> lines;
	_load_model_file(path, lines);
	
	vector<string> line_tokens;
	int curr_line = 0;

	_split_line(lines[curr_line], line_tokens);
	ro->name_ = line_tokens[0];
	int num_vert = atoi(line_tokens[1].c_str());
	int num_poly = atoi(line_tokens[2].c_str());

	ro->vlist_local_.clear();
	ro->vlist_trans_.clear();
	ro->poly_list_.clear();

	++curr_line;
	for (int i = 0; i < num_vert; i++) {
		_split_line(lines[curr_line + i], line_tokens);
		float x = atof(line_tokens[0].c_str());
		float y = atof(line_tokens[1].c_str());
		float z = atof(line_tokens[2].c_str());
		point4d vert = {
			x, y, z, 1
		};
		ro->add_vertex(vert);
	}

	curr_line += num_vert;
	for (int i = 0; i < num_poly; i++) {
		_split_line(lines[curr_line + i], line_tokens);
		int num_vert = atoi(line_tokens[0].c_str());
		int vi1 = atoi(line_tokens[1].c_str());
		int vi2 = atoi(line_tokens[2].c_str());
		int vi3 = atoi(line_tokens[3].c_str());

		polygon *pol = new polygon();
		pol->vlist_ptr_ = &ro->vlist_local_;
		pol->vertex_index_[0] = vi1;
		pol->vertex_index_[1] = vi2;
		pol->vertex_index_[2] = vi3;
		ro->poly_list_.push_back(pol);
	}
}

void simple_load_model(const char *path, render_polygon_list *rpl) {
	
}