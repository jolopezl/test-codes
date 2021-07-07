
#include <iostream>
#include <array>
#include <deque>
#include <unordered_map>
#include <vector>

#define MAXCHAMBER 8
#define TIMEBINS 30
#define READOUT_TIME 3000

struct SignalArray {
    double firstTBtime;                    // first TB time
    std::array<float, TIMEBINS> signals{}; // signals
    std::unordered_map<int, int> trackIds; // tracks Ids associated to the signal
    std::vector<int> labels;               // labels associated to the signal
    bool isDigit = false;                  // flag a signal converted to a digit
    bool isShared = false;                 // flag if converted digit is shared (copied)
                                           // if that is the case, also the labels have to be copied
};

using SignalContainer = std::unordered_map<int, SignalArray>;

class Digitizer
{
   public:
    std::deque<std::array<SignalContainer, MAXCHAMBER>> mPileupSignals;
    float mCurrentTriggerTime;
    SignalContainer addSignalsFromPileup();
};

SignalContainer Digitizer::addSignalsFromPileup()
{
    SignalContainer addedSignalsMap;
    int nSignalsToRemove = 0;
    for (const auto& collection : mPileupSignals) {
        bool pileupSignalBecomesObsolete = false;
        for (int det = 0; det < MAXCHAMBER; ++det) {
            const auto& signalMap = collection[det]; //--> a map with active pads only for this chamber
            for (const auto& signal : signalMap) {   // loop over active pads only, if there is any
                const int& key = signal.first;
                const SignalArray& signalArray = signal.second;
                // check if the signal is from a previous event
                if (signalArray.firstTBtime < mCurrentTriggerTime) {
                    pileupSignalBecomesObsolete = true;
                    if ((mCurrentTriggerTime - signalArray.firstTBtime) > READOUT_TIME) { // OS: READOUT_TIME should actually be drift time (we want to ignore signals which don't contribute signal anymore at mCurrentTriggerTime)
                        continue;                                                         // ignore the signal if it  is too old.
                    }
                    // add only what's leftover from this signal
                    // 0.01 = samplingRate/1000, 1/1000 to go from ns to micro-s, the sampling rate is in 1/micro-s
                    int idx = (int)((mCurrentTriggerTime - signalArray.firstTBtime) * 0.01); // number of bins to add, from the tail
                    auto it0 = signalArray.signals.begin() + idx;
                    auto it1 = addedSignalsMap[key].signals.begin();
                    while (it0 < signalArray.signals.end()) {
                        *it1 += *it0;
                        it0++;
                        it1++;
                    }
                } else {
                    // the signal is from a subsequent event
                    int idx = (int)((signalArray.firstTBtime - mCurrentTriggerTime) * 0.01); // time bin offset of the pileup signal wrt trigger time. Number of time bins to be added to the signal is constants::TIMEBINS - idx
                    auto it0 = signalArray.signals.begin();
                    auto it1 = addedSignalsMap[key].signals.begin() + idx;
                    while (it1 < addedSignalsMap[key].signals.end()) {
                        *it1 += *it0;
                        it0++;
                        it1++;
                    }
                }
                // keep the labels
                for (const auto& label : signalArray.labels) {
                    // do we want to keep all labels? what about e.g. a TR signal which does not contribute to the pileup of a previous event since the signal arrives too late, but then we will have its label?
                    (addedSignalsMap[key].labels).push_back(label); // maybe check if the label already exists? is that even possible?
                }
            } // loop over active pads in detector
        }     // loop over detectors
        if (pileupSignalBecomesObsolete) {
            ++nSignalsToRemove;
        }
    } // loop over pileup container
    // remove all used added signals, keep those that can pileup to newer events.
    for (int i = 0; i < nSignalsToRemove; ++i) {
        mPileupSignals.pop_front();
    }
    return addedSignalsMap;
}

int main()
{
    std::cout << "TEST" << std::endl;
    Digitizer d;
    d.mCurrentTriggerTime = 4900;
    // create a signal at t=0
    SignalArray first;
    first.firstTBtime = 0;
    for (int tb = 0; tb < 30; ++tb) {
        first.signals[tb] = 1;
    }
    first.labels = { 1 }; // three dummy labels

    SignalArray second;
    second.firstTBtime = 2000;
    for (int tb = 0; tb < 30; ++tb) {
        second.signals[tb] = 1;
    }
    second.labels = { 2 }; // three dummy labels

    SignalArray third;
    third.firstTBtime = 4900;
    for (int tb = 0; tb < 30; ++tb) {
        third.signals[tb] = 1;
    }
    third.labels = { 3 }; // three dummy labels

    std::array<SignalContainer, MAXCHAMBER> SignalContainerPerDets;
    SignalContainerPerDets[1][0] = first;
    d.mPileupSignals.push_back(SignalContainerPerDets);
    SignalContainerPerDets[1][0] = second;
    d.mPileupSignals.push_back(SignalContainerPerDets);
    SignalContainerPerDets[1][0] = third;
    d.mPileupSignals.push_back(SignalContainerPerDets);

    std::cout << "size of pileup container (before): " << d.mPileupSignals.size() << std::endl;
    auto result = d.addSignalsFromPileup();
    std::cout << "size of pileup container (after): " << d.mPileupSignals.size() << std::endl;

    std::cout << "Result container size: " << result.size() << std::endl;
    std::cout << "time bin:     |00|01|02|03|04|05|06|07|08|09|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|" << std::endl;
    for (const auto& el : result) {
        std::cout << "key: " << el.first << std::endl;
        std::cout << "result array: |";
        for (int tb = 0; tb < 30; ++tb) {
            std::cout << "0" << el.second.signals[tb] << "|";
        }
        std::cout << std::endl;
        std::cout << "trigger from " << el.second.labels[0] << std::endl;
    }
}