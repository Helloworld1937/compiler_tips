// C���Դʷ�������
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct _2tup
{
	string token;
	int id;
};

bool is_blank(char ch)
{
	return ch == ' ' || ch == '    ';
}

bool adv(string& token, char& ch, string::size_type& pos, const string& prog)
{
	token += ch;
	++pos;
	if (pos >= prog.size())
	{
		return false;
	}
	else
	{
		ch = prog[pos];
		return true;
	}
}

bool gofor(char& ch, string::size_type& pos, const string& prog)
{
	++pos;
	if (pos >= prog.size())
	{
		return false;
	}
	else
	{
		ch = prog[pos];
		return true;
	}
}

_2tup scanner(const string& prog, string::size_type& pos, const map<string, int>& keys, int& row)
{
	/*
	if
	��ʾ��
	else if
	����
	else
	����
	*/
	_2tup ret;
	string token;
	int id = 0;

	char ch;
	ch = prog[pos];

	while (is_blank(ch))
	{
		++pos;
		ch = prog[pos];
	}
	// �жϱ�ʾ�����ؼ���
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
	{
		while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
		{
			token += ch;
			if (!gofor(ch, pos, prog))
			{
				break;
			}
			//++pos;
			//ch = prog[pos];
		}
		// �����ȿ�������������ʾ��
		id = keys.size();

		// ��֤�Ƿ��ǹؼ���
		map<string, int>::const_iterator cit = keys.find(token);
		if (cit != keys.end())
		{
			id = cit->second;
		}
	}
	// ʶ����
	else if ((ch >= '0' && ch <= '9') || ch == '.')
	{
		while (ch >= '0' && ch <= '9' || ch == '.')
		{
			token += ch;
			if (!gofor(ch, pos, prog))
			{
				break;
			}
			//++pos;
			//ch = prog[pos];
		}
		id = keys.size() - 1;
		int dot_num = 0;
		for (string::size_type i = 0; i != token.size(); ++i)
		{
			if (token[i] == '.')
			{
				++dot_num;
			}
		}
		if (dot_num > 1)
		{
			id = -1;
		}
	}
	else
	{
		map<string, int>::const_iterator cit;
		switch (ch)
		{
		case '-': // - ������
			token += ch;
			if (gofor(ch, pos, prog))
				//++pos;
				//ch = prog[pos];
			{
				if (ch == '-' || ch == '=' || ch == '>') // -- ������
				{
					token += ch;
					gofor(ch, pos, prog);
					//++pos;
					//ch = prog[pos];
				}
			}
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;

		case '!': // ! ������        
		case '%': // % ������
		case '*':
		case '^':
		case '=':
			token += ch;
			if (gofor(ch, pos, prog))
				//++pos;
				//ch = prog[pos];
			{
				if (ch == '=') // !% %= ������
				{
					token += ch;
					gofor(ch, pos, prog);
					//++pos;
					//ch = prog[pos];
				}
			}
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;

		case '/': // / ������
			token += ch;
			if (gofor(ch, pos, prog))
				//++pos;
				//ch = prog[pos];
			{
				if (ch == '=') // /= ������
				{
					token += ch;
					gofor(ch, pos, prog);
					//++pos;
					//ch = prog[pos];
				}
				else if (ch == '/') // ����ע��
				{
					token += ch;
					++pos;
					while (pos < prog.size())
					{
						ch = prog[pos];
						if (ch == '\n')
						{
							break;
						}
						token += ch;
						++pos;
					}
					if (pos >= prog.size())
					{
						;
					}
					else
					{
						;
					}
					id = keys.size() - 2;
					break;
				}
				else if (ch == '*') // ע��
				{
					// ʵ�ַ�ʽ1
					//string::size_type p1 = pos - 1;
					//
					//string::size_type p2 = prog.find("*/", p1);
					//if (p2 != string::npos)
					//{
					//    token = prog.substr(p1, p2 - p1 + 2);

					//    pos = p2 + 2;
					//    ch = prog[pos];

					//    id = keys.size() - 2;
					//}
					//else
					//{
					//    id = -1;
					//}
					//break;

					// ע�͵���һ��ʵ�֣�Ϊ�˵õ������к�
					token += ch;
					//++pos;
					if (!gofor(ch, pos, prog))
					{
						token += "\n!!!ע�ʹ���!!!";
						id = -10;
						break;
					}
					//ch = prog[pos];
					if (pos + 1 >= prog.size())
					{
						token += ch;
						token += "\n!!!ע�ʹ���!!!";
						id = -10;
						break;
					}
					char xh = prog[pos + 1];
					while (ch != '*' || xh != '/')
					{
						token += ch;
						if (ch == '\n')
						{
							++row;
						}
						//++pos;
						if (!gofor(ch, pos, prog))
						{
							token += "\n!!!ע�ʹ���!!!";
							id = -10;
							ret.token = token;
							ret.id = id;
							return ret;
						}
						//ch = prog[pos];
						if (pos + 1 >= prog.size())
						{
							token += ch;
							token += "\n!!!ע�ʹ���!!!";
							id = -10;
							ret.token = token;
							ret.id = id;
							return ret;
						}
						xh = prog[pos + 1];
					}
					token += ch;
					token += xh;
					pos += 2;
					ch = prog[pos];
					id = keys.size() - 2;
					break;
				}
			}
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;

		case '&':
			token += ch;
			if (gofor(ch, pos, prog))
				//++pos;
				//ch = prog[pos];
			{
				if (ch == '&' || ch == '=')
				{
					token += ch;
					gofor(ch, pos, prog);
					//++pos;
					//ch = prog[pos];
				}
			}
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;

		case '|':
			token += ch;
			if (gofor(ch, pos, prog))
				//++pos;
				//ch = prog[pos];
			{
				if (ch == '|' || ch == '=')
				{
					token += ch;
					gofor(ch, pos, prog);
					//++pos;
					//ch = prog[pos];
				}
			}
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;

		case '+':
			token += ch;
			if (gofor(ch, pos, prog))
				//++pos;
				//ch = prog[pos];
			{
				if (ch == '+' || ch == '=')
				{
					token += ch;
					gofor(ch, pos, prog);
					//++pos;
					//ch = prog[pos];
				}
			}
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;

		case '<':
			token += ch;
			if (gofor(ch, pos, prog))
				//++pos;
				//ch = prog[pos];
			{
				if (ch == '<')
				{
					token += ch;
					if (gofor(ch, pos, prog))
						//++pos;
						//ch = prog[pos];
					{
						if (ch == '=')
						{
							token += ch;
							gofor(ch, pos, prog);
							//++pos;
							//ch = prog[pos];
						}
					}
				}
				else if (ch == '=')
				{
					token += ch;
					gofor(ch, pos, prog);
					//++pos;
					//ch = prog[ch];
				}
			}
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;

		case '>':
			token += ch;
			if (gofor(ch, pos, prog))
				//++pos;
				//ch = prog[pos];
			{
				if (ch == '>')
				{
					token += ch;
					if (gofor(ch, pos, prog))
						//++pos;
						//ch = prog[pos];
					{
						if (ch == '=')
						{
							token += ch;
							gofor(ch, pos, prog);
							//++pos;
							//ch = prog[pos];
						}
					}
				}
				else if (ch == '=')
				{
					token += ch;
					gofor(ch, pos, prog);
					//++pos;
					//ch = prog[pos];
				}
			}
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;

		case '(':
		case ')':
		case ',':
		case '.':
		case ':':
		case ';':
		case '?':
		case '[':
		case ']':
		case '{':
		case '}':
		case '~':
		case '"':
			token += ch;
			gofor(ch, pos, prog);
			//++pos;
			//ch = prog[pos];
			cit = keys.find(token);
			if (cit != keys.end())
			{
				id = cit->second;
			}
			break;


			//case '#':
			//    id = 0;
			//    token += ch;
			//    break;

		case '\n':
			token += "����";
			++pos;
			ch = prog[pos];
			id = -2;
			break;
		default:
			token += "����";
			++pos;
			ch = prog[pos];
			id = -1;
			break;
		}
	}
	ret.token = token;
	ret.id = id;

	return ret;
}

