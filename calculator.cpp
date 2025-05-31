#include "crow.h"
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "mswsock.lib")

class Calculator {
private:
    double memory = 0;
    
public:
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) { return b != 0 ? a / b : 0; }
    double power(double base, double exp) { return pow(base, exp); }
    double modulo(double a, double b) { return fmod(a, b); }
    
    double sine(double x) { return sin(x); }
    double cosine(double x) { return cos(x); }
    double tangent(double x) { return tan(x); }
    double squareRoot(double x) { return sqrt(x); }
    double naturalLog(double x) { return log(x); }
    double log10(double x) { return log10(x); }
    double exponential(double x) { return exp(x); }
    double factorial(int n) {
        if (n <= 1) return 1;
        double result = 1;
        for (int i = 2; i <= n; i++) result *= i;
        return result;
    }
    
    void memoryClear() { memory = 0; }
    void memoryStore(double value) { memory = value; }
    double memoryRecall() { return memory; }
    void memoryAdd(double value) { memory += value; }
    void memorySubtract(double value) { memory -= value; }
    
    long bitwiseAnd(long a, long b) { return a & b; }
    long bitwiseOr(long a, long b) { return a | b; }
    long bitwiseXor(long a, long b) { return a ^ b; }
    long bitwiseNot(long a) { return ~a; }
    
    std::string convertToBase(long num, int base) {
        if (num == 0) return "0";
        std::string chars = "0123456789ABCDEF";
        std::string result;
        bool negative = num < 0;
        if (negative) num = -num;
        
        while (num > 0) {
            result = chars[num % base] + result;
            num /= base;
        }
        
        if (negative) result = "-" + result;
        return result;
    }
};

Calculator calc;

