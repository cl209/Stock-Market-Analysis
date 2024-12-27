# Stock Market Analysis Tool

A C++ application that fetches and displays real-time stock market data using the Alpha Vantage API. This tool provides daily stock information including open, high, low, close prices, and trading volume for any specified stock symbol.

## Features

- Real-time stock data retrieval
- Daily time series data display
- Formatted output with date and volume formatting
- Error handling for API and JSON parsing
- SSL-verified secure connections

## Prerequisites

- C++ compiler with C++11 support or higher
- libcurl library
- nlohmann/json library
- Alpha Vantage API key

## Dependencies Installation

### Linux
```bash
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install nlohmann-json3-dev
```

### macOS
```bash
brew install curl
brew install nlohmann-json
```

### Windows
You can use vcpkg package manager:
```bash
vcpkg install curl:x64-windows
vcpkg install nlohmann-json:x64-windows
```

## Configuration

1. Obtain an API key from [Alpha Vantage](https://www.alphavantage.co/support/#api-key)
2. Replace the `apiKey` constant in the code with your API key:
```cpp
const string apiKey = "YOUR_API_KEY";
```

## Building the Project

```bash
g++ -o stock_analysis main.cpp -lcurl
```

## Usage

1. Set the stock symbol in the code:
```cpp
const string symbol = "NVDA"; // Replace with desired stock symbol
```

2. Run the compiled program:
```bash
./stock_analysis
```

## Output Format

The program outputs stock data in the following format:
```
Ticker: NVDA
Date: MM/DD/YYYY
Open: $X.XX
High: $X.XX
Low: $X.XX
Close: $X.XX
Volume: XXX,XXX
-------------------------
```

## Error Handling

The application includes comprehensive error handling for:
- CURL initialization and execution errors
- API response errors
- JSON parsing errors
- Data type conversion errors

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is available under the MIT License. See the LICENSE file for more details.

## Acknowledgments

- [Alpha Vantage API](https://www.alphavantage.co/) for providing stock market data
- [libcurl](https://curl.se/libcurl/) for HTTP requests
- [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing

## Contact

If you have any questions or suggestions, please open an issue in the repository.
