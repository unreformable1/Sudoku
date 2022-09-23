![Alt text](/assets/screenshoots/sudoku_example.png)

# Sudoku
Classic sudoku puzzle using SFML.

## Key Features

* Having fun solving sudoku puzzles!
* Having fun solving sudoku puzzles!
* And having fun solving sudoku puzzles!

## Installation

- Clone this repository by ```git clone https://github.com/unreformable1/Sudoku.git```  
- Use script depending on OS:  
Linux/macOS: `bash build.sh`  
Windows: `build.bat`

## Launching the program

```
cd build  
./sudoku
```

## Installation of testing framework

Note: There is only one unit test as example if you would like to extend it by pull request or after forking.  
Linux:
```
mkdir tmp
cd tmp
git clone git@github.com:catchorg/Catch2.git
cd Catch2
cmake -Bbuild -H. -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install
cd ..
cd ..
rm -r tmp
```

## Dependencies required

* CMake 3.0.0
* SFML 2.5.1

## Q&A

Q: Why the functionality of the board is split into `SudokuBoard`, `SudokuBoardView` and `SudokuBoardController` classes?  
A: After the first attempt of creating one superclass for sudoku board where game logic was mixed with rendering
I decided to seperate `Model` from `View` and add a `Controller` to manage them. This software architectural pattern is known as `Model-View-Controller` (MVC) and was traditionally used for desktop graphical user interfaces (GUIs). Here is [link](https://www.guru99.com/mvc-tutorial.html) if you want to know more :)

## Contributing

Pull requests are welcomed. For major changes please open an issue first to discuss what you would like to change.

## License

[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)