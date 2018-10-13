# Summary of cppcon 2018
This document contains comments, notes and opinions about annual C++ conference that took place 23-29 September 2018.
All members of C++ User Group Krakow are encouraged to contribute through commenting interesting talks.
On the following meeting(s) we'll be discousing about it.

## Bjarne Stroustrup: "Concepts: The Future of Generic Programming (the future is here)"
"The future" has been becoming for years... It turns out that C++ concepts it's not brand new idea. The need of improving generic code with "compile time predicates" has been noticed and some approaches has been performed. Finally in 2016 TS containing concepts was approved and has been available in GCC since version 6 (-fconcepts) - no clang support yet. Currently, concepts are in working draft for C++20.

Concepts help develop better design, provide better specification interface, simplify code and give precise, early error messages.

[conference video](https://www.youtube.com/watch?v=HddFGPTAmtU&feature=youtu.be)

## Jussi Pakkanen: "Compiling Multi-Million Line C++ Code Bases Effortlessly with the Meson Build System"

[Meason](https://mesonbuild.com) is an open source, multiplatform build system for multiple languages. It's fast, lean and efficient. It's widely used by multiple open source projects - [see the list](http://mesonbuild.com/Users.html). The main idea is to use modern programming tools and best practises including unit testing, code coverage, procompiled headers, code generators, caching, templates and so on... All in one place.

[conference video](https://youtu.be/SCZLnopmYBM)

## Kate Gregory “Simplicity: Not Just For Beginners”

This speech is about good programming practises and it's aimed for all programmers. Some important thoughts from the presentation:
* "Programming is a social activity in which communication is a vital skill. The code you leave behind speaks". 
* General "rocket science" design forces maintenace complicated code that is "ready for all possible extending cases" that never happens
* "Simplicity paradox - the things you do to make code simple can make it more complex", "As simple as possible but no simpler!"
* Use idioms, libraries and commonality - don't re-invent the wheel
* "Action points: Learn, Read, Care, Test, Communicate" 

[conference video](https://youtu.be/n0Ak6xtVXno)

