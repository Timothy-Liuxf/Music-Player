
#include "song.h"

std::vector<song> inputSong; 
int pai = DEFAULT_PAI; 

int middle[]{ 0, Do, re, mi, fa, so, la, xi }; 
int high[]{ 0, do1, re1, mi1, fa1, so1, la1, xi1 }; 
int low[]{ 0, qdo, qre, qmi, qfa, qso, qla, qxi };
int smiddle[]{ 0, 0, sre, 0, sfa, sso, sla, 0 };
int shigh[]{ 0, sdo1, sre1, 0, sfa1, sso1, sla1, 0 };
int slow[]{ 0, sqdo, sqre, 0, sqfa, sqso, sqla, 0 };
std::string tuneStr[] = { "0", "1", "2", "3", "4", "5", "6", "7" }; 

std::string operator* (std::string s, unsigned int n)
{
	if (n == 0u) return ""; 
	std::string s0 = s; 
	for (unsigned int i = 1; i < n; ++i)
	{
		s += s0; 
	}
	return s; 
}

//休止符0，中音1~7，高音^1~^7，低音_1~_7, 1/2拍[1]~[7]，1/4拍{1}~{7}，延长一半X.（X为某音符），连续一拍-
///其中优先级：^/_ > []/{} > # > ./- ，优先级高的距离数字更近
//第一个字符，一个大写字母，代表某大调（目前作保留字，无实际作用，用来标识新文件）
//第二行，一个分数y/x，表示以x分音符为一拍，每小节有y拍
//第三行，乐曲的速度，即1min内的拍数

