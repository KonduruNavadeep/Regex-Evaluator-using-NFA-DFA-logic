# Diagrams

All diagrams are written in [Mermaid](https://mermaid.js.org/), which GitHub renders automatically.

## 1. Architecture Diagram

End-to-end pipeline, showing which component handles each stage (see `src/main.cpp`).

```mermaid
flowchart TD
    A["Input<br/>Regular Expression + String"] --> B["RegexParser<br/>parse()"]
    B --> C["Syntax Tree<br/>RegexNode hierarchy"]
    C --> D["NFABuilder<br/>Thompson's construction"]
    D --> E["NFA<br/>NFAFragment (start, end)"]
    E --> F["DFABuilder<br/>Subset construction"]
    E -. "optional check" .-> G["NFASimulator<br/>matches()"]
    F --> H["DFA<br/>DFAState graph"]
    H --> I["DFASimulator<br/>matches()"]
    I --> J{"Final state<br/>reached?"}
    J -- Yes --> K["ACCEPT"]
    J -- No --> L["REJECT"]

    O["NFAOperations<br/>epsilonClosure() / move()"] -.-> F
    O -.-> G
```

> `NFASimulator` is available for testing the NFA directly, but `main.cpp` runs the DFA path.

## 2. Class Diagram

```mermaid
classDiagram
    direction TB

    %% Syntax tree
    class RegexNode {
        <<abstract>>
        +evaluate() string*
        +~RegexNode()
    }
    class LiteralNode {
        -char value
        +LiteralNode(char value)
        +evaluate() string
    }
    class ConcatNode {
        -RegexNode* left
        -RegexNode* right
        +evaluate() string
        +getLeft() RegexNode*
        +getRight() RegexNode*
    }
    class UnionNode {
        -RegexNode* left
        -RegexNode* right
        +evaluate() string
        +getLeft() RegexNode*
        +getRight() RegexNode*
    }
    class StarNode {
        -RegexNode* child
        +evaluate() string
        +getChild() RegexNode*
    }
    RegexNode <|-- LiteralNode
    RegexNode <|-- ConcatNode
    RegexNode <|-- UnionNode
    RegexNode <|-- StarNode
    ConcatNode o-- RegexNode : left, right
    UnionNode o-- RegexNode : left, right
    StarNode o-- RegexNode : child

    %% Parser
    class RegexParser {
        -string regex
        -int pos
        +RegexParser(string regex)
        +parse() RegexNode*
        -parseExpression() RegexNode*
        -parseTerm() RegexNode*
        -parseFactor() RegexNode*
        -parsePrimary() RegexNode*
    }
    RegexParser ..> RegexNode : creates

    %% NFA
    class NFAState {
        +int id
        +bool isFinal
        +vector~pair~char, NFAState*~~ transitions
        +addTransition(char symbol, NFAState* dest)
    }
    class NFAFragment {
        +NFAState* start
        +NFAState* end
    }
    class NFABuilder {
        -int stateCount
        +build(RegexNode* node) NFAFragment
        -buildLiteral(RegexNode*) NFAFragment
        -buildConcat(RegexNode*) NFAFragment
        -buildUnion(RegexNode*) NFAFragment
        -buildStar(RegexNode*) NFAFragment
    }
    class NFAOperations {
        +epsilonClosure(states, closure)$ void
        +move(states, symbol)$ set~NFAState*~
    }
    class NFASimulator {
        +matches(NFAFragment, string input) bool
    }
    NFAFragment --> NFAState : start, end
    NFAState --> NFAState : transitions
    NFABuilder ..> RegexNode : reads
    NFABuilder ..> NFAFragment : returns
    NFASimulator ..> NFAFragment
    NFASimulator ..> NFAOperations

    %% DFA
    class DFAState {
        +int id
        +bool isFinal
        +set~NFAState*~ nfaStates
        +map~char, DFAState*~ transitions
    }
    class DFABuilder {
        -int stateCount
        +build(NFAFragment nfa) DFAState*
        -containsFinalState(set) bool
        -findState(states, nfaStates) DFAState*
    }
    class DFASimulator {
        +matches(DFAState* start, string input) bool
    }
    DFAState o-- NFAState : represents set of
    DFAState --> DFAState : transitions
    DFABuilder ..> NFAFragment : input
    DFABuilder ..> DFAState : returns start
    DFABuilder ..> NFAOperations
    DFASimulator ..> DFAState
```

## 3. Sequence Diagram (Program Flow)

```mermaid
sequenceDiagram
    actor User
    participant Main as main()
    participant P as RegexParser
    participant NB as NFABuilder
    participant DB as DFABuilder
    participant Ops as NFAOperations
    participant S as DFASimulator

    User->>Main: regex, input string
    Main->>P: parse()
    P-->>Main: RegexNode* root (syntax tree)
    Main->>NB: build(root)
    NB-->>Main: NFAFragment (start, end)
    Main->>DB: build(nfa)
    loop for each unmarked DFA state and symbol
        DB->>Ops: move(states, symbol)
        Ops-->>DB: next NFA states
        DB->>Ops: epsilonClosure(states)
        Ops-->>DB: closure
    end
    DB-->>Main: DFAState* start
    Main->>S: matches(start, input)
    S-->>Main: true / false
    Main-->>User: ACCEPT / REJECT
```

## 4. Parser Grammar

Operator precedence, lowest to highest: union, concatenation, star. Each rule matches a `RegexParser` method.

```mermaid
flowchart LR
    E["parseExpression<br/>Term ( '|' Term )*"] --> T["parseTerm<br/>Factor Factor*"]
    T --> F["parseFactor<br/>Primary '*'*"]
    F --> P["parsePrimary<br/>char | '(' Expression ')'"]
    P -. "parentheses" .-> E
```

## 5. Example Syntax Tree for `(a|b)*abb`

```mermaid
flowchart TD
    C1["Concat"] --> C2["Concat"]
    C1 --> B2["Literal b"]
    C2 --> C3["Concat"]
    C2 --> B1["Literal b"]
    C3 --> S["Star"]
    C3 --> A2["Literal a"]
    S --> U["Union"]
    U --> A1["Literal a"]
    U --> B0["Literal b"]
```

## 6. Thompson's Construction Patterns

`ε` marks an epsilon transition (stored as `'\0'` internally).

```mermaid
flowchart LR
    subgraph Literal["Literal a"]
        l1(("start")) -- a --> l2((("end")))
    end
    subgraph Concat["Concat AB"]
        c1(("start")) --> cA["NFA(A)"] -- ε --> cB["NFA(B)"] --> c2((("end")))
    end
    subgraph Union["Union A|B"]
        u1(("start")) -- ε --> uA["NFA(A)"] -- ε --> u2((("end")))
        u1 -- ε --> uB["NFA(B)"] -- ε --> u2
    end
    subgraph Star["Star A*"]
        s1(("start")) -- ε --> sA["NFA(A)"] -- ε --> s2((("end")))
        s1 -- ε --> s2
        sA -- "ε (loop back)" --> sA
    end
```

## 7. DFA for `(a|b)*abb`

The minimal equivalent DFA. The program's subset construction gives an equivalent automaton, possibly with extra states.

```mermaid
stateDiagram-v2
    direction LR
    [*] --> S0
    S0 --> S1: a
    S0 --> S0: b
    S1 --> S1: a
    S1 --> S2: b
    S2 --> S1: a
    S2 --> S3: b
    S3 --> S1: a
    S3 --> S0: b
    S3 --> [*]
```
