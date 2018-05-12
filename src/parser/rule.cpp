
#include <parser/rule.h>

#include <parser/lexer.h>

namespace Manticore
{
	Rule::Rule ()
	{
		
	}
	
	int Rule::size ()
	{
		return parts.size ();
	}
	
	std::string &Rule::operator[] (int place)
	{
		return parts[place];
	}
	
	std::vector<Rule> parseRule (std::string name, std::string rule)
	{
		std::vector<Rule> rules;
		Rule currentRule;
		
		Lexer l = Lexer ();
		l.whitespace = {" ", "\t", "\n"};
		l.feed (rule);
		
		while (!l.eos ())
		{
			Token t = l.next ();
			if (t == "\'" or t == "\"")
			{
				// this is a string of characters
				std::string r = "\'";
				while (!l.eos ()) // while not end-of-stream
				{
					Token t = l.next ();
					if (t == "\'" or t == "\"")
					{
						r += '\'';
						break;
					}
					else if (t == "\\")
					{
						Token a = l.peek ();
						if (a == "\'" or a == "\"")
						{
							r += a == "\'" ? '\'' : '\"';
							l.skip (1);
						}
						else if (a == "\\")
						{
							r += "\\\\";
							l.skip (1);
						}
					}
					else
					{
						r += t.token;
					}
				}
				
				currentRule.parts.push_back (r);
			}
			else if (t == "<")
			{
				// this is a string of characters
				std::string r = "<";
				while (!l.eos ()) // while not end-of-stream
				{
					Token t = l.next ();
					if (t == ">")
					{
						r += '>';
						break;
					}
					else
					{
						r += t.token;
					}
				}
				
				currentRule.parts.push_back (r);
			}
			else if (t == "|") // the or statement
			{
				currentRule.name = name;
				rules.push_back (currentRule);
				currentRule = Rule ();
			}
			else if (t == "!") // token to denote what should be added to the AST
			{
				currentRule.parts.push_back ("!");
			}
			else if (t == "(") // this just functions as a grouping mechanism
			{
				currentRule.parts.push_back ("(");
			}
			else if (t == ")") // this just functions as a grouping mechanism
			{
				currentRule.parts.push_back (")");
			}
			else if (t == "{") // this just functions as a maybe-this-appears mechanism
			{
				currentRule.parts.push_back ("(");
			}
			else if (t == "}") // this just functions as a maybe-this-appears mechanism
			{
				currentRule.parts.push_back ("}");
			}
			else if (t == "*") // this just functions as a this token may repeat as many times as it appears mechanism
			{
				currentRule.parts.push_back ("*");
			}
			else
			{
				std::cerr << "unknown token in stream: " << t << std::endl;
			}
		}
		
		if (currentRule.parts.size () > 0)
		{
			currentRule.name = name;
			rules.push_back (currentRule);
			currentRule = Rule ();
		}
		
		return rules;
	}
}
