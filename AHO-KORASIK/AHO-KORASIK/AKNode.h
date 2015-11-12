//
//  AKNode.h
//  AHO-KORASIK
//
//  Created by Alexander Malyshev on 13.11.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef AKNode_h
#define AKNode_h

class AKNode {
public:
    AKNode(AhoAutomata& automata, long long id, long long parentId, IAhoAutomataConfig& config, char symbol = '\0',
                 long long stringId = NO_NODE);
    long long GetChildId(char c);
    long long GetId();
    char GetSymbol();
    bool IsString();
    std::vector<long long>& GetStrings();
    long long GetTransition(char c);
    long long GetSuffixLinkId();
    long long GetFastLinkId();
    long long GetParentId();
    void SetSuffixLinkId(long long id);
    void SetFastLinkId(long long id);
    void SetTransition(char c, long long transition);
    void AddChild(char c, long long childId);
    void MarkAsString(long long stringId);
private:
    long long id_;
    char symbol_;
    long long parentId_;
    long long suffix_;
    std::vector<long long> childs_;
    std::vector<long long> transitions_;
    std::vector<long long> string_;
    long long fastSuffix_;
    IAhoAutomataConfig& config_;
    AhoAutomata& automata_;
};

#endif /* AKNode_h */
