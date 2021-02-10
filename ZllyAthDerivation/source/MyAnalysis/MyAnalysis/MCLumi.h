//
// MCLumi: class to return nevts / filter efficiency / xsection / equivalent lumi
//         for photon MC samples, starting from information stored in txt file via getAMI5xsec.pl
//         script (for background) or from CERN yellow report for signal
//
// Usage: .L MCLumi.C+ (or link your code against MCLumi)
//        MClumi foo("mc11a_lumi_p756.txt");
//        unsigned int mc_channel_number = 116870;
//        double gen_xsec = foo.getXsec(sample);
//        double filter_eff = foo.getFEff(sample);
//        ...
//

#ifndef MCLumi_h
#define MCLumi_h

#include <utility>
#include <string>
#include <vector>

using namespace std;

class MCLumi {

public: 
    MCLumi(std::string filename);

    void listSamples();
    bool containsSample(unsigned int mc_channel_number);
    double getXsec(unsigned int mc_channel_number); // returns sample xsec in pb (from AMI or from better calculation if available)
    double getFEff(unsigned int mc_channel_number); // returns filter efficiency from AMI
    
private:
    std::vector< unsigned int > samples;
    std::vector< std::pair<unsigned int,double> > xsecs;
    std::vector< std::pair<unsigned int,double> > effs;
};


#endif
