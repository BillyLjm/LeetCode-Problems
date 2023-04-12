/*******************************************************************************
 * 0071-Simplify_Path.cpp
 * Billy.Ljm
 * 12 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/simplify-path/
 * Given a string path, which is an absolute path (starting with a slash '/') to
 * a file or directory in a Unix-style file system, convert it to the simplified
 * canonical path.
 *
 * In a Unix-style file system, a period '.' refers to the current directory, a
 * double period '..' refers to the directory up a level, and any multiple
 * consecutive slashes (i.e. '//') are treated as a single slash '/'. For this
 * problem, any other format of periods such as '...' are treated as
 * file/directory names.
 *
 * The canonical path should have the following format:
 * - The path starts with a single slash '/'.
 * - Any two directories are separated by a single slash '/'.
 * - The path does not end with a trailing '/'.
 * - The path only contains the directories on the path from the root directory
 *   to the target file or directory (i.e., no period '.' or double period '..')
 *
 * Return the simplified canonical path.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to parse the directory from left to right and navigate through
 * the directories appropriately. Then, we just concatenate the resulting
 * directories together into a path.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the length of the string.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

class Solution {
public:
	/**
	 * Converts an absolute path to a canonical path
	 *
	 * @param path absolute path to convert
	 *
	 * @return canonical path
	 */
	std::string simplifyPath(std::string path) {
		size_t id1 = 0, id2 = 0; // crawlers
		std::string dir; // directory name
		std::vector<std::string> pathname; // path name

		while (id2 < path.size()) {
			// find next directory name
			id1 = id2; // previous '/'
			id2++; // next '/'
			while (path[id2] != '/' and id2 < path.size()) {
				id2++;
			}
			dir = path.substr(id1 + 1, id2 - id1 - 1);

			// check directory name
			if (dir == "." or dir == "") { // ignore
				;
			}
			else if (dir == "..") { // go up a level
				if (not pathname.empty()) {
					pathname.pop_back();
				}
			}
			else {
				pathname.push_back(dir);
			}
		}

		// create canonical path name
		if (pathname.size() == 0) {
			dir = "/";
		}
		else {
			dir = "";
			for (std::string s : pathname) {
				dir += "/" + s;
			}
		}
		return dir;
	}
};

// << for vector
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (auto it = v.begin(); it != v.end(); it++) {
		os << *it;
		if (it != v.end() - 1) {
			os << ", ";
		}
	}
	os << "]";
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::string path;

	// test case 1
	path = "/home/";
	std::cout << "simplifyPath(" << path << ") = " << sol.simplifyPath(path)
		<< std::endl;

	// test case 2
	path = "/../";
	std::cout << "simplifyPath(" << path << ") = " << sol.simplifyPath(path)
		<< std::endl;

	// test case 3
	path = "/home//foo/";
	std::cout << "simplifyPath(" << path << ") = " << sol.simplifyPath(path)
		<< std::endl;

	return 0;
}