void init_keys(const string& file, map<string, int>& keys)
{
	ifstream fin(file.c_str());
	if (!fin)
	{
		cerr << file << " doesn't exist!" << endl;
		exit(1);
	}
	keys.clear();
	string line;
	string key;
	int id;
	while (getline(fin, line))
	{
		istringstream sin(line);
		sin >> key >> id;
		keys[key] = id;
	}
}

void read_prog(const string& file, string& prog)
{
	ifstream fin(file.c_str());
	if (!fin)
	{
		cerr << file << " error!" << endl;
		exit(2);
	}
	prog.clear();
	string line;
	while (getline(fin, line))
	{
		prog += line + '\n';
	}
}

int main()
{
	map<string, int> keys;
	init_keys("c_keys.txt", keys);

	string prog;
	read_prog("prog.txt", prog);

	vector< _2tup > tups;
	string token, id;

	string::size_type pos = 0;
	int row = 1;

	_2tup tu;

	cout << prog << endl << endl;

	// prog += "#"; // ��ʶ��ֵ����ʵ���Լ�� pos ���б��Ƿ���ֹ

	int no = 0;

	do
	{
		tu = scanner(prog, pos, keys, row);

		switch (tu.id)
		{
		case -1:
			++no;
			cout << no << ": ";
			cout << "Error in row" << row << "!" << '<' << tu.token << "," << tu.id << '>' << endl;
			tups.push_back(tu);
			break;
		case -2:
			++row;
			// cout << '<' << tu.token<< "," << tu.id << '>' << endl;
			break;
		default:
			++no;
			cout << no << ": ";
			cout << '<' << tu.token << "," << tu.id << '>' << endl;
			tups.push_back(tu);
			break;
		}
	} while (/*tu.id != 0 && */pos < prog.size());

	cout << endl << tups.size() << endl;
	return 0;
}