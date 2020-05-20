
#include "song.h"

std::vector<song> inputSong; 

int middle[]{ 0, Do, re, mi, fa, so, la, xi }; 
int high[]{ 0, do1, re1, mi1, fa1, so1, la1, xi1 }; 
int low[]{ 0, qdo, qre, qmi, qfa, qso, qla, qxi };

//休止符0，中音1~7，高音^1~^7，低音_1~_7, 1/2拍[1]~[7]，1/4拍{1}~{7}，延长一半X.（X为某音符），连续一拍-
//其中优先级：^/_ > []/{} > ./- ，优先级高的距离数字更近

int readSong(const char* src)
{
	std::ifstream fin(src, std::ios::in); 
	if (!fin) return FILE_NOT_EXIST; 
	char buf; 
	char tuneTmp = '9';
	int height = MID;
	int length = WHOLE;
	int prolong = false; //延长0.5倍
	std::stack<char> stk; 
	while (fin >> buf)
	{
		switch (buf)
		{
		case '{':
			if (!stk.empty()) return GRAMMAR_MISTAKE; 
			if (tuneTmp != '9') PUSH_TUNE(); 
			stk.push('{'); 
			length = QUARTER; 
			break;
		case '[':
			if (!stk.empty()) return GRAMMAR_MISTAKE; 
			if (tuneTmp != '9') PUSH_TUNE();
			stk.push('['); 
			length = HALF; 
			break; 
		case '^':
			if (tuneTmp != '9') PUSH_TUNE();
			if (height != MID) return GRAMMAR_MISTAKE; 
			height = HIGH; 
			break; 
		case '_':
			if (tuneTmp != '9') PUSH_TUNE();
			if (height != MID) return GRAMMAR_MISTAKE; 
			height = LOW; 
			break; 
		case ']':
			if (stk.empty() || stk.top() != '[' || tuneTmp == '9') return GRAMMAR_MISTAKE;
			stk.pop(); 
			break; 
		case '}':
			if (stk.empty() || stk.top() != '{' || tuneTmp == '9') return GRAMMAR_MISTAKE;
			stk.pop(); 
			break; 
		case '.':
			if (prolong) return GRAMMAR_MISTAKE;
			prolong = true; 
			break; 
		case '-':
			if(length == HALF || length == QUARTER || prolong) return GRAMMAR_MISTAKE; 
			++length; 
			break; 
		case '0': case '1': case '2': case '3': 
		case '4': case '5': case '6': case '7': 
			if (tuneTmp != '9') PUSH_TUNE();
			tuneTmp = buf; 
			break; 
		default:
			continue; 
		}
	}
	if (tuneTmp != '9') PUSH_TUNE();
	fin.close(); 
	return INPUT_SUCCESS; 
}

