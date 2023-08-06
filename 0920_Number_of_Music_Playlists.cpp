/*******************************************************************************
 * 0920_Number_of_Music_Playlists.cpp
 * Billy.Ljm
 * 06 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-music-playlists/
 *
 * Your music player contains n different songs. You want to listen to goal
 * songs (not necessarily different) during your trip. To avoid boredom, you
 * will create a playlist so that:
 * 
 * - Every song is played at least once.
 * - A song can only be played again only if k other songs have been played.
 *
 * Given n, goal, and k, return the number of possible playlists that you can
 * create. Since the answer can be very large, return it modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * For the first song, we have n choices; and for the second, we have n-1. This
 * continues until the k+1'th song comes into play again, giving n-k options.
 * This number of options stays constant for the remaining songs, giving the
 * number of playlists as n!/(n-k)! * (n-k)^(goal-k).
 *
 * To ensure that every song is played at least once, we find the number of
 * playlists from k songs, where every song will play at least once. Then we
 * find the number of playlists from k+1 songs, which is the quantity above
 * minus the number from k songs multiplied by the k choices of removed song.
 * Then playlists from k+2 songs, which is the quantity above minus k+1 songs
 * and k songs with the appropriate number of choices of removed song.
 *
 * !!! Modular Arithmetic !!!
 * We note that modulo is distributive across +,-,x, but not division. Thus,
 * we have to find the modular multiplicative inverses of the factorials.
 * Also note in c++ % is remainder, and it doesn't modulo negative numbers.
 *
 * This has a time complexity of O(n log goal), and a space complexity of  O(n), 
 * where n is the number of songs, and goal is the length of the playlists.
 ******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

/**
 * << operator for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Solution
 */
class Solution {
private:
	int modval = 1000000007; // value to modulo over

	/**
	 * Function to calculate (base^ pow) % mod
	 */
	long long powerMod(long long base, int pow, int mod) {
		if (pow == 0)
			return 1;

		long long result = 1;
		base = base % mod;

		while (pow > 0) {
			if (pow & 1) { // If the current power is odd
				result = (result * base) % mod;
			}
			base = (base * base) % mod;
			pow >>= 1; // Equivalent to pow = pow / 2
		}

		return result;
	}

public:
	int numMusicPlaylists(int n, int goal, int k) {
		// calculate factorials
		vector<long long> factorial(n + 1);
		vector<long long> invfactorial(n + 1);
		factorial[0] = 1LL;
		invfactorial[0] = 1LL;
		for (int i = 1; i < factorial.size(); i++) {
			factorial[i] = (1LL * factorial[i - 1] * i) % modval;
			invfactorial[i] = powerMod(factorial[i], modval-2, modval);
		}

		// calculate number of playlists with n=k+i songs
		// n!/(n-k)! * (n-k)^(goal-k) = (k+i)!/i! * i^(goal-k).
		vector<long long> nlists(n - k + 1);
		for (int i = 0; i < nlists.size(); i++) {
			nlists[i] = (factorial[k + i] * invfactorial[i]) % modval;
			nlists[i] = (nlists[i] * powerMod(i, goal - k, modval)) % modval;
		}

		// minus playlists with missing songs;
		long long tmp;
		for (int i = 0; i < nlists.size(); i++) {
			for (int j = 0; j < i; j++) {
				tmp = (nlists[j] * factorial[k + i]) % modval;
				tmp = (tmp * invfactorial[i - j]) % modval;
				tmp = (tmp * invfactorial[k + j]) % modval;
				nlists[i] = nlists[i] - tmp;
				if (nlists[i] < 0) nlists[i] += modval;
			}
		}
		
		return int(nlists.back());
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n, goal, k;

	// test case 1
	n = 3;
	goal = 3;
	k = 0;
	std::cout << "numMusicPlaylists(" << n << "," << goal << "," << k << ") = ";
	std::cout << sol.numMusicPlaylists(n, goal, k) << std::endl;

	// test case 2
	n = 2;
	goal = 3;
	k = 0;
	std::cout << "numMusicPlaylists(" << n << "," << goal << "," << k << ") = ";
	std::cout << sol.numMusicPlaylists(n, goal, k) << std::endl;

	// test case 3
	n = 2;
	goal = 3;
	k = 1;
	std::cout << "numMusicPlaylists(" << n << "," << goal << "," << k << ") = ";
	std::cout << sol.numMusicPlaylists(n, goal, k) << std::endl;

	return 0;
}