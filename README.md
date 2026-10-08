# Regular Expression Evaluator using NFA-DFA Logic

## Overview

This project implements a lightweight Regular Expression (Regex) Evaluator in C++.

The evaluator accepts a regular expression and an input string, converts the regular expression into a syntax tree, constructs an NFA using Thompson's construction, converts the NFA into a DFA using subset construction, and finally uses the DFA to determine whether the input string is accepted or rejected.

## Features

* Regular expression parsing
* Syntax tree construction
* Literal expressions
* Concatenation
* Union (`|`)
* Kleene star (`*`)
* Thompson NFA construction
* NFA simulation
* NFA to DFA conversion
* DFA simulation
* Accept/Reject result

## Supported Regex Operators

| Operator      | Meaning                  | Example |     |    |
| ------------- | ------------------------ | ------- | --- | -- |
| `             | `                        | Union   | `a  | b` |
| `*`           | Zero or more occurrences | `a*`    |     |    |
| `()`          | Grouping                 | `(a     | b)` |    |
| Concatenation | Sequence of expressions  | `ab`    |     |    |

## Project Architecture

```text
Regular Expression
        |
        v
   Regex Parser
        |
        v
    Syntax Tree
        |
        v
   NFA Builder
        |
        v
       NFA
        |
        v
  NFA Simulation
        |
        v
   DFA Builder
        |
        v
       DFA
        |
        v
  DFA Simulation
        |
        v
   ACCEPT / REJECT
```

## Class Structure

```text
RegexNode
|
|-- LiteralNode
|-- ConcatNode
|-- UnionNode
|-- StarNode

NFAState
NFAFragment
NFABuilder
NFAOperations
NFASimulator

DFAState
DFABuilder
DFASimulator

RegexParser
```

## OOP Concepts Used

### Abstraction

`RegexNode` is an abstract base class containing the virtual `evaluate()` function.

### Inheritance

The following classes inherit from `RegexNode`:

* `LiteralNode`
* `ConcatNode`
* `UnionNode`
* `StarNode`

### Polymorphism

The `evaluate()` function is overridden by the derived node classes and can be accessed through the base class pointer.

### Encapsulation

Class data such as node values, child nodes, state information, and transitions are kept inside their respective classes.

## NFA Construction

The project uses Thompson's construction to build an NFA.

For example, a literal:

```text
Start ----a----> Final
```

For union:

```text
          EPSILON --> NFA(a) --EPSILON-->
Start
          EPSILON --> NFA(b) --EPSILON-->
```

For Kleene star:

```text
             EPSILON
          +-----------> Final
          |
Start ----+
          |
          +--> Child NFA --EPSILON--> Start path
```

`EPSILON` transitions are represented internally using the null character (`'\0'`).

## NFA Simulation

NFA simulation uses two important operations:

* Epsilon closure
* Move

The simulator begins with the epsilon closure of the NFA start state and processes the input character by character.

## NFA to DFA Conversion

The project uses subset construction.

A DFA state represents a set of NFA states.

For each DFA state and input symbol:

```text
Current NFA State Set
        |
        v
      move()
        |
        v
   epsilon closure
        |
        v
 Next NFA State Set
        |
        v
 Next DFA State
```

A DFA state is marked as final if it contains at least one final NFA state.

## DFA Simulation

The DFA simulator starts from the DFA start state and follows one transition for each input character.

After the complete input is processed:

* If the current DFA state is final → `ACCEPT`
* Otherwise → `REJECT`

## Example

Input:

```text
Regular Expression: (a|b)*abb
String: abababb
```

Output:

```text
Result: ACCEPT
```

Another example:

```text
Regular Expression: (a|b)*abb
String: abc
```

Output:

```text
Result: REJECT
```

## Project Structure

```text
RegexProject
|
|-- include
|   |-- RegexNode.h
|   |-- LiteralNode.h
|   |-- ConcatNode.h
|   |-- UnionNode.h
|   |-- StarNode.h
|   |-- RegexParser.h
|   |-- NFAState.h
|   |-- NFAFragment.h
|   |-- NFABuilder.h
|   |-- NFAOperations.h
|   |-- NFASimulator.h
|   |-- DFAState.h
|   |-- DFABuilder.h
|   |-- DFASimulator.h
|
|-- src
|   |-- main.cpp
|   |-- LiteralNode.cpp
|   |-- ConcatNode.cpp
|   |-- UnionNode.cpp
|   |-- StarNode.cpp
|   |-- RegexParser.cpp
|   |-- NFAState.cpp
|   |-- NFAFragment.cpp
|   |-- NFABuilder.cpp
|   |-- NFAOperations.cpp
|   |-- NFASimulator.cpp
|   |-- DFAState.cpp
|   |-- DFABuilder.cpp
|   |-- DFASimulator.cpp
|
|-- .gitignore
|-- README.md
```

## How to Run

Compile all source files using a C++ compiler.

Example:

```powershell
g++ -Iinclude src/*.cpp -o src/a.exe
```

Run:

```powershell
src/a.exe
```

The program will ask for:

```text
Enter Regular Expression:
Enter String:
```

It will then display:

```text
Result: ACCEPT
```

or:

```text
Result: REJECT
```

## Testing

The evaluator was tested with the following regular expressions and input strings.

**1. Literal matching**

```text
Regex: a
Input: a
Result: ACCEPT
```

```text
Regex: a
Input: b
Result: REJECT
```

**2. Union operator**

```text
Regex: a|b
Input: b
Result: ACCEPT
```

**3. Kleene star**

```text
Regex: a*
Input: aaa
Result: ACCEPT
```

**4. Complex regular expressions**

```text
Regex: (a|b)*abb
Input: abb
Result: ACCEPT
```

```text
Regex: (a|b)*abb
Input: aabb
Result: ACCEPT
```

```text
Regex: (a|b)*abb
Input: ababb
Result: ACCEPT
```

```text
Regex: (a|b)*abb
Input: abababb
Result: ACCEPT
```

```text
Regex: (a|b)*abb
Input: ab
Result: REJECT
```

```text
Regex: (a|b)*abb
Input: abc
Result: REJECT
```

## Automated Testing

The project includes a PowerShell script (`tests.ps1`) that automatically compiles the Regex Evaluator and runs 21 test cases covering valid expressions, invalid syntax, and edge cases.

### Run the Tests

Open PowerShell in the project root directory and execute:

```powershell
.\tests.ps1
```

If PowerShell blocks script execution, allow scripts for the current terminal session:

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\tests.ps1
```

The test runner displays the result of each test and a final summary containing the total number of tests passed and failed.

A successful run should report:

```text
Total:  21
Passed: 21
Failed: 0
```

The expected results above reflect the current test suite. Actual results may vary if the implementation or tests change.

## Technologies Used

* C++
* Object-Oriented Programming
* Standard Template Library (STL)
* Regular Expressions
* NFA
* DFA
* Thompson's Construction
* Subset Construction

## Conclusion

This project demonstrates how a regular expression can be processed from a high-level representation into a finite automaton.

The implementation combines parsing, object-oriented design, NFA construction, NFA simulation, DFA conversion, and DFA simulation to create a complete lightweight Regex evaluation pipeline.
