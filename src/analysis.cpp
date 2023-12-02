#include "analysis.h"

void TechnicalAnalysis::calculateEMA(JSONdata &HistoricalData, int period, std::function<void(double)> setEMA) {
    assert(!HistoricalData.isEmpty());

    std::vector<double> closePrices;
    HistoricalData.accessClose(closePrices);

    if (closePrices.size() <= period) {
        std::cout << std::endl << "NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
        return;
    }

    double sum = std::accumulate(closePrices.begin(), closePrices.begin() + period, 0.0);
    double SMA = sum / period;
    std::vector<double> tempEMA = {SMA};
    setEMA(SMA);

    double multiplier = 2.0 / (period + 1);

    for (size_t i = period; i < closePrices.size(); i++) {
        double EMA = (closePrices[i] - tempEMA.back()) * multiplier + tempEMA.back();
        tempEMA.push_back(EMA);
        setEMA(EMA);
    }
}

void TechnicalAnalysis::calcFiftyEMA(JSONdata &HistoricalData) {
    calculateEMA(HistoricalData, 50, [this](double EMA) { setFifEMA(EMA); });
}

void TechnicalAnalysis::calcHundredEMA(JSONdata &HistoricalData) {
    calculateEMA(HistoricalData, 100, [this](double EMA) { setHundEMA(EMA); });
}

void TechnicalAnalysis::calcHundFiftyEMA(JSONdata &HistoricalData) {
    calculateEMA(HistoricalData, 150, [this](double EMA) { setHundFifEMA(EMA); });
}

void TechnicalAnalysis::calcTwoHundEMA(JSONdata &HistoricalData) {
    calculateEMA(HistoricalData, 200, [this](double EMA) { setTwoHundEMA(EMA); });
}

void TechnicalAnalysis::calculateSMA(JSONdata &HistoricalData, int period, std::function<void(double)> setSMA) {
    assert(!HistoricalData.isEmpty());

    std::vector<double> closePrices;
    HistoricalData.accessClose(closePrices);

    if (closePrices.size() <= period) {
        std::cout << std::endl << "NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
        return;
    }

    for (size_t i = 0; i <= closePrices.size() - period; i++) {
        double sum = std::accumulate(closePrices.begin() + i, closePrices.begin() + i + period, 0.0);
        setSMA(sum / period);
    }
}

void TechnicalAnalysis::calcFiftySMA(JSONdata &HistoricalData) {
    calculateSMA(HistoricalData, 50, [this](double SMA) { setFifSMA(SMA); });
}

void TechnicalAnalysis::calcHundredSMA(JSONdata &HistoricalData) {
    calculateSMA(HistoricalData, 100, [this](double SMA) { setHundSMA(SMA); });
}

void TechnicalAnalysis::calcHundFiftySMA(JSONdata &HistoricalData) {
    calculateSMA(HistoricalData, 150, [this](double SMA) { setHundFifSMA(SMA); });
}

void TechnicalAnalysis::calcTwoHundSMA(JSONdata &HistoricalData) {
    calculateSMA(HistoricalData, 200, [this](double SMA) { setTwoHundSMA(SMA); });
}

#include "TechnicalAnalysis.h"

void TechnicalAnalysis::calcRSI(JSONdata &HistoricalData) {
    assert(!HistoricalData.isEmpty());

    std::vector<double> closePrices;
    HistoricalData.accessClose(closePrices);

    // Ensure there is enough data for calculation
    size_t dataSize = closePrices.size() > 250 ? 250 : closePrices.size();
    if (dataSize < 2) {
        std::cout << "\nNot enough data for RSI calculation";
        return;
    }

    std::vector<double> gains, losses;
    for (size_t i = 1; i < dataSize; ++i) {
        double change = closePrices[i] - closePrices[i - 1];
        gains.push_back(change > 0 ? change : 0);
        losses.push_back(change < 0 ? -change : 0);
    }

    double avgGain = std::accumulate(gains.begin(), gains.begin() + 14, 0.0) / 14;
    double avgLoss = std::accumulate(losses.begin(), losses.begin() + 14, 0.0) / 14;

    for (size_t i = 14; i < dataSize; ++i) {
        avgGain = (avgGain * 13 + gains[i]) / 14;
        avgLoss = (avgLoss * 13 + losses[i]) / 14;
        double RS = avgLoss == 0 ? 100 : avgGain / avgLoss;
        setRSI(avgLoss == 0 ? 100 : 100 - (100 / (1 + RS)));
    }

    calcStochRSI();
}

void TechnicalAnalysis::calcStochRSI() {
    assert(!indicators.RSI.empty());

    const size_t period = 14;
    if (indicators.RSI.size() < period) {
        std::cout << "\nNot enough data for Stochastic RSI calculation";
        return;
    }

    for (size_t i = period - 1; i < indicators.RSI.size(); ++i) {
        auto range = std::minmax_element(indicators.RSI.begin() + i - period + 1, indicators.RSI.begin() + i + 1);
        double stochRSI = (indicators.RSI[i] - *range.first) / (*range.second - *range.first);
        setStoch(stochRSI);
    }
}