std::string loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "<html><body><h1>Calculator</h1><p>Please place index.html in the same directory</p></body></html>";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    crow::SimpleApp app;

    // Serve the main HTML page
    app.route_dynamic("/")
        .methods("GET"_method)
        ([](const crow::request& req) {
            std::string html = loadFile("index.html");
            crow::response res{html};
            res.add_header("Content-Type", "text/html");
            res.add_header("Access-Control-Allow-Origin", "*");
            return res;
        });

    // Basic calculator operations
    app.route_dynamic("/calculate")
        .methods("GET"_method, "OPTIONS"_method)
        ([](const crow::request& req) {
            if (req.method == crow::HTTPMethod::OPTIONS) {
                crow::response res;
                res.add_header("Access-Control-Allow-Origin", "*");
                res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
                res.add_header("Access-Control-Allow-Headers", "Content-Type");
                res.code = 200;
                return res;
            }

            const char* num1_str = req.url_params.get("num1");
            const char* num2_str = req.url_params.get("num2");
            const char* op = req.url_params.get("op");

            std::cout << "Calculate request: num1=" << (num1_str ? num1_str : "null")
                      << ", num2=" << (num2_str ? num2_str : "null")
                      << ", op=" << (op ? op : "null") << std::endl;

            if (!num1_str || !num2_str || !op) {
                crow::json::wvalue error_json;
                error_json["error"] = "Missing required parameters (num1, num2, op)";
                crow::response res{error_json};
                res.add_header("Access-Control-Allow-Origin", "*");
                res.code = 400;
                return res;
            }

            double num1, num2;
            try {
                num1 = std::stod(num1_str);
                num2 = std::stod(num2_str);
            } catch (const std::invalid_argument&) {
                crow::json::wvalue error_json;
                error_json["error"] = "Invalid number format";
                crow::response res{error_json};
                res.add_header("Access-Control-Allow-Origin", "*");
                res.code = 400;
                return res;
            }

            std::string operation = op;
            double result = 0.0;
            std::string error_message = "";

            if (operation == "add") result = calc.add(num1, num2);
            else if (operation == "subtract") result = calc.subtract(num1, num2);
            else if (operation == "multiply") result = calc.multiply(num1, num2);
            else if (operation == "divide") {
                if (num2 != 0) result = calc.divide(num1, num2);
                else error_message = "Division by zero error";
            }
            else if (operation == "power") result = calc.power(num1, num2);
            else if (operation == "modulo") result = calc.modulo(num1, num2);
            else if (operation == "and") result = calc.bitwiseAnd((long)num1, (long)num2);
            else if (operation == "or") result = calc.bitwiseOr((long)num1, (long)num2);
            else if (operation == "xor") result = calc.bitwiseXor((long)num1, (long)num2);
            else error_message = "Invalid operation";

            crow::json::wvalue response_json;
            if (!error_message.empty()) {
                response_json["error"] = error_message;
            } else {
                response_json["result"] = result;
            }

            crow::response res{response_json};
            res.add_header("Access-Control-Allow-Origin", "*");
            res.code = error_message.empty() ? 200 : 400;
            return res;
        });

    // Scientific functions
    app.route_dynamic("/scientific")
        .methods("GET"_method, "OPTIONS"_method)
        ([](const crow::request& req) {
            if (req.method == crow::HTTPMethod::OPTIONS) {
                crow::response res;
                res.add_header("Access-Control-Allow-Origin", "*");
                res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
                res.add_header("Access-Control-Allow-Headers", "Content-Type");
                res.code = 200;
                return res;
            }

            const char* value_str = req.url_params.get("value");
            const char* func = req.url_params.get("func");

            std::cout << "Scientific request: value=" << (value_str ? value_str : "null")
                      << ", func=" << (func ? func : "null") << std::endl;

            if (!value_str || !func) {
                crow::json::wvalue error_json;
                error_json["error"] = "Missing required parameters (value, func)";
                crow::response res{error_json};
                res.add_header("Access-Control-Allow-Origin", "*");
                res.code = 400;
                return res;
            }

            double value;
            try {
                value = std::stod(value_str);
            } catch (const std::invalid_argument&) {
                crow::json::wvalue error_json;
                error_json["error"] = "Invalid number format";
                crow::response res{error_json};
                res.add_header("Access-Control-Allow-Origin", "*");
                res.code = 400;
                return res;
            }

            std::string function = func;
            double result = 0.0;
            std::string error_message = "";

            if (function == "sin") result = calc.sine(value);
            else if (function == "cos") result = calc.cosine(value);
            else if (function == "tan") result = calc.tangent(value);
            else if (function == "sqrt") result = calc.squareRoot(value);
            else if (function == "ln") result = calc.naturalLog(value);
            else if (function == "log") result = calc.log10(value);
            else if (function == "exp") result = calc.exponential(value);
            else if (function == "factorial") result = calc.factorial((int)value);
            else if (function == "not") result = calc.bitwiseNot((long)value);
            else error_message = "Invalid function";

            crow::json::wvalue response_json;
            if (!error_message.empty()) {
                response_json["error"] = error_message;
            } else {
                response_json["result"] = result;
            }

            crow::response res{response_json};
            res.add_header("Access-Control-Allow-Origin", "*");
            res.code = error_message.empty() ? 200 : 400;
            return res;
        });

    // Memory operations
    app.route_dynamic("/memory")
        .methods("GET"_method, "OPTIONS"_method)
        ([](const crow::request& req) {
            if (req.method == crow::HTTPMethod::OPTIONS) {
                crow::response res;
                res.add_header("Access-Control-Allow-Origin", "*");
                res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
                res.add_header("Access-Control-Allow-Headers", "Content-Type");
                res.code = 200;
                return res;
            }

            const char* op = req.url_params.get("op");
            const char* value_str = req.url_params.get("value");

            std::cout << "Memory request: op=" << (op ? op : "null")
                      << ", value=" << (value_str ? value_str : "null") << std::endl;

            if (!op) {
                crow::json::wvalue error_json;
                error_json["error"] = "Missing operation parameter";
                crow::response res{error_json};
                res.add_header("Access-Control-Allow-Origin", "*");
                res.code = 400;
                return res;
            }

            std::string operation = op;
            double value = 0;

            if (value_str) {
                try {
                    value = std::stod(value_str);
                } catch (const std::invalid_argument&) {
                    crow::json::wvalue error_json;
                    error_json["error"] = "Invalid number format";
                    crow::response res{error_json};
                    res.add_header("Access-Control-Allow-Origin", "*");
                    res.code = 400;
                    return res;
                }
            }

            if (operation == "clear") calc.memoryClear();
            else if (operation == "store") calc.memoryStore(value);
            else if (operation == "add") calc.memoryAdd(value);
            else if (operation == "subtract") calc.memorySubtract(value);

            crow::json::wvalue response_json;
            response_json["memory"] = calc.memoryRecall();

            crow::response res{response_json};
            res.add_header("Access-Control-Allow-Origin", "*");
            res.code = 200;
            return res;
        });

    // Base conversion
    app.route_dynamic("/convert")
        .methods("GET"_method, "OPTIONS"_method)
        ([](const crow::request& req) {
            if (req.method == crow::HTTPMethod::OPTIONS) {
                crow::response res;
                res.add_header("Access-Control-Allow-Origin", "*");
                res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
                res.add_header("Access-Control-Allow-Headers", "Content-Type");
                res.code = 200;
                return res;
            }

            const char* number_str = req.url_params.get("number");
            const char* base_str = req.url_params.get("base");

            if (!number_str || !base_str) {
                crow::json::wvalue error_json;
                error_json["error"] = "Missing required parameters (number, base)";
                crow::response res{error_json};
                res.add_header("Access-Control-Allow-Origin", "*");
                res.code = 400;
                return res;
            }

            long number;
            int base;
            try {
                number = (long)std::stod(number_str);
                base = std::stoi(base_str);
            } catch (const std::invalid_argument&) {
                crow::json::wvalue error_json;
                error_json["error"] = "Invalid number format";
                crow::response res{error_json};
                res.add_header("Access-Control-Allow-Origin", "*");
                res.code = 400;
                return res;
            }

            crow::json::wvalue response_json;
            response_json["result"] = calc.convertToBase(number, base);

            crow::response res{response_json};
            res.add_header("Access-Control-Allow-Origin", "*");
            res.code = 200;
            return res;
        });

    std::cout << "Calculator server starting on http://localhost:8080" << std::endl;
    app.port(8080).multithreaded().run();
    return 0;
}
