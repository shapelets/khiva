// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>

af::array tsa::features::absoluteSumOfChanges(af::array tss) {
    long n = tss.dims(0);
    return af::sum(af::abs(tss(af::seq(std::min(1L, n - 1), n - 1), span) - tss(af::seq(0, std::max(0L, n - 2)), span)));
}

af::array tsa::features::absEnergy(af::array base){
    array p2 = af::pow(base, 2);
    af::array sp2 = af::sum(p2);
    return sp2;
}

af::array aggregating(af::array input, af::array (*aggregationFunction)(const af::array&, const int)) {
    return aggregationFunction(input, -1);
}

af::array aggregating(af::array input, af::array (*aggregationFunction)(const af::array&, const dim_t)) {
    return aggregationFunction(input, -1);
}

af::array aggregatingOnChunks(af::array input, long chunkSize, af::array (*aggregationFunction)(const af::array&, const int)) {
    af::array inputChunks = af::join(0, input, af::constant(0, (input.dims(0)%chunkSize == 0)? 0: chunkSize - input.dims(0)%chunkSize, input.type()));
    inputChunks = af::moddims(inputChunks, chunkSize, inputChunks.dims(0)/chunkSize);
    return af::transpose(aggregationFunction(inputChunks, 0));
}

af::array aggregatingOnChunks(af::array input, long chunkSize, af::array (*aggregationFunction)(const af::array&, const dim_t)) {
    af::array inputChunks = af::join(0, input, af::constant(0, (input.dims(0)%chunkSize == 0)? 0: chunkSize - input.dims(0)%chunkSize, input.type()));
    inputChunks = af::moddims(inputChunks, chunkSize, inputChunks.dims(0)/chunkSize);
    return af::transpose(aggregationFunction(inputChunks, 0));
}

void tsa::features::aggregatedLinearTrend(af::array t, long chunkSize, af::array (*aggregationFunction)(const af::array&, const int),
                                            af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue, af::array &stderrest) {
    af::array aggregateResult = aggregatingOnChunks(t, chunkSize, aggregationFunction);
    tsa::regression::linear(af::range(aggregateResult.dims(0)).as(t.type()), aggregateResult, slope, intercept, rvalue, pvalue, stderrest);
}

void tsa::features::aggregatedLinearTrend(af::array t, long chunkSize, af::array (*aggregationFunction)(const af::array&, const dim_t),
                                            af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue, af::array &stderrest) {
    af::array aggregateResult = aggregatingOnChunks(t, chunkSize, aggregationFunction);
    tsa::regression::linear(af::range(aggregateResult.dims(0)).as(t.type()), aggregateResult, slope, intercept, rvalue, pvalue, stderrest);
}

af::array tsa::features::autocorrelation(af::array tss, long lag) {
    long n = tss.dims(0);

    af::array y1 = tss(af::seq(n - lag), span);
    af::array y2 = tss(af::seq(lag, n - 1), span);
    
    af::array xMean = af::mean(tss, 0);

    af::array sumProduct = af::sum((y1 - af::tile(xMean, n - lag)) * (y2 - af::tile(xMean, n - lag)), 0);
    af::array den = (n - lag) * af::var(tss, true, 0);
    return sumProduct / den;
}

af::array tsa::features::c3(af::array tss, long lag) {
    af::array aux = af::shift(tss, 2 * -lag) * af::shift(tss, -lag) * tss;
    return af::mean(aux(af::seq(tss.dims(0) - 2 * lag), span), 0);
}

af::array tsa::features::cidCe(af::array tss, bool zNormalize) {
    long n = tss.dims(0);
    if (zNormalize) {
        tsa::normalization::znormInPlace(tss);
    }

    af::array diff = tss(af::seq(std::min(1L, n - 1), n - 1), span) - tss(af::seq(0, std::max(0L, n - 2)), span);
    return af::sqrt(af::sum(diff * diff));
}

af::array tsa::features::countBelowMean(af::array tss) {
    af::array mean = af::mean(tss, 0);
    af::array belowMean = (tss < af::tile(mean, tss.dims(0))).as(af::dtype::u32);
    return af::sum(belowMean, 0);
}
