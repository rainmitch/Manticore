
#include <parser/lexer.h>

bool contains (std::vector<std::string> values, char c)
{
	std::string delim = std::string (1, c);
	for (std::string v : values)
		if (v == delim)
			return true;
	return false;
}

bool isWord (char c)
{
	return  (c >= 'a' and c <= 'z') or
			(c >= 'A' and c <= 'Z') or
			(c >= '_') or
			(c >= '0' and c <= '9');
}

namespace Manticore
{
	Token::Token () : Token ("", 0x00, 0x00)
	{
		
	}

	Token::Token (std::string token, uint32_t line, uint32_t col)
	{
		this->token = token;
		this->line = line;
		this->col = col;
	}

	Lexer::Lexer ()
	{
		internalPointer = 0;
	}

	Token &Lexer::operator[] (int place)
	{
		return tokens[place];
	}

	uint32_t Lexer::size ()
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
			if (isWord (data[i]))
			{
				std::string tmp;
				
				while (i < data.size ())
				{
					if (!isWord (data[i]))
					{
						break;
					}
					else
					{
						tmp += data[i];
						col++;
						i++;
					}
				}
				
				tokens.push_back ({tmp, line, col-1});
			}
			else if (contains (whitespace, data[i]))
			{
				if (std::string (newline.size (), data[i]) == newline)
				{
					line++;
					col = 0;
					i += newline.size ();
				}
				else
				{
					col++;
					i++;
				}
			}
			else
			{
				tokens.push_back ({std::string (1, data[i]), line, col});
				col++;
				i++;
			}
		}
	}
	
	void Lexer::push (Token t)
	{
		tokens.push_back (t);
	}
	
	Lexer Lexer::slice (int start, int length)
	{
		Lexer lex;
		for (int i = start; i < start + length; i++)
		{
			lex.push (tokens[i]);
		}
		
		return lex;
	}
	
	Token Lexer::next ()
	{
		return tokens[internalPointer++];
	}
	
	Token Lexer::peek ()
	{
		return tokens[internalPointer]; // return without increment, just sneak a peek
	}
	
	bool Lexer::eos ()
	{
		return internalPointer >= tokens.size ();
	}
	
	void Lexer::reset ()
	{
		internalPointer = 0;
	}
	
	bool Lexer::empty ()
	{
		return tokens.empty ();
	}
	
	void Lexer::rewind (int steps)
	{
		internalPointer -= steps;
	}
	
	void Lexer::skip (int steps)
	{
		internalPointer += steps;
	}
	
	void Lexer::stepBack ()
	{
		rewind (1);
	}
}
