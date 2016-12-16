# Kestrel Compiler
## Group C

### Jones Instructions

From: http://thinkingeek.com/2013/01/09/arm-assembler-raspberry-pi-chapter-1/

0. Be on a raspberry pi in the repo, and execute the following:
1. make
2. ./kestrel /Testing/XDeclareTestFile.kestrel > test.s | as -o test.o test.s | gcc -o test test.o
3. ./test; echo $?

This




### Travis build status:
[![Build Status](https://travis-ci.org/ajjl/compiler.svg?branch=master)](https://travis-ci.org/ajjl/compiler)


## Contributors
###	kntsn - Dan Knutson, kntsn@uiowa.edu
###     hongxli - Hongxu Li, hongxu-li@uiowa.edu
###	aleinoff - Alexander Leinoff, alexander-leinoff@uiowa.edu
###	bziolko - Brad Ziolko, bradley-ziolko@uiowa.edu
###	xzhu16 - Xi Zhu, xi-zhu-1@uiowa.edu


## Github repo available at:
### https://github.com/ajjl/compiler

## Slack channel is:
### compiler-groupc.slack.com

## Building With CMake
CMake is a build environment generator. For larger projects it is easier than writing Makefiles by hand. We will try to have our Makefiles still work anyways. CMake also has good support for testing and building and linking to dependencies.

### You probably need to install cmake:
On linux: `sudo apt-get install cmake`
On mac, install with homebrew: `brew install cmake`

If you dont have homebrew, get it here: http://brew.sh/
On Windows: ???

### Git is also a pre-req
`sudo apt-get install git`

### Out of source build
CMake requires an "out of source" build. That means that the directory that the compiled objects land in is completely separate from the directory of the source files. Here are instructions for building with cmake. You can also build the narmal way with plain ol make.

### Instructions:
Parallel to the groupc directory (at the same level) make a new directory called "groupc-build" and then change into it.
`mkdir groupc-build`
`cd groupc-build`
Run cmake from the groupc-build filder, using the groupc directory as the argument.
`cmake ../groupc`
This generates the makefiles. Now just run make.
`make`
Now you can run your tests:
`ctest`
or 
`make test`

### You can also use cmake to build project files for many IDE's. Google it.

### yup, we now have some tests.

If you want to rebuild the project. Run `make clean` first.

### Do NOT add the build directory to svn or git
## Git-svn
This repo should update automatically with new svn commits. So you could just
commit on svn and see the results on github.

you might need to do apt-get git-svn or something.

Below is how you could setup your own git svn repo

Detailed info on git svn at: google it.

Basic git svn instrucitons -- works on mac (probably linux too)
you dont have to do this, you can just use svn if you want ...

1. Creating Repository
make a home for your new git svn repo on you computer:

"mkdir compilerStuff"
"cd compilerStuff"

use git svn to clone your repo:
"git svn clone https://svn.divms.uiowa.edu/repos/cs4980/groupc cs4980"

You now have a git-svn hybred repository!!

2. Go into your repository and check stuff out:
"cd cs4980"
"git log"
....

3. Add the github remote, and update the github repo:
"git remote add github https://github.com/ajjl/compiler"
"git fetch github"

4. Make a change and commit it:
"echo 'something' >> groupc/testFile"

You need to commit in git first, then svn <------IMPORTANT
"git add groupc/testFile"
"git commit -m"Testing stuff"
"git svn rebase"
"git svn dcommit"

4a. "git add" and "git commit" do the same thing that you'd expect.
4b. "git svn rebase" fetches the svn remote, then replays your changes on top of it.
4c. "git svn dcommit" pushes your recent git commits on to the svn repo. It will delete any git authorship information and look like it was authored only by whoever is now committing on svn

5. The master branch of the repo will update with the svn of our group
every 5 minutes

6. Every time a new commit or branch is pushed, a build starts on our continuous integration server:
https://travis-ci.org/ajjl/compiler

7. Put up a slack message with your github account. I'll git you write access, and then you push any branches you want. This will prove that your changes work on a standard linux system. The "master" and "jones" branches are locked. "master" is the current state of our svn folder. "jones" is the current state of the professors svn folder.

8. Notes:
you need to make your commits on svn yourself or the author wont show up.


## Contribution Guide
I think It'd be cool to use a feature/branch workflow. Svn branches are complicated, but we can just use git branches, and then instead of merging with git when they are ready, we'll commit with git svn.

#### example:
1. In your git-svn repo checkout a new branch with git

"git checkout -b myNewBranchThatIsCool"

2. Make your changes than commit them
"echo 'somethingNew' >> myNewFile"
"git add myNewFile"
"git commit -m'commiting my new file'"

3. Push the new branch to the remote (github)
"git push github myNewBranchThatIsCool"

4. Wait for it to pass the tests
...
...
...

5. Make a pull request so we can see what you did, and/or help you fix whats wrong.

6. When it's ready then, push to the svn:
"git svn rebase"
"git svn dcommit"

7. Checkout the master branch and update it, and delete the old branch:
"git checkout master"
"git svn rebase"
"git branch -D myNewBranchThatIsCool"

