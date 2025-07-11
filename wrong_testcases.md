new:

3-4,6,8,10-11
basic: 5-9,12,14-16,19-27,29-34,36-37,39-40,42,45-47,50-52,54,58,64,67,70,

break: 1-2, 4-5,

builtin: 3-4

class: 8,10,12,14,16

expression: 1, 4-5

function: 1-3, 5-6

if: 1-3

loop: 1,3

misc: 15, 32

scope: 3-5

symbol: 2, 4

old: -basic39 +basic56


// after ast:
array: 1-2, 4-8, 10-11
basic: 1, 3, 5, 7-8, 10, 12, 14-16, 18, 22-23, 25-27, 29-31, 33-34, 37, 40, 45, 47, 49, 51-54, 56, 59-60, 64, 67, 71-72
breakcontinue: 3
builtin: 1-4
class: 1-3, 6, 8-12, 16
codeforces: all
expression: 1, 3-5
function: 2-3, 5-6
loop: 2-3
misc: 1-14, 16-31, 33-34, 36-37
scope: 1-2, 6-8
string: 1
symbol: 4
ternary: 1, 3-5

// after semantic
array: 1-2, 5, 7, 9
basic: 1-3, 10-11, 17-18, 28, 41, 44, 49, 53, 55-56, 59-60, 62-66, 69, 71-72
breakcontinue: 3
builtin: 1-2
class: 1-7, 9, 11, 13, 15
codeforces: all
expression: 2-3
function: 4
loop: 2
misc: 1-14, 16-31, 33-37
scope: 1-2, 6-8
string: 1
symbol: 1
ternary: 1, 3-5