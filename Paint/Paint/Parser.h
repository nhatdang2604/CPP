#pragma once
#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include <string>
#include <fstream>

#include "Tokenizer.h"
#include "Line.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Square.h"
#include "Circle.h"
#include "Figure.h"

class Parser {
public:
	static std::shared_ptr<figure::Figure> parse(std::string& buffer, std::string needle = ": ") {
		std::vector<std::string> tokens = Tokenizer::split(buffer, needle);
		try {
			if ("Line" == tokens[0]) return figure::Line::parse(tokens[1]);
			if ("Rectangle" == tokens[0]) return figure::Rectangle::parse(tokens[1]);
			if ("Ellipse" == tokens[0]) return figure::Ellipse::parse(tokens[1]);
			if ("Square" == tokens[0]) return figure::Square::parse(tokens[1]);
			if ("Circle" == tokens[0]) return figure::Circle::parse(tokens[1]);
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		return nullptr;
	};
	static std::vector<std::shared_ptr<figure::Figure>> readFigure(const std::string& input) {
		std::ifstream device(input);
		std::string buffer;
		std::vector<std::shared_ptr<figure::Figure>> result;
		try {
			while (!device.eof()) {
				getline(device, buffer);
				std::shared_ptr<figure::Figure> figure = parse(buffer);
				if (figure) {
					result.push_back(figure);
				}
			}

			device.close();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		return result;
	};
};

#endif // !_PARSER_H_





