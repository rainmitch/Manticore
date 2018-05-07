
#include <parser/lexer.h>

bool contains (std::vector<std::string> values, char c)
{
	std::string delim = std::string (1, c);
	for (std::string v : values)
		if (v == delim)
			return true;
	return false;
}

namespace Manticore
{
	Token::Token () : Token (0x00, 0x00, 0x00)
	{
		
	}

	Token::Token (char token, uint32_t line, uint32_t col)
	{
		this->token = token;
		this->line = line;
		this->col = col;
	}

	Lexer::Lexer ()
	{
		
	}

	Token &Lexer::operator[] (int place)
	{
		return tokens[place];
	}

	int Lexer::size ()
	{
		return tokens.size ();
	}

	void Lexer::feed (std::string data)
	{
		uint32_t line = 1;
		uint32_t col = 0;
		
		unsigned int i = 0;
		while (i < data.size ())
		{
			if (contains (whitespace, data[i]))
			{
				if (std::string (1, data[i]) == newline)
				{
					line++;
					col = 0;
				}
				else
				{
					col++;
				}
				i++;
			}
			else
			{
				tokens.push_back ({data[i], line, col});
				col++;
				i++;
			}
		}
	}
}