int readSong(const char* src)
{
	std::ifstream fin(src, std::ios::in); 
	if (!fin) return FILE_NOT_EXIST; 
	int n, x, y; 
	char buf = 0; 
	char tuneTmp = '9';
	int height = MID;
	int shorten = 0;		
	int enlarge = 0; 
	int needToMinus = 0; 
	bool prolong = false; //延长0.5倍
	bool rise = false;		//升半音
	std::stack<char> stk; 
	buf = fin.peek(); 
	if (buf >= 'A' && buf <= 'Z')
	{
		fin.get(); 
		fin >> y; 
		if (!fin || fin.get() != '/') return GRAMMAR_MISTAKE; 
		fin >> x >> n; 
		if (!fin || x <= 0 || n <= 0) return GRAMMAR_MISTAKE; 
		pai = 4 * 60000 / (n * x); 
		justParsedFormat(buf, y, x, n); 
	}
	else pai = DEFAULT_PAI; 
	std::function<int(void)> PUSH_TUNE = [&]() {
		if (!rise)
		{
			switch (height)
			{
			case MID:
				inputSong.push_back(song(middle[tuneTmp - '0'], (enlarge ? enlarge + 1 : pow(2, -shorten)) * (prolong ? 1.5 : 1), 
					(std::string("[") * shorten + tuneStr[tuneTmp - '0'] + std::string("]") * shorten + (prolong ? std::string(".") : std::string("")) + (std::string("-") * enlarge)).c_str()));
				justPushedTune(); 
				break;
			case HIGH:
				inputSong.push_back(song(high[tuneTmp - '0'], (enlarge ? enlarge + 1 : pow(2, -shorten)) * (prolong ? 1.5 : 1), 
					(std::string("[") * shorten + std::string("^") + tuneStr[tuneTmp - '0'] + std::string("]") * shorten + (prolong ? std::string(".") : std::string("")) + (std::string("-") * enlarge)).c_str()));
				justPushedTune(); 
				break;
			case LOW:
				inputSong.push_back(song(low[tuneTmp - '0'], (enlarge ? enlarge + 1 : pow(2, -shorten)) * (prolong ? 1.5 : 1), 
					(std::string("[") * shorten + std::string("_") + tuneStr[tuneTmp - '0'] + std::string("]") * shorten + (prolong ? std::string(".") : std::string("")) + (std::string("-") * enlarge)).c_str()));
				justPushedTune(); 
				break;
			default:
				return 1;
			}
		}
		else
		{
			switch (height)
			{
			case MID:
				inputSong.push_back(song(smiddle[tuneTmp - '0'], (enlarge ? enlarge + 1 : pow(2, -shorten)) * (prolong ? 1.5 : 1), 
					(std::string("[") * shorten + std::string("#") + tuneStr[tuneTmp - '0'] + std::string("]") * shorten + (prolong ? std::string(".") : std::string("")) + (std::string("-") * enlarge)).c_str()));
				justPushedTune();
				break;
			case HIGH:
				inputSong.push_back(song(shigh[tuneTmp - '0'], (enlarge ? enlarge + 1 : pow(2, -shorten)) * (prolong ? 1.5 : 1), 
					(std::string("[") * shorten + std::string("#^") + tuneStr[tuneTmp - '0'] + std::string("]") * shorten + (prolong ? std::string(".") : std::string("")) + (std::string("-") * enlarge)).c_str()));
				justPushedTune();
				break;
			case LOW:
				inputSong.push_back(song(slow[tuneTmp - '0'], (enlarge ? enlarge + 1 : pow(2, -shorten)) * (prolong ? 1.5 : 1), 
					(std::string("[") * shorten + std::string("#_") + tuneStr[tuneTmp - '0'] + std::string("]") * shorten + (prolong ? std::string(".") : std::string("")) + (std::string("-") * enlarge)).c_str()));
				justPushedTune(); 
				break;
			default:
				return 1;
			}
		}
		////std::cout << enlarge << "||" << shorten << "|||" << (enlarge ? enlarge + 1 : pow(2, -shorten)) * (prolong ? 1.5 : 1) << "|<>|" << tuneTmp << std::endl;
		tuneTmp = '9';
		height = MID;
		enlarge = 0;
		rise = prolong = false; 
		shorten -= needToMinus; 
		needToMinus = 0; 
		return 0; 
	}; 
	while (fin >> buf)
	{
		switch (buf)
		{
		case '{':
			if (tuneTmp != '9')
			{
				if (PUSH_TUNE()) return GRAMMAR_MISTAKE; 
				
			}
			shorten += 2; 
			stk.push('{'); 
			break;
		case '[':
			if (tuneTmp != '9')
			{
				if (PUSH_TUNE()) return GRAMMAR_MISTAKE; 
			}
			++shorten;
			stk.push('[');
			break; 
		case '^':
			if (tuneTmp != '9') if (PUSH_TUNE()) return GRAMMAR_MISTAKE;
			if (height != MID) return GRAMMAR_MISTAKE; 
			height = HIGH; 
			break; 
		case '_':
			if (tuneTmp != '9') if (PUSH_TUNE()) return GRAMMAR_MISTAKE;
			if (height != MID) return GRAMMAR_MISTAKE; 
			height = LOW; 
			break; 
		case '#':
			if (rise) return GRAMMAR_MISTAKE; 
			if (tuneTmp != '9') if (PUSH_TUNE()) return GRAMMAR_MISTAKE;
			rise = true; 
			break; 
		case ']':
			if (stk.empty() || stk.top() != '[' || shorten - needToMinus < 1) return GRAMMAR_MISTAKE; 
			stk.pop(); 
			++needToMinus;
			break; 
		case '}':
			if (stk.empty() || stk.top() != '{' || shorten - needToMinus < 2) return GRAMMAR_MISTAKE;
			stk.pop(); 
			needToMinus += 2; 
			break; 
		case '.':
			if (prolong) return GRAMMAR_MISTAKE;
			prolong = true; 
			break; 
		case '-':
			if(shorten || needToMinus || tuneTmp == '9' || prolong) return GRAMMAR_MISTAKE; 
			++enlarge; 
			break; 
		case '0': case '1': case '2': case '3': 
		case '4': case '5': case '6': case '7': 
			if (tuneTmp != '9') if (PUSH_TUNE()) return GRAMMAR_MISTAKE;
			tuneTmp = buf; 
			break; 
		default:
			continue; 
		}
	}
	if (tuneTmp != '9') PUSH_TUNE();
	if (!stk.empty()) return GRAMMAR_MISTAKE; 
	fin.close(); 
	return INPUT_SUCCESS; 
}

