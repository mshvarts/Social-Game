# About
An engaging social game created for SFU's CMPT 373 class in a team of seven members.   
It uses web sockets to connect the front-end chatbox with the C++ backend code.   
Currently supports playing the game Rock Paper Scissors.

# Social Gaming

Team Francesinha Social Gaming Project
Members:

- Max Shvartsman
- John
- Kirat
- Camilo
- Eric
- Lang
- Dylan

## Dependencies

This project requires:

1. C++17 or newer
2. Boost >= 1.66
3. CMake >= 3.12
4. nlohmann_json >= 3.2.0 (https://github.com/nlohmann/json)

## Building with CMake

1.  Clone the repository.

        git clone https://csil-git1.cs.surrey.sfu.ca/373-20-1-francesinha/social-gaming.git

2.  Create a new directory for building.

        mkdir build

3.  Change into the new directory.

        cd build

4.  Run CMake with the path to the source.

        cmake ../social-gaming/

5.  Run make inside the build directory:

        make

## Running the Example Social Game Client and Social Game Server

First run the Social Game server on an unused port of the server machine. The server
also takes an HTML file that it will server to standard http requests for
`index.html`.

    bin/gameserver 4000 ../social-gaming/webgame.html

A browser based interface can be accessed by opening the URL
`http://localhost:4000/index.html`. The server will respond with the
specified web page above. By clicking `Connect`, the page gains access to the
Social Game on the server via web sockets in browsers that support web sockets.
