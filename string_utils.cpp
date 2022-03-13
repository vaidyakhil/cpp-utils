#include <bits/stdc++.h>
using namespace std;

class StringUtils {
	/*
  	**	string::substr, takes length as second param
  	**	string::find has several forms one which takes char as input also. handy!
  	**	string::compare returns 0 if matched, < 0 if lexically less than passed string
	*/

	/*
  	**	if you need a longest palindromic string starting from start or end of a given string,
  	**	use kmp with patern as give string, text as reversed of given string,
  	**	return prefix[m-1] 
	*/

	private:

		string getComopositeString(string text) {
			string res = "$";
			int n = text.size();

			for (int i =0; i<n; i++) {
				res+= "#" + text[i];
			}
			res+= "$";
			return res;
		}

  public:

		bool isLetter(char ch) {
		  	return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122);
		}

		bool isNumeric(char ch) {
		  	return (ch >= 48 && ch <= 57);
		}

		bool isAlphaNumeric(char ch) {
		 	return isLetter(ch) || isNumeric(ch);
		}

		bool compAlphaNumeric(char ch1, char ch2) {
			if (ch1 == ch2) {
			return true;
			}

			if (isLetter(ch1) && isLetter(ch2)) {
			return ch1 < ch2 ? ch1 + 32 == ch2 : ch2 + 32 == ch1;
			}

			return false;
		}

		/*
		** KMP algo for pattern matching / check substring  algo
		*/
		bool matches(string text, string pattern) {
			string TEST = pattern + "&" + text; // delimitter string "&" that is not present in either of string.
			int n = TEST.size();
			int patLen= pattern.size();

			/*
			** stores for ith index "LENGTH" of TEST string such that:
			** TEST[0..(prefix[i]-1)] = TEST[(i-prefix[i]+1)..i]
			*/
			vector<int> prefix = vector<int>(n, 0); 

			/*
			** if TEST[i] == TEST[prefix[i-1]], prefix[i] = prefix[i-1] + 1;
			** else move to prefix[prefix[i-1] - 1]. (calling it x)
			** by logic of prefix array, x is the next pos where we need to match 
			** TEST[i] such that TEST[(i-x+1)...i-1] is already matched
			*/

			for (int i=1; i<n; i++) {
				int j= prefix[i-1];
				while (j>0 && TEST[j] != TEST[i]) { 
				  j = prefix[j-1]; **
				}
				if (TEST[j] == TEST[i]) {
				  j++;
				}
				prefix[i] = j;
				if(prefix[i] == patLen) {
				  return true;
				}
			}

		  	return false;
		}

		
		/* manacher */
		int longestPalindromicString(string text) {
			string compString = getComopositeString(text);
			int m = compString.size();

			vector<int> pal = vector<int>(m, 0);
			int c=0, r=0;

			for (int i=1; i<m; i++) {
				if (i < r) {
				  int mirrorIndex= c - (i-c);
				  pal[i] = minm(pal[mirrorIndex], r - i);
				}
				while(i + pal[i] < n && text[i - pal[i] - 1] == text[i + pal[i] + 1]) {
				  pal[i]++;
				}

				if (i+ pal[i] > r) {
				  r = i + pal[i];
				  c = i;
				}
			}
		}

		string fromInt(int n) {
	        string res = "";
	        while (n) {
	        	res = res + (char)(n%10 + '0');
	        	n/=10;
	        }
	        reverse(res.begin(), res.end());
	        return res;
		}
};