# Advanced Calculator - Full-Stack Implementation

A comprehensive calculator application featuring Basic, Scientific, and Programmer modes with C++ backend and modern web frontend.

![Calculator Demo](https://img.shields.io/badge/.shields.io/badge

### 📱 Basic Calculator
- Standard arithmetic operations (+, -, ×, ÷)
- Memory functions (MC, MR, MS, M+, M-)
- Clear and backspace functionality
- Decimal point support

### 🔬 Scientific Calculator
- **Trigonometric Functions**: sin, cos, tan, asin, acos, atan
- **Logarithmic Functions**: ln, log, exp, power (x^y)
- **Mathematical Constants**: π (pi), e (Euler's number)
- **Advanced Operations**: factorial, square root, reciprocal, absolute value
- **Utility Functions**: random number generator, sign toggle
- **6-column responsive layout** for comprehensive function coverage

### 💻 Programmer Calculator
- **Number Base Support**: Binary, Octal, Decimal, Hexadecimal
- **Hex Digit Input**: A, B, C, D, E, F buttons
- **Bitwise Operations**: AND, OR, XOR, NOT
- **Bit Shift Operations**: Left Shift (LSH), Right Shift (RSH)
- **Real-time Base Conversion Display**
- **Smart Button Management**: Auto-enable/disable based on current base

## 🛠 Tech Stack

### Backend
- **Language**: C++17
- **Framework**: Crow (Lightweight HTTP framework)
- **Architecture**: RESTful API design
- **Threading**: Multi-threaded server support

### Frontend
- **Languages**: HTML5, CSS3, JavaScript (ES6+)
- **Design**: Responsive, glassmorphism UI
- **Features**: Dynamic mode switching, keyboard support

## 📁 Project Structure

```
calculator/
├── calculator.cpp          # C++ backend server
├── index.html             # Frontend interface
├── README.md              # This file
└── static/               # Static assets (if needed)
```

## 🔧 Installation & Setup

### Prerequisites
- **C++ Compiler**: GCC/MinGW with C++17 support
- **Crow Framework**: Download from [Crow GitHub](https://github.com/CrowCpp/Crow)
- **Windows**: ws2_32 library for socket support

### Build Instructions

1. **Clone/Download the project**
   ```bash
   git clone 
   cd calculator
   ```

2. **Install Crow Framework**
   ```bash
   # Download Crow headers to your system
   # Update the include path in calculator.cpp accordingly
   ```

3. **Compile the Backend**
   ```bash
   # For Windows with MinGW
   g++ calculator.cpp -o calculator -I"path/to/crow/include" -pthread -DCROW_MAIN -lws2_32

   # For Linux
   g++ calculator.cpp -o calculator -I"path/to/crow/include" -pthread -DCROW_MAIN
   ```

4. **Run the Server**
   ```bash
   ./calculator
   # Server starts on http://localhost:8080
   ```

5. **Access the Calculator**
   - Open your web browser
   - Navigate to `http://localhost:8080`
   - Enjoy calculating! 🎉

## 🌐 API Endpoints

### Basic Operations
```
GET /calculate?num1={value}&num2={value}&op={operation}
```
**Operations**: `add`, `subtract`, `multiply`, `divide`, `power`, `modulo`, `and`, `or`, `xor`

### Scientific Functions
```
GET /scientific?value={number}&func={function}
```
**Functions**: `sin`, `cos`, `tan`, `ln`, `log`, `exp`, `sqrt`, `factorial`, `not`

### Memory Operations
```
GET /memory?op={operation}&value={number}
```
**Operations**: `clear`, `store`, `add`, `subtract`, `recall`

### Base Conversion
```
GET /convert?number={value}&base={base}
```
**Bases**: `2` (binary), `8` (octal), `10` (decimal), `16` (hexadecimal)

## ⌨️ Keyboard Shortcuts

| Key | Action |
|-----|--------|
| `0-9` | Number input |
| `+`, `-`, `*`, `/` | Basic operations |
| `Enter` or `=` | Calculate |
| `Escape` or `C` | Clear |
| `Backspace` | Delete last digit |
| `.` | Decimal point |
| `A-F` | Hex digits (Programmer mode) |

## 🎨 UI Features

- **Glassmorphism Design**: Modern, translucent interface
- **Color-Coded Buttons**: 
  - 🟠 Orange: Operators
  - 🔵 Blue: Functions
  - 🔴 Red: Clear operations
  - 🟢 Green: Equals
  - 🟣 Purple: Hex digits
  - 🟡 Yellow: Bitwise operations
- **Responsive Layout**: Adapts to different screen sizes
- **Mode-Specific Layouts**: Each mode has optimized button arrangement

## 🔍 Technical Highlights

### Backend Architecture
- **Multi-threaded Server**: Handles concurrent requests efficiently
- **CORS Support**: Enables cross-origin requests
- **Error Handling**: Comprehensive validation and error responses
- **Memory Management**: Efficient resource utilization

### Frontend Features
- **Dynamic UI**: Real-time mode switching without page reload
- **State Management**: Maintains calculation state across operations
- **Input Validation**: Prevents invalid operations based on current mode
- **Visual Feedback**: Button states and hover effects

## 🐛 Troubleshooting

### Common Issues

1. **Compilation Errors**
   ```bash
   # Missing Crow headers
   fatal error: crow.h: No such file or directory
   ```
   **Solution**: Update the include path to your Crow installation

2. **Linking Errors (Windows)**
   ```bash
   # Undefined reference to WSAStartup
   ```
   **Solution**: Add `-lws2_32` to compilation command

3. **Server Won't Start**
   ```bash
   # Port already in use
   ```
   **Solution**: Change port in `calculator.cpp` or kill existing process

### Performance Tips
- Use latest C++ compiler for optimal performance
- Ensure sufficient system memory for multi-threading
- Close unnecessary browser tabs to free resources

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/amazing-feature`
3. **Commit changes**: `git commit -m 'Add amazing feature'`
4. **Push to branch**: `git push origin feature/amazing-feature`
5. **Open a Pull Request**

### Areas for Improvement
- [ ] Add parentheses support for complex expressions
- [ ] Implement calculation history
- [ ] Add more scientific functions (hyperbolic, statistical)
- [ ] Create mobile app version
- [ ] Add unit tests
- [ ] Implement expression parser for natural input


## 👨‍💻 Author
**Arkaprabha Banerjee**

## 🙏 Acknowledgments

- [Crow Framework](https://github.com/CrowCpp/Crow) for the excellent HTTP framework
- Mac Calculator for UI/UX inspiration
- Open source community for continuous learning

## 📊 Project Stats

- **Lines of Code**: ~800 (C++) + ~600 (HTML/CSS/JS)
- **API Endpoints**: 4 main endpoints with multiple operations
- **Calculator Modes**: 3 (Basic, Scientific, Programmer)
- **Supported Operations**: 25+ mathematical and logical operations
- **Browser Compatibility**: Chrome, Firefox, Safari, Edge

---

⭐ **Star this repository if you found it helpful!** ⭐

*Built with ❤️ and lots of ☕*

---
