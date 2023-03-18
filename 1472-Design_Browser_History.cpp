/*******************************************************************************
 * 1472-Design_Browser_History.cpp
 * Billy.Ljm
 * 18 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/design-browser-history/
 * You have a browser of one tab where you start on the homepage and you can
 * visit another url, get back in the history number of steps or move forward in
 * the history number of steps. Implement the BrowserHistory class:
 *
 * - `BrowserHistory(string homepage)` Initializes the object with the homepage
 *   of the browser.
 * - `void visit(string url)` Visits url from the current page. It clears up all
 *   the forward history.
 * - `string back(int steps)` Move steps back in history. If you can only return
 *   x steps in the history and steps > x, you will return only x steps. Return
 *   the current url after moving back in history at most steps.
 * - `string forward(int steps)` Move steps forward in history. If you can only
 *   forward x steps in the history and steps > x, you will forward only x
 *   steps. Return the current url after forwarding in history at most steps.
 *
 * ===========
 * My Approach
 * ===========
 * The questions is just asking us to remember the past few strings, and
 * navigate between them. These strings can be stored as a vector and we just
 * have to move the index around.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class BrowserHistory {
public:
	std::vector<std::string> history; // history of pages
	size_t index; // current index of `history`

	BrowserHistory(std::string homepage) {
		//history.clear();
		history.push_back(homepage);
		index = 0;
	}

	void visit(std::string url) {
		history.resize(index + 1); // clear forward history
		history.push_back(url);
		index++;
	}

	std::string back(int steps) {
		if (steps > index) {
			index = 0;
		}
		else {
			index -= steps;
		}
		return history[index];
	}

	std::string forward(int steps) {
		index += steps;
		if (index >= history.size()) {
			index = history.size() - 1;
		}
		return history[index];
	}
};

int main(void) {
	BrowserHistory browserHistory = BrowserHistory("leetcode.com");
	browserHistory.visit("google.com");
	browserHistory.visit("facebook.com");
	browserHistory.visit("youtube.com");
	std::cout << browserHistory.back(1) << std::endl; // return "facebook.com"
	std::cout << browserHistory.back(1) << std::endl; // return "google.com"
	std::cout << browserHistory.forward(1) << std::endl; // return "facebook.com"
	browserHistory.visit("linkedin.com");
	browserHistory.forward(2);
	std::cout << browserHistory.back(2) << std::endl; // return "google.com"
	std::cout << browserHistory.back(7) << std::endl; // return "leetcode.com"
}