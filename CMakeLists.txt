cmake_minimum_required(VERSION 3.20)
project(project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h PeriodAutomaton.h PeriodAutomaton.cpp QuestionMarkAutomaton.cpp QuestionMarkAutomaton.h LeftParenAutomaton.cpp LeftParenAutomaton.h RightParenAutomaton.cpp RightParenAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.cpp AddAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h UndefinedAutomaton.cpp UndefinedAutomaton.h LineCommentAutomaton.cpp LineCommentAutomaton.h EndOfFileAutomaton.cpp EndOfFileAutomaton.h IDAutomaton.cpp IDAutomaton.h BlockCommentAutomaton.cpp BlockCommentAutomaton.h StringAutomaton.cpp StringAutomaton.h UDStringAutomaton.cpp UDStringAutomaton.h UDBlockCommentAutomaton.cpp UDBlockCommentAutomaton.h Parser.cpp Parser.h Schemes.cpp Schemes.h)
