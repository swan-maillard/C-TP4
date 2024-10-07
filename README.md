# Log Request Extractor and Link Analyzer

## Description

This project aims to facilitate the analysis of log files by extracting requests and visualizing the links between different web pages. It allows users to better understand their visitors' behavior and optimize their site based on the results.

## Log File Format

For the application to function correctly, each line of the log file must adhere to the following format:

```
ADRESS_IP USER_LOGNAME AUTHENTICATED_USER [D/M/Y:H:M:S TIMEZONE] "GET URL_TARGET HTTP_PROTOCOL" STATUS_CODE RESPONSE_SIZE "URL_REFERER" "USER_AGENT"
```

### Example:

```
192.168.0.0 - - [10/Feb/2023:10:14:31 +0200] "GET /page1.html HTTP/1.1" 200 666 "www.google.fr" "Mozilla/5.0 (Windows NT 6.3; Trident/7.0; rv:11.0) like Gecko"
```

Lines that do not conform to this format will not be considered by the application.

## Configuration File

A file named *config* must be present at the root of the project. It allows defining a local address to ignore during URL analysis. The format should be:

```
BASE_URL=LocalAddress
```

### Example content of the `config` file:

```
BASE_URL=http://intranet-if.insa-lyon.fr/
```

## Compilation Instructions

To compile the project, use the provided Makefile in the directory. The available commands are as follows:

- **`make`**: Compiles the project and links it.
- **`make dev`**: Compiles the project in development mode.
- **`make fclean`**: Removes object files and the executable.
- **`make help`**: Displays information about available commands.

## Application Usage

To run the application, use the following command:

```
./analog [options] filename.log
```

### Default Functionality:

Without options, the application extracts requests from the specified file (e.g., `myfile.log`) and displays the top 10 most visited pages in descending order on the console. No `.dot` file generation occurs.

### Available Options:

- **`-g filename.dot`**:
  - Generates a GraphViz formatted file named `filename.dot`, representing a graph of links between the different pages.

- **`-e`**:
  - Excludes requests corresponding to static resources such as images, CSS files, and JavaScript.
  - Supported extensions are: **jpg, jpeg, png, gif, svg, webp, bmp, ico, js, css** (case insensitive).

- **`-t hour`**:
  - Filters requests to retain only those within a specified one-hour interval (e.g., `[ hour ; hour+1 [ `).
  - The hour must be an integer between **0 and 24**. Otherwise, an error will be displayed.

## Tests

It is important to perform regular tests to ensure that new modifications do not affect the application's functionality.

### How to Run Tests:

1. Navigate to the **`tests/`** directory.
2. Execute the following command:

```
./mktest.sh
```

## Authors

- Swan Maillard (maillard.swan@gmail.com)
- Sarah Malard (sarah.malard@insa-lyon.fr)

## License

This project is licensed under the MIT License. Please refer to the `LICENSE` file for more information.
