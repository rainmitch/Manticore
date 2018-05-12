
#include <parser/parser.h>

#include <parser/lexer.h>
#include <parser/rule.h>
#include <parser/ast.h>


std::string strip (std::string input)
{
	return input.substr (1, input.size () - 2);
}

bool isWordString (std::string input)
{
	for (char &c : input)
	{
		if (!isWord (c))
			return false;
	}
	
	return true;
}

namespace Manticore
{
	AST Parser::parseFunction (Lexer tokens, std::vector<Rule> internalRules, ParserHelper &helper)
	{
		AST out = AST ("ROOT");
		std::vector<Rule> rules;
		if (internalRules.size () > 0)
			rules = internalRules;
		
		int tmpPos = helper.pos;
		for (unsigned int r = 0; r < rules.size (); r++)
		{
			int pos = tmpPos;
			int rulePos = 0;
			bool pass = true;
			bool pushFlag = false;
			bool pushFlagGlobal = false;
			bool pushedStack = false;
			
			AST tree = AST ("<" + rules[r].name + ">");
			
			for (int rp = 0; rp < rules[r].size (); rp++)
			{
				rulePos = rp;
				if (rules[r][rp][0] == '\'')
				{
					if (strip (rules[r][rp]) == tokens[pos])
					{
						if (pushFlag or pushFlagGlobal)
						{
							tree.add (tokens[pos]);
							pushFlag = false;
						}
						
						pos++;
					}
					else
					{
						pass = false;
						break;
					}
				}
				else if (rules[r][rp][0] == '<')
				{
					if (rules[r][rp] == "<word>")
					{
						if (isWordString (tokens[pos].token))
						{
							if (pushFlag or pushFlagGlobal)
							{
								AST t = AST ("<word>");
								t.add (tokens[pos]);
								tree.add (t);
							}
							pos++;
						}
						else
						{
							pass = false;
							break;
						}
					}
					else
					{
						std::string name = strip (rules[r][rp]);
						auto rs = getRuleByName (name);
						
						ParserHelper h = helper;
						AST t = parseFunction (tokens, rs, h);
						if (t.value == "ROOT" and t.size () != 0)
						{
							pos = h.pos; // update cursor pos
							if (pushFlag or pushFlagGlobal)
							{
								for (AST &child : t.children)
									tree.add (child);
								pushFlag = false;
							}
						}
						else
						{
							std::cout << "Branch failed" << std::endl;
							pass = false;
							break;
						}
					}
				}
				else if (rules[r][rp] == "!")
				{
					pushFlag = true;
					if (rp+1 < rules[r].size ())
						if (rules[r][rp+1] == "(")
							pushFlagGlobal = true;
				}
				else if (rules[r][rp] == "(")
				{
					pushedStack = true;
				}
				else if (rules[r][rp] == ")")
				{
					pushedStack = false;
					pushFlag = false;
					pushFlagGlobal = false;
				}
			}
			
			if (pass)
			{
				tmpPos = pos;
				out.add (tree);
			}
			else
			{
				std::cerr << "Parser failed:" << std::endl;
				std::cerr << "   Parsing Rule: " << rules[r].name << std::endl;
				std::cerr << "   Parsing Token: " << rules[r][rulePos] << std::endl;
				std::cerr << "   Lexer Token: " << tokens[pos] << std::endl;
			}
		}
		
		helper.pos = tmpPos;
		
		return out;
	}
	
	AST Parser::parse (std::string input)
	{
		Lexer lex;
		lex.whitespace = {" ", "\t", "\n"};
		lex.feed (input);
		return parse (lex);
	}
	
	AST Parser::parse (Lexer lex)
	{
		auto rs = getRuleByName (rootRule);
		
		ParserHelper help = {0};
		return parseFunction (lex, rs, help);
	}
	
	void Parser::add (std::string name, std::string rule)
	{
		std::vector<Rule> rs = parseRule (name, rule);
		
		for (Rule &r : rs)
			rules.push_back (r);
	}
	
	std::vector<Rule> Parser::getRuleByName (std::string name)
	{
		std::vector<Rule> out;
		for (unsigned int i = 0; i < rules.size (); i++)
		{
			if (rules[i].name == name)
			{
				out.push_back (rules[i]);
			}
		}
		
		return out;
	}
}
