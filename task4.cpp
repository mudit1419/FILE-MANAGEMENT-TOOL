#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Parser {
public:
    explicit Parser(const std::string& expr) : input(expr), pos(0) {}

    double parse() {
        double result = expression();
        if (pos < input.size()) {
            throw std::runtime_error("Unexpected character: " + std::string(1, input[pos]));
        }
        return result;
    }

private:
    std::string input;
    size_t pos;

    void skipWhitespace() {
        while (pos < input.size() && isspace(input[pos])) ++pos;
    }

    double number() {
        skipWhitespace();
        double result = 0;
        bool hasDecimal = false;
        double decimalFactor = 0.1;

        if (pos < input.size() && (isdigit(input[pos]) || input[pos] == '.')) {
            while (pos < input.size() && (isdigit(input[pos]) || input[pos] == '.')) {
                if (input[pos] == '.') {
                    if (hasDecimal) throw std::runtime_error("Multiple decimals in number");
                    hasDecimal = true;
                    ++pos;
                } else {
                    if (hasDecimal) {
                        result += (input[pos] - '0') * decimalFactor;
                        decimalFactor *= 0.1;
                    } else {
                        result = result * 10 + (input[pos] - '0');
                    }
                    ++pos;
                }
            }
            return result;
        }

        throw std::runtime_error("Expected number at position " + std::to_string(pos));
    }

    double factor() {
        skipWhitespace();
        if (pos < input.size() && input[pos] == '(') {
            ++pos;  // consume '('
            double result = expression();
            skipWhitespace();
            if (pos >= input.size() || input[pos] != ')') {
                throw std::runtime_error("Expected ')'");
            }
            ++pos;  // consume ')'
            return result;
        } else {
            return number();
        }
    }

    double term() {
        double result = factor();
        skipWhitespace();
        while (pos < input.size()) {
            char op = input[pos];
            if (op == '*' || op == '/') {
                ++pos;
                double rhs = factor();
                if (op == '*') result *= rhs;
                else {
                    if (rhs == 0) throw std::runtime_error("Division by zero");
                    result /= rhs;
                }
            } else {
                break;
            }
            skipWhitespace();
        }
        return result;
    }

    double expression() {
        double result = term();
        skipWhitespace();
        while (pos < input.size()) {
            char op = input[pos];
            if (op == '+' || op == '-') {
                ++pos;
                double rhs = term();
                if (op == '+') result += rhs;
                else result -= rhs;
            } else {
                break;
            }
            skipWhitespace();
        }
        return result;
    }
};

int main() {
    std::string input;

    std::cout << "Simple Arithmetic Expression Evaluator (type 'exit' to quit)\n";
    while (true) {
        std::cout << "\nEnter expression: ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        try {
            Parser parser(input);
            double result = parser.parse();
            std::cout << "Result: " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
