/*******************************************************************************
 * 0399-Evaluate_Division.cpp
 * Billy.Ljm
 * 20 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/evaluate-division/
 *
 * You are given an array of variable pairs equations and an array of real
 * numbers values, where equations[i] = [Ai, Bi] and values[i] represent the
 * equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a
 * single variable.
 *
 * You are also given some queries, where queries[j] = [Cj, Dj] represents the
 * jth query where you must find the answer for Cj / Dj = ?.
 *
 * Return the answers to all queries. If a single answer cannot be determined,
 * return -1.0.
 *
 * ===========
 * My Approach
 * ===========
 * We can view this problem as a directed graph, where the numerator/denominator
 * indicate the direction of the graph. For example, finding A/C is equivalent
 * to find a path from the node A to C, such as A to B to C which would
 * correspond to A/B * B/C. Then, we just have to find a path between the
 * desired nodes, which I'll do with a recursive depth-first search.
 *
 * This has a time complexity of O(e * q) and space complexity of O(e), where 
 * e is the number of equations and q the number of queries.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Recursively search for node in graph
	 *
	 * @param val current value, will be multiplied by next edge
	 * @param node current node to search from
	 * @param dest final node to stop at
	 * @param visited nodes visited already
	 * @param graph graph[A][B] = A/B
	 *
	 * @return product of all edges of found path, or -1.0 if dest not found
	 */
	double recurse(double val, string node, string dest, set<string>& visited,
		unordered_map<string, unordered_map<string, double>>& graph) {
		// if destination found (and they're valid), return value
		if (node == dest and graph.find(node) != graph.end()) {
			return val;
		}

		// else recurse through all unvisited neighbours
		double tmp;
		for (auto it : graph[node]) {
			if (visited.find(it.first) == visited.end()) {
				visited.insert(it.first);
				tmp = recurse(val * it.second, it.first, dest, visited, graph);
				if (tmp != -1.0) return tmp; // if destination found, echo value
			}
		}

		// destination not found in all neighbours, return -1
		return -1.0;
	}

public:
	/**
	 * Evaulates the fractions b/w two algebraic variables based on a set of
	 * other known fractions
	 *
	 * @param equations known equations[i] = [numerator[i], denominator[i]]
	 * @param values known values[i] = numerator[i] / denominator[i]
	 * @param queries unknown queries[i] = [qnumerator[i], qdenominator[i]]
	 *
	 * @return unknown qvalues[i] = qnumerator[i] / qdenominator[i]
	 */
	vector<double> calcEquation(
		vector<vector<string>>& equations,
		vector<double>& values,
		vector<vector<string>>& queries) {
		// build graph (graph[A][B] = A/B)
		unordered_map<string, unordered_map<string, double>> graph;
		for (int i = 0; i < equations.size(); i++) {
			graph[equations[i][0]][equations[i][1]] = values[i];
			graph[equations[i][1]][equations[i][0]] = 1 / values[i];
		}

		// answer queries
		set<string> visited;
		vector<double> answers;
		for (int i = 0; i < queries.size(); i++) {
			visited.clear();
			answers.push_back(recurse(1, queries[i][0], queries[i][1], visited,
				graph));
		}

		return answers;
	}
};

/**
 * << operator for vectors
 */
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<vector<string>> equations;
	vector<double> values;
	vector<vector<string>> queries;

	// test case 1
	equations = { {"a", "b"}, {"b", "c"} };
	values = { 2.0, 3.0 };
	queries = { {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"} };
	cout << "calcEquation(" << equations << "," << values << "," << queries
		<< ") = " << sol.calcEquation(equations, values, queries) << endl;

	// test case 2
	equations = { {"a", "b"}, {"b", "c"}, {"bc", "cd"} };
	values = { 1.5, 2.5, 5.0 };
	queries = { {"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"} };
	cout << "calcEquation(" << equations << "," << values << "," << queries
		<< ") = " << sol.calcEquation(equations, values, queries) << endl;

	// test case 3;
	equations = { {"a", "b"} };
	values = { 0.5 };
	queries = { {"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"} };
	cout << "calcEquation(" << equations << "," << values << "," << queries
		<< ") = " << sol.calcEquation(equations, values, queries) << endl;

	return 0;
}