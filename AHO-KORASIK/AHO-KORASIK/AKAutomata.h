//
//  AKAutomata.h
//  AHO-KORASIK
//
//  Created by Alexander Malyshev on 13.11.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef AKAutomata_h
#define AKAutomata_h


class AKAutomata {
public:
    AKAutomata();
    unsigned long long GetLetterId(char c);
    unsigned long long GetAlphabetSize();
    
private:
    unsigned long long alphabetSize_;
    std::unordered_map<char, unsigned long long> lettersCodes_;
};


#endif /* AKAutomata_h */
