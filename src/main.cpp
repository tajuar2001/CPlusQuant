#include "main.h"

int main() {
    JSONdata minData, threadData;
    TechnicalAnalysis TIobj;

    // Initialize minData with data from IEX API.
    Json::Value IEXdata = IEX::stocks::chartRange("aapl", "1d");
    minData.parseIEXdata(IEXdata);

    while (true) {
        // Separate thread for data acquisition.
        std::thread t1(AcquireIEXdata, std::ref(threadData), "aapl", "1d");

        // Spawn threads for various calculations.
        std::thread t2(&TechnicalAnalysis::calcRSI, TIobj, std::ref(minData));
        std::thread t3(&TechnicalAnalysis::calcFiftySMA, TIobj, std::ref(minData));
        // ... other thread initializations ...

        // Wait for all threads to complete.
        t1.join(); t2.join(); t3.join(); // ... other joins ...

        // Prepare for the next iteration.
        TIobj.clearTAobj();
        minData.clearJSONstruct();
        minData = threadData;
        threadData.clearJSONstruct();
    }

    return 0;
}

void AcquireIEXdata(JSONdata &dataToFormat, const std::string &stock, const std::string &range) {
    assert(dataToFormat.isEmpty() && !range.empty() && !stock.empty());
    Json::Value IEXdata = IEX::stocks::chartRange(stock, range);
    dataToFormat.parseIEXdata(IEXdata);
}
