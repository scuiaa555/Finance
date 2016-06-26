# Finance
Financial Engineering

This repo is for my own practise using C++.

Instruction to link Quantlib with Xcode projects: 1. Target Project-> Build Settings-> Search Paths-> Header Search Paths-> /opt/local/include 2. Target Project-> Build Settings-> Search Paths-> Library Search Paths-> /opt/local/lib 3. Target Project-> Build Phases-> Link Binary With Library-> + -> libQuantLib.0.dylib (path:"/opt/local/lib") 4. Target Project-> Build Settings-> Apple LLVM 7.1-Language- C++-> C++ Language Dialect -> GNU++98[-std=gnu++98]

Instruction on incorporating github for source control 1. New a repo in github, say "Finance" 2. Create a new project in Xcode using the same name "Finance" for consistency. 3. In Terminal, open the "Finance" folder and intial the git file by git init 4. Link the local folder to the github website git remote add origin https://github.com/scuiaa555/Finance.git 5. Grad the initial files on the github website git pull origin master git add * git commit -m "Grab README" 6. Add the files in local folder to the website git add Finance Finance.xcodeproj/ git commit -m "add project files to master" 7. Push to the server by using Xcode source control button Xcode-> Source Control-> Push Done. :)
