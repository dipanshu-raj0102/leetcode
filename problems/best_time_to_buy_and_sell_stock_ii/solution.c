int maxProfit(int* prices, int pricesSize) {
    int maxprofit = 0;

    for (int i = 0; i < pricesSize - 1; i++) {
        if (prices[i + 1] > prices[i]) {
            maxprofit = maxprofit + (prices[i + 1] - prices[i]);
        }
    }
    return maxprofit;
}